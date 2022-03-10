
// Cand apas, se inregistreaza de prea multe ori!

const int pushButton = 2;
int counter =0;
void setup() {
  pinMode(pushButton,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
 
int buttonState=digitalRead(pushButton);
buttonState=!buttonState;
if(buttonState == HIGH)
 {
  counter++;
  Serial.println(counter);
 }

}
