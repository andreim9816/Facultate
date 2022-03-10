#include<LiquidCrystal.h>

const int RSPin = 12;
const int EPin = 11;
const int D4Pin = 5;
const int D5Pin = 4;
const int D6Pin = 3;
const int D7Pin = 2;

const int trigPin = 9;
const int echoPin = 10;

long duration;
long distance; 


LiquidCrystal lcd (RSPin , EPin, D4Pin , D5Pin , D6Pin, D7Pin);


void setup() {

 lcd.begin( 16 , 2); // 16 columns 2 rows
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 Serial.begin(9600);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // emite sunetul 10 secunde
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // opreste sunetul 

  duration = pulseIn(echoPin, HIGH); // receptioneaza 
  distance = duration * 0.034 /2.0;


  lcd.print("Distance: ");  
  lcd.setCursor( 0 , 1); // setez sa inceapa pe randul 0, coloana 1
  lcd.print(distance);
  lcd.setCursor(0,0); // setez sa inceapa pe randul 0 , coloana 0 
 
  delay(400); // sa ramana 0,4 secunde afisat, dupa face clear
  lcd.clear();
  
  
}
