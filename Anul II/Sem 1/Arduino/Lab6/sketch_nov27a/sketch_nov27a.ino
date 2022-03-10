const int row[] = {6, 11, A5, 9, 5, A4, 4, A2};

                 //C1 C2 C3 C4  C5 C6  C7  C8 - anodes
const int col[] = {10, 3, 2, 7, A3, 8, 12, 13};

int matrix[8][17] ={
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,1,0,0,1,0,0,0,1,0,1,0,1,0,1,0},
  {0,0,1,0,0,1,0,0,0,0,1,0,0,0,1,0,0},
  {0,0,1,0,0,1,0,0,0,1,0,1,0,1,0,1,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

 /* 
  {0,0,0,0,0,0,0,0},
  {1,0,1,0,1,0,1,0},
  {0,1,0,0,0,1,0,0},
  {1,0,1,0,1,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,1,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,0}
  */
};

unsigned long long lastTime = 0;

int firstCol = 0;
int lastCol = 8;

void setup() {
  int i;Serial.begin(9600);
  
  for (i = 0; i < 8; i++)
  {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
  }
  
  for (i = 0; i < 8; i++)
  {
    digitalWrite(col[i], LOW);
    digitalWrite(row[i], HIGH);
  }
}

void displayMatrix()
{
  int i, j;
  Serial.println((j+firstCol)%17);
  for(i = 0 ; i < 8 ; i++)
  {
    for(j = 0 ; j < 8 ; j++)
     digitalWrite(col[j] , matrix[i][ (j+firstCol) %17] ); /// ATENTIE!!! NU MODIFIC COL[J] CACI ACOLO AM PINII. MODIFIC COORDONATA MATRICEI

    digitalWrite(row[i],LOW);
    delay(1);
    digitalWrite(row[i],HIGH);
  }

  if(millis() - lastTime >= 100)
  {
    delay(1);
    firstCol++;
    lastTime = millis();
  } 
}

void loop() {
    displayMatrix();
}
