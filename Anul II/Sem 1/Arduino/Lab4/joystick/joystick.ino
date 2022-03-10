
/* OX
 * /\                  (1023,1023)
 * |
 * |
 * |        Default
 * |        State 
 * |        
 * | 
 * |
 * |(0,0)
 * -----------------------> OY 
 */
 
const int pinX = A0;
const int pinY = A1;
int buttonValue = 0;
int xValue = 0;
int yValue = 0;
const int pushButton = 10;


void setup()
{
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pushButton, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  buttonValue = digitalRead(pushButton);
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  Serial.print("SWITCH: ");
  Serial.print(buttonValue);
  Serial.print(" | ");
  Serial.print("X Axis: " );
  Serial.print(xValue);
  Serial.print(" | " );
  Serial.print(" Y Axis: ");
  Serial.print(yValue);
  Serial.println("");
  delay(200);
}
