#define YELLOWE 3
#define BLUEE 24
#define YELLOWD 2
#define BLUED 25

// motor_A
int IN1 = 49; // TE
int IN2 = 48;
int velocidadeA = 6;

// motor_B
int IN3 = 47; // TD
int IN4 = 46;
int velocidadeB = 7;

// motor_C
int IN5 = 53; // FE
int IN6 = 52;
int velocidadeC = 5;

// motor_D
int IN7 = 51; // FD
int IN8 = 50;
int velocidadeD = 4;

int speed = 150;

volatile long degreesD;
volatile long degreesE;

void countdegreesD(){
  if(digitalRead(YELLOWD) == digitalRead(BLUED)){
    degreesD++;
  
  }else{
    degreesD--;
  }
}

void countdegreesE(){
  if(digitalRead(YELLOWE) == digitalRead(BLUEE)){
    degreesE++;
  
  }else{
    degreesE--;
  }
}

void frente() {
    digitalWrite(IN1, LOW); // EF
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, LOW); // ET
    digitalWrite(IN4, HIGH);

    digitalWrite(IN5, HIGH); // DF
    digitalWrite(IN6, LOW);

    digitalWrite(IN7, HIGH); // DT
    digitalWrite(IN8, LOW);

    analogWrite(velocidadeA, int(abs(speed)));
    analogWrite(velocidadeB, int(abs(speed)));
    analogWrite(velocidadeC, int(abs(speed)));
    analogWrite(velocidadeD, int(abs(speed)));
}

void direita() {
    digitalWrite(IN1, LOW); // EF
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, LOW); // ET
    digitalWrite(IN4, HIGH);

    digitalWrite(IN5, LOW); // DF
    digitalWrite(IN6, LOW);

    digitalWrite(IN7, LOW); // DT
    digitalWrite(IN8, LOW);

    analogWrite(velocidadeA, int(abs(speed)));
    analogWrite(velocidadeB, int(abs(speed)));
    analogWrite(velocidadeC, int(abs(speed)));
    analogWrite(velocidadeD, int(abs(speed)));

}

void esquerda() {

    digitalWrite(IN1, LOW); // EF
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW); // ET
    digitalWrite(IN4, LOW);

    digitalWrite(IN5, HIGH); // DF
    digitalWrite(IN6, LOW);

    digitalWrite(IN7, HIGH); // DT
    digitalWrite(IN8, LOW);

    analogWrite(velocidadeA, int(abs(speed)));
    analogWrite(velocidadeB, int(abs(speed)));
    analogWrite(velocidadeC, int(abs(speed)));
    analogWrite(velocidadeD, int(abs(speed)));

}

void parar() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, LOW);
}

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(velocidadeA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(velocidadeB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
 	pinMode(19, OUTPUT);
  	pinMode(18, OUTPUT);
  	pinMode(17, OUTPUT);
  	pinMode(16, OUTPUT);
    pinMode(velocidadeC, OUTPUT);             
    pinMode(IN5, OUTPUT);
    pinMode(IN6, OUTPUT);

    pinMode(velocidadeD, OUTPUT);
    pinMode(IN7, OUTPUT);
    pinMode(IN8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    frente();

  static long degD = 0;

  if (degD != degreesD) {
    Serial.print("degreesD: ");
    Serial.println(degreesD);
    degD = degreesD;
  }

  static long degE = 0;

  if (degE != degreesE) {
    Serial.print("degreesE: ");
    Serial.println(abs(degreesE));
    degE = degreesE;
  }
}
