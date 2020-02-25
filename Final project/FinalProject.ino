//pins
const int trigPin = 9;
const int echoPin = 10;
const int buzzPin = 11;
const int ledPin = 3;

//variables 
long duration;
int distance;
int safetyDistance;


void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
}

void loop() {
  //Clearing the trigPin
  digitalWrite(trigPin, LOW);
  delay(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);  

  //Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  //Calculating the distance
  distance = duration*0.034/2;

  safetyDistance = distance;

  //I took a safetyDistance of 10 cm
  if (safetyDistance <= 10){
    digitalWrite(buzzPin, HIGH);
    digitalWrite(ledPin, LOW);
  }
  else{   
    digitalWrite(buzzPin, LOW);
    digitalWrite(ledPin, HIGH);
  }
  
}
