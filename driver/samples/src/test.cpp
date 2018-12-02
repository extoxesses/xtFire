#include <xtfire/xtfire.h>

#include <iostream>

using namespace exto::emulation;

int main(void){
  std::cout << "Start emulation test..." << std::endl;
  XtFire emulator;
  emulator.mouseMove(50, 50);

  std::cout << "Test ended!" << std::endl;
  return 1;
}// main
