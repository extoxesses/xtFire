#ifndef XT_FIRE_H
#define XT_FIRE_H

#include <xtfire/libdefs.h>

#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

// Headers for file listener
#include <sys/inotify.h>
#include <sys/stat.h>
#include <unistd.h>

// Header for file reading
#include <fstream>
#include <string>


namespace exto {
namespace emulation {

#define EVENT_SIZE (sizeof (struct inotify_event))
#define BUF_LEN (1024 * ( EVENT_SIZE + 16 ))

#define DEVICES_FOLDER "/dev/"

class EXPORT_API XtFire {
public:
  static const std::string& ARDUINO_DEV;

  XtFire(int device_id);
  ~XtFire();

  void start();

private:
  std::string device_path_;
  std::ifstream* device_;

  void openArduino();

}; //class::XtFire

}// namespace::emulation
}// namespace::exto

#endif // !XT_FIRE_H
