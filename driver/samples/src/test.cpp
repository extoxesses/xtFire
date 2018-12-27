#include <xtfire/xtfire.h>
#include <iostream>

using namespace std;
using namespace exto::emulation;

int xtFireTest(){
  try{
    cout << "Start emulation test..." << endl;
    XtFire emulator(0);
    emulator.start();
    cout << "Test ended!" << endl;

  } catch (invalid_argument* e){
    cout << " > Exception rised: " << endl;
    cout << e->what() << endl;
    return 0;
  }

  return 1;
}// xtFireTest

/// =========


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


int main(void){
  return xtFireTest();

  // uinputMouseTest();
  // uinputKeyboardTest();
  // return 1;
}// main
