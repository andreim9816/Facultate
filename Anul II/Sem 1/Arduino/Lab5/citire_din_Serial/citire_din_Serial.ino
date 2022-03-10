int incomingByte = 0;

void setup() {
  Serial.begin(9600);
  }

void loop()
{
  if(Serial.available() > 0) 
  {
    incomingByte = Serial.read();
    Serial.print("I received (DEC): ");
    Serial.println(incomingByte, DEC);

    Serial.print("I received (HEX): ");
    Serial.println(incomingByte, HEX);

    Serial.print("I received (OCT): ");
    Serial.println(incomingByte, OCT);

    Serial.print("I received (BIN): ");
    Serial.println(incomingByte, BIN);

    char ch = (char)incomingByte;
    Serial.print(" I received " );
    Serial.println(ch);
  }
}
