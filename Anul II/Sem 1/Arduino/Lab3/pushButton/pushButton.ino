
const int pushButton=2;
const int pinLed=13;
void setup() {

  Serial.begin(9600);
  pinMode(pushButton,INPUT);
  pinMode(pinLed,OUTPUT);
}

void loop() {
  int buttonState = digitalRead(pushButton); // citeste 1 sau 0 daca e pushed butonul
   Serial.println(buttonState);
}
