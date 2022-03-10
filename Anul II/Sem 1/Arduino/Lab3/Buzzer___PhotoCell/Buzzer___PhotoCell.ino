const int buzzerPin = 11;
const int photoCellPin = A0;

int buzzerTone = 1000;
int photoCellValue = 0;

int minPitch = 120;
int maxPitch = 1500;

int minPhotoCell = 40;// my value
int maxPhotoCell = 90;// my value 

void setup() {
Serial.begin(9600);

}

void loop() {
  photoCellValue = analogRead(photoCellPin);
  Serial.println(photoCellValue);
  int buzzerTone = map(photoCellValue,minPhotoCell,maxPhotoCell,minPitch,maxPitch);
  tone(buzzerPin, buzzerTone, 10);
}
