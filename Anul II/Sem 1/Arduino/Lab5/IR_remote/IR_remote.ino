#include<IRremote.h>

const int recvPin = 10;

IRrecv irrecv(recvPin);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true); // turn on the built-in led on the Arduino board
}

void loop()
{
 if(irrecv.decode(&results))
 {
  Serial.println(results.value, HEX);
  irrecv.resume(); 
 }
}
