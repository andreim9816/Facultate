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
  // put your setup code here, to run once:

 lcd.begin( 16 , 2); // 16 columns 2 rows
 lcd.print("Hello");

}

void loop() {

  lcd.setCursor( 0 , 1);
  lcd.print(millis()/1000);

}
