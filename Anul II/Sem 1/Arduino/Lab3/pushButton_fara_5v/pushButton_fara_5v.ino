
const int pushButton=2;
const int ledPin=13;
void setup() {

  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  pinMode(pushButton,INPUT_PULLUP); // ii dau eu 5V prin chestia asta 
}

 // nu voi avea rezistenta si nici 5v => pinMode( , INPUT_PULLUP);

void loop() {
  int buttonState = digitalRead(pushButton); // citeste 1 sau 0 daca e pushed butonul. Circuitul e facut sa am 1 default. Apas => am 0
  int ledState=!buttonState; // daca e apasat, e 0, schimb in 1 
  digitalWrite(ledPin,ledState); // lumineaza
}
