const int buttonPin = 2;
const int ledPin = 13;

int ledState = HIGH;
int buttonState = 0;
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup(){
 
  pinMode(ledPin,OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(ledPin, ledState);
  
}

void loop()
{
  int reading = digitalRead(buttonPin);
 
  if(reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }
  
  if( (millis() - lastDebounceTime)>debounceDelay)
  {
    if(reading != buttonState) // ca sa schimb starea 
    {
      buttonState = reading;
      if(buttonState == LOW)
      {
        ledState = !ledState;
      }
    }
  }

  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}
