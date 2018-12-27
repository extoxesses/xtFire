#include <xtfire/xtfire.h>

namespace exto {
namespace emulation {

const std::string& XtFire::ARDUINO_DEV = "/dev/ttyACM";

XtFire::XtFire(int device_id) {
  device_path_ = ARDUINO_DEV + std::to_string(device_id);

  openArduino();
  createEmulation();
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
  while (getline(*device_, line)) {
    if(line != ""){


      std::cout << "  - Readed: " << line << std::endl;

      // Key press, report the event, send key release, and report again.
      //  emit(fd, EV_KEY, KEY_H, 1);
      //  emit(fd, EV_SYN, SYN_REPORT, 0);
      //  emit(fd, EV_KEY, KEY_H, 0);
      //  emit(fd, EV_SYN, SYN_REPORT, 0);

      // Mouse movement simultion
      // emit(fd, EV_REL, REL_X, 5);
      // emit(fd, EV_REL, REL_Y, 5);
      // emit(fd, EV_SYN, SYN_REPORT, 0);
      // usleep(15000);

    }// if
  }// while
}// start


/// --- PRIVATE METHODS --------- ///

void XtFire::createEmulation(){
  struct uinput_setup usetup;
  emu_fd_ = open(LINUX_UINPUT_FOLDER, O_WRONLY | O_NONBLOCK);
  if(emu_fd_ == -1){
    std::stringstream msg;
    msg << "[XtFire] ERROR: Unable to create virtual HID device.\n";
    msg << "                Probably you don't have the right permissions.";
    throw new std::invalid_argument(msg.str());
  }// if

  /* TODO: Enable joypad interaction */

  memset(&usetup, 0, sizeof(usetup));
  usetup.id.bustype = BUS_USB;
  usetup.id.vendor = EXTO_VENDOR
  usetup.id.product = XT_FIRE_MOD_W;
  strcpy(usetup.name, XT_FIRE_MOD_W_NAME);

  ioctl(emu_fd_, UI_DEV_SETUP, &usetup);
  ioctl(emu_fd_, UI_DEV_CREATE);
  // sleep(1);
}// createEmulation

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
