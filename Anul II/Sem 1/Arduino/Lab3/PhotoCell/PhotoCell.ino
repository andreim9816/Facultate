
const int photoCellPin = A0;
const int ledPin = 13;
int photoCellValue = 0;

int ledState = 0;
int threshold = 45 ;

void setup() {
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);
}

void loop() {
 
  photoCellValue = analogRead(photoCellPin);
  Serial.println(photoCellValue);
  if(photoCellValue > threshold)
  {
   ledState = HIGH;
  }
  else ledState = LOW;

  digitalWrite(ledPin, ledState);
}
