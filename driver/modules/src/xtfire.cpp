#include <xtfire/xtfire.h>

namespace exto {
namespace emulation {

const std::string& XtFire::ARDUINO_DEV = "/dev/ttyACM";

XtFire::XtFire(int device_id) {
  device_path_ = ARDUINO_DEV + std::to_string(device_id);
  openArduino();
}// constructor

XtFire::~XtFire(){
  device_->close();
  delete device_;
}// destructor

void XtFire::start() {
  std::string line;
  while (getline(*device_, line)) {
    if(line != ""){
      std::cout << "  - Readed: " << line << std::endl;
    }// if
  }// while
}// start


/// --- PRIVATE METHODS --------- ///

void XtFire::openArduino(){
  device_ = new std::ifstream(device_path_);
  if (!device_->is_open()) {
    std::stringstream msg;
    msg << "[XtFire] ERROR: Unable to open device '" << device_path_ << "'";
    throw new std::invalid_argument(msg.str());
  }// if
}// openArduino

}// namespace::emulation
}// namespace::exto
