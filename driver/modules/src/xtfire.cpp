#include <xtfire/xtfire.h>

using namespace std;

namespace exto {
namespace emulation {

const char* XtFire::ARDUINO_DEV = "ttyACM0";

XtFire::XtFire() {
  display_ = XOpenDisplay(NULL);

  if(display_ == NULL) {
    throw new std::invalid_argument("ERROR: Unable to open any Display");
  }// if

  file_descriptor_ = inotify_init();
  if (file_descriptor_ < 0) {
    throw new std::invalid_argument(std::strerror(file_descriptor_));
  }// if
} // constructor

XtFire::~XtFire(){
  XCloseDisplay(display_);
  (void)close(file_descriptor_);
} // constructor

void XtFire::start() {
  if(!isPluged("/dev/ttyACM0")){
    LOGGER("'/dev/ttyACM0' file not found...");
    readDeviceBuff(DEVICES_FOLDER, IN_CREATE);
  }// if
  LOGGER("'/dev/ttyACM0' file found!");

  for(int i = 0; i < 10; i++){
    //char readBuffer[1024];
    //int numBytesRead;
    //FILE *serPort = fopen("/dev/ttyACM0", "rwb");

    string line;
    ifstream myfile ("/dev/ttyACM0");
    if (myfile.is_open())
    {
      while ( getline (myfile,line) )
      {
        cout << line << '\n';
      }
      myfile.close();
    }

    else cout << "Unable to open file";
  }// for

}// start


/// --- PRIVATE METHODS --------- ///

void XtFire::addPlugListener() {
}// addPlugListener

bool XtFire::isPluged(const char* name) {
  struct stat buffer;
  return (stat (name, &buffer) == 0);
}// isPluged

char XtFire::readDeviceBuff(const char* device, int events, int* state) {
  // int events = IN_CREATE | IN_DELETE | IN_MODIFY;
  int watcher = inotify_add_watch(file_descriptor_, device, events);

  char buffer[BUF_LEN];
  int length = read(file_descriptor_, buffer, BUF_LEN);

  int i = 0;
  if (length < 0) {
    std::stringstream msg;
    msg << "ERROR: Unable to read the device: " << device;
    msg << " with statee " << state;
    throw new std::invalid_argument(msg.str());
  }// if

  while (i < length) {
    struct inotify_event *event = (struct inotify_event *) &buffer[i];
    if (event->len) {
      if (event->mask & IN_CREATE) {
        printf("The file %s was created.\n", event->name);
      } else if (event->mask & IN_DELETE) {
        printf("The file %s was deleted.\n", event->name);
      } else if (event->mask & IN_MODIFY) {
        printf("The file %s was modified.\n", event->name);

        string line;
        ifstream myfile ("/dev/ttyACM0");
        if (myfile.is_open()) {
          while ( getline (myfile,line) ){
            cout << line << '\n';
          }
          myfile.close();
        } else {
          cout << "Unable to open file";
        }


      }
    }// if
    i += EVENT_SIZE + event->len;
    std::cout << "Event: " << i << std::endl;
  }// while


  (void) inotify_rm_watch(file_descriptor_, watcher);
}// read

void XtFire::mouseClick(int button, long delay) {
  // https://www.x.org/releases/X11R7.5/doc/Xext/xtestlib.html
  XTestFakeButtonEvent(display_, button, true, delay);
  XTestFakeButtonEvent(display_, button, false, 0);
  XFlush(display_);
}// mouseClick

void XtFire::mouseMove(int x, int y) {
  XWarpPointer(display_, None, None, 0, 0, 0, 0, x, y);
}// mouseMove

}// namespace::emulation
}// namespace::exto
