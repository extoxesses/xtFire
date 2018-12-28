// Arduino configuration
const unsigned short serial_speed = 9600;

const byte CMD_FIRE = 0;
const byte CMD_MOVX = 1;
const byte CMD_MOVY = 2;

// This scatch was developped using an Arduino Mega and its interrupts.
const byte  fire_pin = 2;

const byte    up_pin = 18;
const byte  down_pin = 19;
const byte  left_pin = 20;
const byte rigth_pin = 21;


// This parameters are needed to reduce the debounce effects of mecchanical buttons.
const unsigned long debounceDelay = 200;

unsigned long  fireDebounceTime;
unsigned long    upDebounceTime;
unsigned long  downDebounceTime;
unsigned long  leftDebounceTime;
unsigned long rigthDebounceTime;


/// Firmware initialization ---------

void setup() {
  Serial.begin(serial_speed);
  setPins();
  setInterrupts();

  startTimers();
}// setup

void loop() { }// loop


/// Configuration functions ---------

void setPins(){
  pinMode(fire_pin,  INPUT);
  
  pinMode(up_pin,    INPUT);
  pinMode(down_pin,  INPUT);
  pinMode(left_pin,  INPUT);
  pinMode(rigth_pin, INPUT);
}// setPins

void setInterrupts(){
  attachInterrupt(digitalPinToInterrupt(fire_pin),  fireISR,  RISING);
  
  attachInterrupt(digitalPinToInterrupt(up_pin),    upISR,    RISING);
  attachInterrupt(digitalPinToInterrupt(down_pin),  downISR,  RISING);
  attachInterrupt(digitalPinToInterrupt(left_pin),  leftISR,  RISING);
  attachInterrupt(digitalPinToInterrupt(rigth_pin), rigthISR, RISING);
}// setInterrupts

void startTimers(){
   fireDebounceTime = 0;
     upDebounceTime = 0;
   downDebounceTime = 0;
   leftDebounceTime = 0;
  rigthDebounceTime = 0;
}// startTimers

/// Interrupts functions ---------

void fireISR()  { serialSend(&fireDebounceTime,  CMD_FIRE, 2); }
void upISR()    { serialSend(&upDebounceTime,    CMD_MOVX, 0); }
void downISR()  { serialSend(&downDebounceTime,  CMD_MOVX, 2); }
void leftISR()  { serialSend(&leftDebounceTime,  CMD_MOVY, 0); }
void rigthISR() { serialSend(&rigthDebounceTime, CMD_MOVY, 2); }

void serialSend(unsigned long* debTime, byte cmd, byte value){
  unsigned long now = millis();
  if ((now - *debTime) > debounceDelay) {
    *debTime = now;
    int command = 10 * (int)cmd + (int)value;
    Serial.println(command);
  }// if
}// serialSend
