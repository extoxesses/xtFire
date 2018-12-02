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
  XtFire();
  ~XtFire();

  void start();

  void mouseMove(int x, int y);

private:
  Display* display_;


}; //class::XtFire

}// namespace::emulation
}// namespace::exto

#endif // !XT_FIRE_H
