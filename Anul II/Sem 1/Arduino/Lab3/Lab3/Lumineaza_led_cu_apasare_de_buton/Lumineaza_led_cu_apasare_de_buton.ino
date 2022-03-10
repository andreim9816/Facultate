
const int pushButton=2;
const int ledPin=13;
void setup() {

  Serial.begin(9600);
  pinMode(pushButton,INPUT);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  int buttonState = digitalRead(pushButton); // citeste 1 sau 0 daca e pushed butonul. Circuitul e facut sa am 1 default. Apas => am 0
  // Serial.println(buttonState);
  int ledState=!buttonState; // daca e apasat, deci 0, schimb in 1 
  digitalWrite(ledPin,ledState); // lumineaza
}
