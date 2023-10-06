//Motores esquerdos

#define ENL1 1
#define O1L1 2
#define O2L1 3

#define ENL2 4
#define O1L2 5
#define O2L2 6

//Motores direitos

#define ENR1 7
#define O1R1 8
#define O2R1 9

#define ENR2 10
#define O1R2 11
#define O2R2 12

int speed = 100;

void setup() {
  Serial.begin(9600);

  pinMode(ENL1, OUTPUT);
  pinMode(O1L1, OUTPUT);
  pinMode(O2L1, OUTPUT);

  pinMode(ENL2, OUTPUT);
  pinMode(O1L2, OUTPUT);
  pinMode(O2L2, OUTPUT);

  pinMode(ENR1, OUTPUT);
  pinMode(O1R1, OUTPUT);
  pinMode(O2R1, OUTPUT);

  pinMode(ENR2, OUTPUT);
  pinMode(O1R2, OUTPUT);
  pinMode(O2R2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  goFoward(speed);
}

void goForward(int speed) {
  LMotorSpeed(speed);
  RMotorSpeed(speed);
}

void turnLeft(int speed) {
  speed = abs(speed);
  LMotorSpeed(speed);
  RMotorSpeed(-speed);
}

void turnRight(int speed) {
  speed = abs(speed);
  LMotorSpeed(-speed);
  RMotorSpeed(speed);
}

void stop(){
  LMotorSpeed(0);
  RMotorSpeed(0);
}


void LMotorSpeed(int speed) {
  if (speed > 100)
    speed = 100;
  if (speed < -100)
    speed = -100;

  analogWrite(ENL1, int(abs(speed)*2.55));

  if(speed > 0){
    digitalWrite(01L1, HIGH);
    digitalWrite(02L1, LOW);
    
  }else{
    digitalWrite(01L1, LOW);
    digitalWrite(02L1, HIGH);
  }
}

void RMotorSpeed(int speed) {
  if (speed > 100)
    speed = 100;
    
  if (speed < -100)
    speed = -100;

  analogWrite(ENR1, int(abs(speed)*2.55));

  if(speed > 0){
    digitalWrite(01R1, HIGH);
    digitalWrite(02R1, LOW);
    
  }else{
    digitalWrite(01R1, LOW);
    digitalWrite(02R1, HIGH);
  }
}
