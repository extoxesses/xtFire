#include <xtfire/xtfire.h>

namespace exto {
namespace emulation {

const std::string& XtFire::ARDUINO_DEV = "/dev/ttyACM";

XtFire::XtFire(int device_id) {
  device_path_ = ARDUINO_DEV + std::to_string(device_id);
  openArduino();
  createEmulation();
  sleep(1);
}// constructor

XtFire::~XtFire(){
  // Closing the emulated device
  // Give userspace some time to read the events before we destroy the device with UI_DEV_DESTOY.
  sleep(1);
  ioctl(emu_fd_, UI_DEV_DESTROY);
  close(emu_fd_);

  // Closing the connection to Arduino
  device_->close();
  delete device_;
}// destructor

void XtFire::start() {
  std::string line;
  while (std::getline(*device_, line)) {
    if(line != ""){
      LOGGER(line);

      int tmp = std::stoi(line);
      int cmd = tmp / 10;
      int value = tmp % 10 - 1;

      parseCmd(cmd, value);
    }// if
  }// while
}// start


/// --- PRIVATE METHODS --------- ///

void XtFire::createEmulation(){
  emu_fd_ = open(LINUX_UINPUT_FOLDER, O_WRONLY | O_NONBLOCK);
  if(emu_fd_ == -1){
    std::string msg = "[XtFire] ERROR: Unable to create virtual HID device.\n";
               msg += "                Probably you don't have the right permissions.";
    throw new std::invalid_argument(msg);
  }// if

  // Enable controller buttons events.
  ioctl(emu_fd_, UI_SET_EVBIT, EV_KEY);
  ioctl(emu_fd_, UI_SET_KEYBIT, BTN_GAMEPAD); // aka BTN_SOUTH or BTN_A.
  ioctl(emu_fd_, UI_SET_KEYBIT, BTN_EAST);    // Second button.
  /***
   * Because of Arduino mini allows only 2 interrupts pins,
   * the following two buttons are not needed.
   ***/
  ioctl(emu_fd_, UI_SET_KEYBIT, BTN_WEST);    // Third button.
  ioctl(emu_fd_, UI_SET_KEYBIT, BTN_NORTH);   // Fourth button.

  // Enable controller relative events.
  ioctl(emu_fd_, UI_SET_EVBIT, EV_REL);
  ioctl(emu_fd_, UI_SET_RELBIT, REL_X);
  ioctl(emu_fd_, UI_SET_RELBIT, REL_Y);

  // Configure BUS
  struct uinput_setup usetup;
  memset(&usetup, 0, sizeof(usetup));
  usetup.id.bustype = BUS_USB;
  usetup.id.vendor = EXTO_VENDOR
  usetup.id.product = XT_FIRE_MOD_W;
  strcpy(usetup.name, XT_FIRE_MOD_W_NAME);

  // Create virtual device
  ioctl(emu_fd_, UI_DEV_SETUP, &usetup);
  ioctl(emu_fd_, UI_DEV_CREATE);
}// createEmulation

void XtFire::mouseMove(int x, int y, int factor){
  writeCmd(emu_fd_, EV_REL, REL_X, (factor * x));
  writeCmd(emu_fd_, EV_REL, REL_Y, (factor * y));
  writeCmd(emu_fd_, EV_SYN, SYN_REPORT, 0);
  usleep(15000);
}// mouseMove

void XtFire::parseCmd(int cmd, int value){
  int msg = 0;
  switch (cmd) {
    case FIRE:
      writeCmd(emu_fd_, EV_KEY, BTN_EAST, 1);
      writeCmd(emu_fd_, EV_SYN, SYN_REPORT, 0);
      writeCmd(emu_fd_, EV_KEY, BTN_GAMEPAD, 0);
      writeCmd(emu_fd_, EV_SYN, BTN_EAST, 0);
      break;

    case MOVX:
      mouseMove(value, 0, SPACE_MOV_UNIT);
      break;

    case MOVY:
      mouseMove(0, value, SPACE_MOV_UNIT);
      break;
  }// case
}// parseCmd

void XtFire::openArduino(){
  device_ = new std::ifstream(device_path_);
  if (!device_->is_open()) {
    std::stringstream msg;
    msg << "[XtFire] ERROR: Unable to open device '" << device_path_ << "'";
    throw new std::invalid_argument(msg.str());
  }// if
}// openArduino

void XtFire::writeCmd(int fd, int type, int code, int val) {
   struct input_event ie;
   ie.type = type;
   ie.code = code;
   ie.value = val;

   ie.time.tv_sec = 0;
   ie.time.tv_usec = 0;

   write(fd, &ie, sizeof(ie));
}// writeCmd

}// namespace::emulation
}// namespace::exto
