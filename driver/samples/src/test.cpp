#include <xtfire/xtfire.h>

#include <iostream>

using namespace std;
using namespace exto::emulation;

int main(void){
  cout << "Start emulation test..." << endl;
  // XtFire emulator("/dev/ttyACM0");
  XtFire emulator;
  emulator.start();

  cout << "Test ended!" << endl;
  return 1;
}// main
