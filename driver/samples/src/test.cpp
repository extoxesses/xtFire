#include <xtfire/xtfire.h>
#include <iostream>

//#include <linux/uinput.h>
//#include <fcntl.h>
//#include <string.h>
//#include <unistd.h>

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

//void emit(int fd, int type, int code, int val) {
//   struct input_event ie;

//   ie.type = type;
//   ie.code = code;
//   ie.value = val;
//   /* timestamp values below are ignored */
//   ie.time.tv_sec = 0;
//   ie.time.tv_usec = 0;

//   write(fd, &ie, sizeof(ie));
//}

//void hello(int fd){
//  emit(fd, EV_KEY, KEY_H, 1);
//  emit(fd, EV_SYN, SYN_REPORT, 0);
//  emit(fd, EV_KEY, KEY_H, 0);
//  emit(fd, EV_SYN, SYN_REPORT, 0);

//  emit(fd, EV_KEY, KEY_E, 1);
//  emit(fd, EV_SYN, SYN_REPORT, 0);
//  emit(fd, EV_KEY, KEY_E, 0);
//  emit(fd, EV_SYN, SYN_REPORT, 0);

//  emit(fd, EV_KEY, KEY_L, 1);
//  emit(fd, EV_SYN, SYN_REPORT, 0);
//  emit(fd, EV_KEY, KEY_L, 0);
//  emit(fd, EV_SYN, SYN_REPORT, 0);

//  emit(fd, EV_KEY, KEY_L, 1);
//  emit(fd, EV_SYN, SYN_REPORT, 0);
//  emit(fd, EV_KEY, KEY_L, 0);
//  emit(fd, EV_SYN, SYN_REPORT, 0);

//  emit(fd, EV_KEY, KEY_O, 1);
//  emit(fd, EV_SYN, SYN_REPORT, 0);
//  emit(fd, EV_KEY, KEY_O, 0);
//  emit(fd, EV_SYN, SYN_REPORT, 0);

//  emit(fd, EV_KEY, KEY_SPACE, 1);
//  emit(fd, EV_SYN, SYN_REPORT, 0);
//  emit(fd, EV_KEY, KEY_SPACE, 0);
//  emit(fd, EV_SYN, SYN_REPORT, 0);

//  emit(fd, EV_KEY, KEY_W, 1);
//  emit(fd, EV_SYN, SYN_REPORT, 0);
//  emit(fd, EV_KEY, KEY_W, 0);
//  emit(fd, EV_SYN, SYN_REPORT, 0);
//}

//void uinputKeyboardTest(){
//  struct uinput_setup usetup;

//  int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);


//  /*
//  * The ioctls below will enable the device that is about to be
//  * created, to pass key events, in this case the space key.
//  */
//  ioctl(fd, UI_SET_EVBIT, EV_KEY);
//  ioctl(fd, UI_SET_KEYBIT, KEY_H);
//  ioctl(fd, UI_SET_KEYBIT, KEY_E);
//  ioctl(fd, UI_SET_KEYBIT, KEY_L);
//  ioctl(fd, UI_SET_KEYBIT, KEY_O);
//  ioctl(fd, UI_SET_KEYBIT, KEY_W);
//  ioctl(fd, UI_SET_KEYBIT, KEY_SPACE);


//  memset(&usetup, 0, sizeof(usetup));
//  usetup.id.bustype = BUS_USB;
//  usetup.id.vendor = 0x1234; /* sample vendor */
//  usetup.id.product = 0x5678; /* sample product */
//  strcpy(usetup.name, "Example device");

//  ioctl(fd, UI_DEV_SETUP, &usetup);
//  ioctl(fd, UI_DEV_CREATE);

//  /*
//  * On UI_DEV_CREATE the kernel will create the device node for this
//  * device. We are inserting a pause here so that userspace has time
//  * to detect, initialize the new device, and can start listening to
//  * the event, otherwise it will not notice the event we are about
//  * to send. This pause is only needed in our example code!
//  */
//  sleep(1);

//  /* Key press, report the event, send key release, and report again */
//  //  emit(fd, EV_KEY, KEY_H, 1);
//  //  emit(fd, EV_SYN, SYN_REPORT, 0);
//  //  emit(fd, EV_KEY, KEY_H, 0);
//  //  emit(fd, EV_SYN, SYN_REPORT, 0);

//  hello(fd);

//  /*
//  * Give userspace some time to read the events before we destroy the
//  * device with UI_DEV_DESTOY.
//  */
//  sleep(1);

//  ioctl(fd, UI_DEV_DESTROY);
//  close(fd);
//}

//void uinputMouseTest(){
//  struct uinput_setup usetup;
//  int i = 50;

//  int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

//  /* enable mouse button left and relative events */
//  ioctl(fd, UI_SET_EVBIT, EV_KEY);
//  ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);

//  ioctl(fd, UI_SET_EVBIT, EV_REL);
//  ioctl(fd, UI_SET_RELBIT, REL_X);
//  ioctl(fd, UI_SET_RELBIT, REL_Y);

//  memset(&usetup, 0, sizeof(usetup));
//  usetup.id.bustype = BUS_USB;
//  usetup.id.vendor = 0x1234; /* sample vendor */
//  usetup.id.product = 0x5678; /* sample product */
//  strcpy(usetup.name, "Example device");

//  ioctl(fd, UI_DEV_SETUP, &usetup);
//  ioctl(fd, UI_DEV_CREATE);

//  /*
//   * On UI_DEV_CREATE the kernel will create the device node for this
//   * device. We are inserting a pause here so that userspace has time
//   * to detect, initialize the new device, and can start listening to
//   * the event, otherwise it will not notice the event we are about
//   * to send. This pause is only needed in our example code!
//   */
//  sleep(1);

//  /* Move the mouse diagonally, 5 units per axis */
//  while (i--) {
//     emit(fd, EV_REL, REL_X, 5);
//     emit(fd, EV_REL, REL_Y, 5);
//     emit(fd, EV_SYN, SYN_REPORT, 0);
//     usleep(15000);
//  }

//  /*
//   * Give userspace some time to read the events before we destroy the
//   * device with UI_DEV_DESTOY.
//   */
//  sleep(1);

//  ioctl(fd, UI_DEV_DESTROY);
//  close(fd);
//}// builtinTest

int main(void){
  return xtFireTest();

  // uinputMouseTest();
  // uinputKeyboardTest();
  // return 1;
}// main
