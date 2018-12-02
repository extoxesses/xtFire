#ifndef XT_FIRE_H
#define XT_FIRE_H

#include <xtfire/libdefs.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace exto {
namespace emulation {

class EXPORT_API XtFire {
public:
  static const int LEFT_BTN = 1;
  static const int CENTER_BTN = 2;
  static const int RIGTH_BTN = 1;

  XtFire();
  ~XtFire();

  void start();

private:
  Display* display_;

  void mouseMove(int x, int y);
  void click(int button, int delay = 100);

}; //class::XtFire

}// namespace::emulation
}// namespace::exto

#endif // !XT_FIRE_H
