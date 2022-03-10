 

const int trigPin = 9;
const int echoPin = 10;

long duration;
long distance;  

void setup() {
  // put your setup code here, to run once:

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
  
  Serial.print(" Distance : ");
  Serial.println(distance);

}
