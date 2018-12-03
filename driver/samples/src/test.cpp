#include <xtfire/xtfire.h>

#include <iostream>

using namespace std;
using namespace exto::emulation;

int main(void){
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
}// main
