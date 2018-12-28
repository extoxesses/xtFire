// Gun properties
const byte a_btn     = 0x0002;
const byte b_btn     = 0x0003;

const byte up_btn    = 0x0030;
const byte down_btn  = 0x0031;
const byte left_btn  = 0x0032;
const byte rigth_btn = 0x0033;

const unsigned short serial_speed = 1200; // 9600;

/*
 * This parameters are needed to reduce the debounce
 * effects of mecchanical buttons.
 */
const unsigned long debounceDelay = 200;
unsigned long debounceTime = 0;


void setup() {
  Serial.begin(serial_speed);

  pinMode(a_btn,     INPUT);
  pinMode(b_btn,     INPUT);
  // attachInterrupt(digitalPinToInterrupt(a_btn), aButtonISR, RISING);
  // attachInterrupt(digitalPinToInterrupt(b_btn), bButtonISR, RISING);
  
  pinMode(up_btn,    INPUT);
  pinMode(down_btn,  INPUT);
  pinMode(left_btn,  INPUT);
  pinMode(rigth_btn, INPUT);
}// setup

void loop() {
  /*
   * For x and y I supposed that the two buttons in the same axe
   * (up&down and left&rigth) will be not pressed at the same time
   */
  byte x = - digitalRead(up_btn) + digitalRead(down_btn);
  byte y = - digitalRead(left_btn) + digitalRead(rigth_btn);
  byte a = digitalRead(a_btn);
  byte b = digitalRead(b_btn);

  bool is_changed = (x || y || a || b);
  if(is_changed){
    String msg = String(x) + '#' + String(y) + '#' + String(a) + '#' + String(b);
    Serial.println(msg); 
  }// if
}// loop

void aButtonISR() {
  btnFilter(1, 0);
}// aButtonCallback

void bButtonISR() {
  btnFilter(0, 1);
}// aButtonCallback

void btnFilter(byte a, byte b){
  long now = millis();
  if ((now - debounceTime) > debounceDelay) {
    debounceTime = now;
    //a_value = a;
    //b_value = b;

    //Serial.println(String(a) + String(b));
  }// if
}// serialSend
