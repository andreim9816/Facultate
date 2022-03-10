const int potPin=A0;
const int ledPin=9;

void setup() {
  // put your setup code here, to run once:

  pinMode(potPin,INPUT);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // ia valori de la 0 la 255 
 
 /* int potVal = analogRead(potPin);
  analogWrite(ledPin,potVal);
 */
  int  potVal = analogRead(potPin); 
  int ledVal=map(potVal,0,1023,0,255); // mapam cu valori de la 0 la 1023, priminand valori de la 0 la 255
  analogWrite(ledPin, ledVal); 
  
 /* 
  int potVal=analogRead(potPin);
  double voltage=potVal*(5.0/1023.0); *Cum la 5V obtin maxim 1023 pe analogOutput, voi face o regula de 3 simpla pentru a afisa voltajul 
  Serial.println(voltage);
  delay(1); // ca sa aib timp sa citeasca
 */

}
