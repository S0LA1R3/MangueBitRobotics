
// motor_A
int IN1 = 49;
int IN2 = 48;
int velocidadeA = 7;

// motor_B
int IN3 = 47;
int IN4 = 46;
int velocidadeB = 6;

// motor_C
int IN5 = 53;
int IN6 = 52;
int velocidadeC = 5;

// motor_D
int IN7 = 51;
int IN8 = 50;
int velocidadeD = 4;

int speed = 255;

void setup(){

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


void loop(){
	frente();
}
