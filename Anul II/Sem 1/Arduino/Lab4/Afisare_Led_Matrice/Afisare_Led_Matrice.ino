
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

const int segSize = 8;
int index = 0;
int state = HIGH;

int segments[segSize]={ pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP};

void setup()
{
  for(int i=0; i< segSize; i++)
   {
    pinMode(segments[i], OUTPUT);
   }
   
}

// A B C D E F G DH
// 0 1 1 0 0 0 0 0 penru 1
// 1 1 0 1 1 0 1 0 pentru 2 etc


void loop()
{
  digitalWrite(segments[index], state );
  index++;
  delay(500);

  if(index>=segSize)
  {
    index = 0;
    state = !state;
  }
  
}
