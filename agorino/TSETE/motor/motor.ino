#define YELLOWE 3
#define BLUEE 44
#define YELLOWD 2
#define BLUED 45

const int MPU_addr = 0x68; // Endereço do sensor
int16_t GyZ;

// Direções absolutas do robô
enum Direction {
    N,
    D,
    S,
    E
};

enum Estado{
  PARADO,
  ANDANDO
};

Estado estado = PARADO;

// Direção absoluta padrão
Direction direction = N;

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

void countdegreesD() {
    if (digitalRead(YELLOWD) == digitalRead(BLUED)) {
        degreesD++;

    } else {
        degreesD--;
    }
}

void countdegreesE() {
    if (digitalRead(YELLOWE) == digitalRead(BLUEE)) {
        degreesE++;

    } else {
        degreesE--;
    }
}

void frente() {
  estado = ANDANDO;

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
    // Muda direção absoluta
    if (static_cast<int>(direction) == 4) {
      direction = N;
    }else{
      direction = static_cast<Direction>(static_cast<int>(direction) + 1);
    }

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
    // Muda direção absoluta
    if (static_cast<int>(direction) == 0) {
      direction = E;
    }else{
        direction = static_cast<Direction>(static_cast<int>(direction) - 1);
    }

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
  estado = PARADO;

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, LOW);
}

void alternar(){
  if(estado == ANDANDO){
    parar();
  }else{
    frente();
  }
}

void setup(){
  Serial.begin(9600);

  pinMode(YELLOWD, INPUT);
  pinMode(BLUED, INPUT);
  degreesD = 0;

  pinMode(YELLOWE, INPUT);
  pinMode(BLUEE, INPUT);
  degreesE = 0;

  attachInterrupt(digitalPinToInterrupt(YELLOWD), countdegreesD, CHANGE);
  attachInterrupt(digitalPinToInterrupt(YELLOWE), countdegreesE, CHANGE);

  // Inicializa Pinos
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

void loop(){
  Serial.print("Direção: ");
  Serial.println(direction);
  
  Serial.print("Estado: ");
  Serial.println(estado);

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
