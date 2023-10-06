#define YELLOW 2

#define BLUE 6

volatile long degrees;

void countDegrees(){
  if(digitalRead(YELLOW) == digitalRead(BLUE)){
  degrees++;
  
  }else{
    degrees--;
  }
}

void setup(){
  Serial.begin(9600);
  while(Serial);
  
  pinMode(YELLOW, INPUT);
  pinMode(BLUE, INPUT);
  
  degrees = 0;
  
  attachInterrupt( digitalPinToInterrupt(YELLOW), countDegrees, CHANGE);
}

void loop() {
  static long deg = 0;

  if(deg != degrees){
    Serial.print("Degrees: ");
    Serial.println(degrees);
    deg = degrees;
  }
}
