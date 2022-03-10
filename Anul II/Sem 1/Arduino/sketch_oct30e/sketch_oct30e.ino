void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // define which should be the bit rate?? 
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long time=millis();
  Serial.println(time);
}
