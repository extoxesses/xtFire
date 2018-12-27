// Gun properties
const byte a_button = 0x0002;
const byte b_button = 0x0003;

const unsigned short serial_speed = 9600;

/*
 * This parameters are needed to reduce the debounce
 * effects of mecchanical buttons.
 */
const unsigned long debounceDelay = 200;
unsigned long debounceTime = 0;


void setup() {
  Serial.begin(serial_speed);

  // pinMode(a_button, INPUT);
  // attachInterrupt(digitalPinToInterrupt(a_button), aButtonISR, RISING);
  
  // pinMode(b_button, INPUT);
  // attachInterrupt(digitalPinToInterrupt(b_button), bButtonISR, RISING);

  pinMode(30, INPUT);
  pinMode(31, INPUT);
  pinMode(32, INPUT);
  pinMode(33, INPUT);
}// setup

void loop() {
  //*
  int up = digitalRead(31);
  int down = digitalRead(30);
  int left = digitalRead(33);
  int rigth = digitalRead(32);
  // char msg[ ] = {up, ' ', down, ' ', left, ' ', rigth};
  // String msg = String(up) + ' ' + String(down) + ' ' + String(left) + ' ' + String(rigth);
  Serial.println(String(up));
  //*/
}// loop

void aButtonISR() {
  serialSend(a_button);
}// aButtonCallback

void bButtonISR() {
  serialSend(b_button);
}// aButtonCallback

void serialSend(byte button){
  long now = millis();
  if ((now - debounceTime) > debounceDelay) {
    debounceTime = now;
    Serial.println(String(button));
  }// if
}// serialSend
