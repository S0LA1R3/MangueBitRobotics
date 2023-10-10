#include "mpu.h"

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
    direction = static_cast<Direction>(static_cast<int>(direction) + 1);
    if (static_cast<int>(direction) == 4) {
      direction = N;
    }

    // Lê valores normalizados
    Vector normGyro = mpu.readNormalizeGyro();

    // Ignore o giroscópio se nossa velocidade angular não atingir nosso limite
    if (normGyro.ZAxis > 1 || normGyro.ZAxis < -1) {
        normGyro.ZAxis /= 1;
        yaw += normGyro.ZAxis;
    }

    // Mantenha nosso ângulo entre 0-359 graus
    while(yaw <= 270) {
      Serial.print("yaw: ");
      Serial.println(yaw);
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
}

void esquerda() {
    // Muda direção absoluta
    direction = static_cast<Direction>(static_cast<int>(direction) + 1);
    if (static_cast<int>(direction) == 4) {
      direction = N;
    }

    // Lê valores normalizados
    Vector normGyro = mpu.readNormalizeGyro();

    // Ignore o giroscópio se nossa velocidade angular não atingir nosso limite
    if (normGyro.ZAxis > 1 || normGyro.ZAxis < -1) {
        normGyro.ZAxis /= 1;
        yaw += normGyro.ZAxis;
    }

    // Mantenha nosso ângulo entre 0-359 graus
    while(yaw >= 90) {
      Serial.print("yaw: ");
      Serial.println(yaw);
        // Muda direção absoluta
        direction = static_cast<Direction>(static_cast<int>(direction) - 1);

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
z