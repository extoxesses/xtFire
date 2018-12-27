#ifndef XT_FIRE_H
#define XT_FIRE_H

#include <xtfire/libdefs.h>
#include <xtfire/consts.h>

#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

#include <stdio.h>
#include <stdlib.h>

// Linux POSIX headers files
#include <linux/uinput.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>



namespace exto {
namespace emulation {

#define LINUX_UINPUT_FOLDER "/dev/uinput"

class EXPORT_API XtFire {
public:
  static const std::string& ARDUINO_DEV;

  XtFire(int device_id);
  ~XtFire();

  void start();

private:
  std::string device_path_;
  std::ifstream* device_;
  int emu_fd_;

  void createEmulation();

  void openArduino();

  void writeCmd(int fd, int type, int code, int val);

}; //class::XtFire

}// namespace::emulation
}// namespace::exto

#endif // !XT_FIRE_H
