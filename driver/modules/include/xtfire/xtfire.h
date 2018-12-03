#ifndef XT_FIRE_H
#define XT_FIRE_H

#include <xtfire/libdefs.h>

#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

// Headers for mouse
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

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
  static const int LEFT_BTN = 1;
  static const int CENTER_BTN = 2;
  static const int RIGTH_BTN = 3;

  static const std::string& ARDUINO_DEV;

  XtFire(int device);
  ~XtFire();

  void start();

private:
  Display* display_;
  int file_descriptor_, device_;
  bool pluged_;

  void addPlugListener();
  bool isPluged (const std::string& name);
  void serialRead(const std::string& device_path);
  void waitDevice(const std::string& device, int events, std::string* dev_path);



  void mouseClick(int button, long delay = 100);
  void mouseMove(int x, int y);

}; //class::XtFire

}// namespace::emulation
}// namespace::exto

#endif // !XT_FIRE_H
