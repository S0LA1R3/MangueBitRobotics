//motor_A
int IN1 = 22 ;
int IN2 = 23 ;
int velocidadeA = 2;

//motor_B
int IN3 = 24 ;
int IN4 = 25 ;
int velocidadeB = 3;

//motor_C
int IN5 = 26;
int IN6 = 27;
int velocidadeC = 4;
//motor_D
int IN7 = 28;
int IN8 = 29;
int velocidadeD = 5;

int speed = 255;

bool liga = false;
int Switch = 22;

void setup() {

  pinMode(velocidadeA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(velocidadeB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(velocidadeC, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);

  pinMode(velocidadeD, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);

  pinMode(Switch, INPUT);

}

void loop() {

  digitalWrite(IN1, LOW); // EF
  digitalWrite(IN2, HIGH);
      
  digitalWrite(IN3, LOW); // ET
  digitalWrite(IN4, HIGH);
  
  digitalWrite(IN5, HIGH); // DF
  digitalWrite(IN6, LOW);
  
  digitalWrite(IN7, HIGH); // DT
  digitalWrite(IN8, LOW);
      
  analogWrite(velocidadeA, int(abs(speed)));
  analogWrite(velocidadeB, int(abs(speed)));,
  analogWrite(velocidadeC, int(abs(speed)));
  analogWrite(velocidadeD, int(abs(speed)))
  
}
