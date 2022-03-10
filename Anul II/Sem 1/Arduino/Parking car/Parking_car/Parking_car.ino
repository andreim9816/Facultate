#include <Servo.h>
 
int servoPin = 6;
Servo servo; 

int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;

const int trigFront = 12;
const int echoFront = A1;

const int trigBack = 13;
const int echoBack = A0;

int motorSpeed = 250;
int distanceBack;
int distanceFront;
int duration;
int angle;
int parking = 0;

void setup() {
  
  pinMode(in1Pin , OUTPUT);
  pinMode(in2Pin , OUTPUT);
  pinMode(enablePin , OUTPUT);

  pinMode(trigFront , OUTPUT);
  pinMode(echoFront , INPUT);

  pinMode(trigBack , OUTPUT);
  pinMode(echoBack , INPUT);
  
  servo.attach(servoPin);
  /*
  for( angle = 95 ; angle < 105 ; angle++)
  {
    servo.write(angle);
    delay(40);
  }

  for(int i = angle ; i > 70 ; i--)
  {
    servo.write(i);
    delay(40);
  }
  */
  
  
  for(angle = 70 ; angle < 90 ; angle++)
  {
    servo.write(angle);
    delay(40);
  }

  
  for( ; angle >= 60 ; angle--)
  {
    servo.write(angle);
    delay(40);
  }
  
  Serial.begin(9600);
}

void setMotor(int motorSpeed , boolean reverse)
{
  analogWrite(enablePin, motorSpeed);
  digitalWrite(in1Pin, reverse);
  digitalWrite(in2Pin, !reverse);
}

long long timp = 0;

void porneste()
{
  if(timp == 0)
    {
      setMotor(motorSpeed , HIGH);
      timp = millis();
    }
    
  else if (millis() - timp >= 100)
    setMotor(160 , HIGH);
}

void readSensor(const int trigPin , const int echoPin , int &distance)
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  float duration = pulseIn(echoPin, HIGH);
  
  // Sound wave reflects from the obstacle, so to calculate the distance we
  // consider half of the distance traveled.
  distance = duration * 0.034 / 2;
}

unsigned long long timeFront = 0;
unsigned long long timeBack = 0;

const int distanceDepth = 15; // the depth has to be at least 15cm for the car to park there
const int timeLength = 1500; // de masurat !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void parkCar()
{
   
   parking = 2;

   // rotim rotile spre stanga
   for( ; angle > 60 ; angle --)
   {
     servo.write(angle);
     delay(30);
   }
   
  // delay(300); // mai merge putin in fata

   setMotor(0 , LOW); // oprim

   // rotim rotile spre dreapta
   for( ; angle < 105 ; angle++)
    {
      servo.write(angle);
      delay(40);
    }

   // merge in spate 
   setMotor(160 , LOW);
   delay(2000);

   for( ; angle > 45 ; angle--)
   {
    servo.write(angle);
    delay(40);
   }
   
   setMotor(160 , LOW);
   delay(600);
   
   for(; angle < 105 ; angle++)
   {
    servo.write(angle);
    delay(40);
   }
   // indreapta rotile si merge in fata
   for( ; angle < 65 ; angle++)
   {
    servo.write(angle);
    delay(40);
   }

   setMotor(160 , HIGH);
   delay(1000);

   setMotor(0 , HIGH);
}

void loop() 
{  
  /*
   * Scaneaza ce are in dreapta, cand gaseste spatiu gol, retine. Daca va fi spatiu gol ( si suficient de lat cat sa incapa masinuta), se incepe parcarea laterala
   * Intai merge putin in fata ( cam jumatate de masinuta / un anumit timp), dupa care se opreste. Rotile se invart spre dreapta, se porneste cu spatele.
   */

  // pornim masina, la inceput cu putere mai mare astfel incat sa ii fie mai usor sa o ia din loc
  if(parking == 0)
  {
      porneste();
  
    // citim senzorii
    readSensor(trigFront, echoFront, distanceFront);
    readSensor(trigBack, echoBack, distanceBack);

    Serial.print("Front ");
    Serial.println(distanceFront);

    Serial.print("Back ");
    Serial.println(distanceBack);
    
     if(distanceFront >= distanceDepth) // am gasit un loc cu cel putin 15 cm, atunci inseamna ca avem latimea minima
     {
      if(timeFront == 0)
       timeFront = millis();
      else timeBack = millis();
     }
     else 
     {
      if(timeFront != 0) 
      {
        // sa vedem daca avem lungimea necesara
        if(timeBack - timeFront >= timeLength) 
          parking = 1; // atunci incepe parcarea
      }
      timeFront = timeBack = 0;
     }
  }
  if(parking == 1)
  {
    // parcam
   parkCar();
  }
  
  /*
  setMotor(motorSpeed , HIGH);
  delay(5000);
  
  setMotor(motorSpeed , LOW);
  
  delay(3000);

  
  setMotor(motorSpeed , LOW);
   */
 /* for(int angle = 70 ; angle < 90 ; angle++)
  {
    servo.write(angle);
    delay(30);
  }
  for(int angle = 90 ; angle > 70 ; angle--)
  {
    servo.write(angle);
    delay(30);
  }*/
}
