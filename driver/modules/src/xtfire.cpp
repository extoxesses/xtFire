#include <xtfire/xtfire.h>

namespace exto {
namespace emulation {

const std::string& XtFire::ARDUINO_DEV = "/dev/ttyACM";

XtFire::XtFire(int device) {
  device_ = device;
  display_ = XOpenDisplay(NULL);

  if(display_ == NULL) {
    throw new std::invalid_argument("[XtFire] ERROR: Unable to open any Display");
  }// if

  file_descriptor_ = inotify_init();
  if (file_descriptor_ < 0) {
    throw new std::invalid_argument(std::strerror(file_descriptor_));
  }// if
} // constructor

XtFire::~XtFire(){
  XCloseDisplay(display_);
  (void)close(file_descriptor_);
} // constructor

void XtFire::start() {
  std::string device = ARDUINO_DEV + std::to_string(device_);
  if(!isPluged(device)){
    LOGGER("'" + device + " file not found...");
    waitDevice(DEVICES_FOLDER, IN_CREATE, &device);
  }// if
  LOGGER("'" + device + "' detected!");

  serialRead(device);
}// start


/// --- PRIVATE METHODS --------- ///

void XtFire::addPlugListener() {
}// addPlugListener

bool XtFire::isPluged(const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}// isPluged

void XtFire::serialRead(const std::string& device_path) {
  std::ifstream device(device_path);
  if (!device.is_open()) {
    std::stringstream msg;
    msg << "[XtFire] ERROR: Unable to open device '" << device_path << "'";
    throw new std::invalid_argument(msg.str());
  }// if

  std::string line;
  while (getline(device, line)) {
    if(line != ""){
      std::cout << "  - Readed: " << line << std::endl;
    }// if
  }// while
  device.close();
}// serialRead

void XtFire::waitDevice(const std::string& device, int events, std::string* dev_path) {
  int watcher = inotify_add_watch(file_descriptor_, device.c_str(), events);

  char buffer[BUF_LEN];
  int length = read(file_descriptor_, buffer, BUF_LEN);
  if (length < 0) {
    std::stringstream msg;
    msg << "[XtFire] ERROR: Unable to read the device: " << device;
    throw new std::invalid_argument(msg.str());
  }// if

  int inc = length;
  for (int i = 0; i < length; i+= inc) {
    struct inotify_event *event = (struct inotify_event *) &buffer[i];
    if (event->len) {
      *dev_path = DEVICES_FOLDER;
      *dev_path += event->name;
    }// if
    inc = EVENT_SIZE + event->len;
  }// for
  (void) inotify_rm_watch(file_descriptor_, watcher);
}// waitDevice

void XtFire::mouseClick(int button, long delay) {
  // https://www.x.org/releases/X11R7.5/doc/Xext/xtestlib.html
  XTestFakeButtonEvent(display_, button, true, delay);
  XTestFakeButtonEvent(display_, button, false, 0);
  XFlush(display_);
}// mouseClick

void XtFire::mouseMove(int x, int y) {
  XWarpPointer(display_, None, None, 0, 0, 0, 0, x, y);
}// mouseMove

}// namespace::emulation
}// namespace::exto
