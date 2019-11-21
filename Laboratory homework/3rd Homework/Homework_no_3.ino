const int pinX = A0;
const int pinY = A1;
const int pinSW = A2;

int valueSW = 0;
int lastValueSW = 0;
int valueX = 0;
int valueY = 0;
bool joyMovedX = false;
bool joyMovedY = false;
int minThreshold = 400; //min value default position
int maxThreshold = 600; //max....

const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int segSize = 8;
const int noOfDisplays = 4;
const int noOfDigits = 10;

bool joyMoved = false;

int dpState = LOW;
int dpSpot = 0;
int dpLastSpot = 0;
int verifyPush = 0;
int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int digit4 = 0;

unsigned long currentTime = 0;
unsigned long lastTime = 0;
const long period = 1000;

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

int digits[noOfDisplays] = {
  pinD1, pinD2, pinD3, pinD4
 };   

int digitNumbers[noOfDisplays] = {
  digit1, digit2, digit3, digit4
};
 
byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};


void displayNumber(byte digit, byte decimalPoint) {
  for (int i = 0; i < segSize - 1; i++) {
  digitalWrite(segments[i], digitMatrix[digit][i]);
  }

  digitalWrite(segments[segSize - 1], decimalPoint);
}


void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
    digitalWrite(digits[i], HIGH);
  }
  
  digitalWrite(digits[num], LOW);
}
         

void setup() {
  for (int i = 0; i < segSize ; i++)
  {
    pinMode(segments[i], OUTPUT);  
  }
  for (int i = 0; i < noOfDisplays; i++)
  {
    pinMode(digits[i], OUTPUT);  
  }
  pinMode(pinSW, INPUT_PULLUP);

  for(int i = 0; i < noOfDisplays; i++)
  {
    showDigit(i);
    if( i == dpSpot){
      dpState = HIGH;
    }
    else dpState = LOW;
    displayNumber(digitNumbers[i], dpState);
    delay(5);
  }
}

void loop() {

  for(int i = 0; i < noOfDisplays; i++)
  {
    showDigit(i);
    if( i == dpSpot){
      dpState = HIGH;
    }
    else dpState = LOW;
    displayNumber(digitNumbers[i], dpState);
    delay(5);
  }

  valueX = analogRead(pinX);
  valueY = analogRead(pinY);
  
  if(valueX > maxThreshold && joyMoved == false && verifyPush == 0){
    if(dpSpot < 3){
      dpSpot++;
      dpLastSpot++;
    }
    else{
      dpSpot = 0;
      dpLastSpot = 0;
    }
    joyMoved = true;
  }
  if(valueX < minThreshold && joyMoved == false && verifyPush == 0){
     if(dpSpot > 0){
      dpSpot--;
      dpLastSpot--;
    }
    else{
      dpSpot = 3;
      dpLastSpot = 3;
    }
    joyMoved = true;
  }
  if(valueX <= maxThreshold && valueX >= minThreshold && verifyPush == 0){
    joyMoved = false;    
  }
  if(valueY > maxThreshold && joyMoved == false && verifyPush == 1){
    if(digitNumbers[dpLastSpot] < 9){
      digitNumbers[dpLastSpot]++;
    }
    else digitNumbers[dpLastSpot] = 0;
    joyMoved = true;
  }
  if(valueY < minThreshold && joyMoved == false && verifyPush == 1){
    if(digitNumbers[dpLastSpot] > 0){
      digitNumbers[dpLastSpot]--;
    }
    else digitNumbers[dpLastSpot] = 9;
    joyMoved = true;
  }
  if(valueY <= maxThreshold && valueY >= minThreshold && verifyPush == 1){
    joyMoved = false;    
  }
  valueSW = digitalRead(pinSW);
  if(valueSW != lastValueSW && valueSW == LOW){
    verifyPush = !verifyPush;
    dpSpot = dpLastSpot;
  }
  lastValueSW = valueSW;

  currentTime = millis();
  delay(5);
}
