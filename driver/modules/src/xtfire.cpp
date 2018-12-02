#include <xtfire/xtfire.h>

using namespace std;

namespace exto {
namespace emulation {

XtFire::XtFire(){
  display_ = XOpenDisplay(NULL);

  if(display_ == NULL) {
    throw new std::invalid_argument("ERROR: Unable to open any Display");
  }// if
} // constructor

XtFire::~XtFire(){
  /* if(display_ != NULL) {
    delete display_;
  }// if */
} // constructor

void XtFire::start(){
}// start

/// --- PRIVATE METHODS --------- ///

void XtFire::mouseMove(int x, int y){
  // Freely inspired by:
  // https://stackoverflow.com/questions/20581343/how-to-move-the-mouse-cursor-from-user-code

  XWarpPointer(display_, None, None, 0, 0, 0, 0, x, y);
  XCloseDisplay(display_);
}// move

}// namespace::emulation
}// namespace::exto
