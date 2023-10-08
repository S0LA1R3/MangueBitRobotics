#define YELLOW 2
#define BLUE 30

const int MPU_addr = 0x68; // Endereço do sensor
int16_t GyZ;

// Direções absolutas do robô
enum Direction {
    N,
    D,
    S,
    E
};

// Direção absoluta padrão
Direction direction = N;

// motor_A
int IN1 = 46;
int IN2 = 47;
int velocidadeA = 7;

// motor_B
int IN3 = 48;
int IN4 = 49;
int velocidadeB = 6;

// motor_C
int IN5 = 50;
int IN6 = 51;
int velocidadeC = 5;

// motor_D
int IN7 = 52;
int IN8 = 53;
int velocidadeD = 4;

int speed = 255;

volatile long degrees;

void countDegrees(){
  if(digitalRead(YELLOW) == digitalRead(BLUE)){
  degrees++;
  
  }else{
    degrees--;
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
  Wire.beginTransmission(MPU_addr); // Começa a transmissao de dados para o sensor
  Wire.write(0x3B); // Registrador dos dados medidos (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14,true);

  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  int16_t copiaZ = GyZ;

  while(abs(copiaZ - GyZ) < 90){
    // Muda direção absoluta
    direction = static_cast<Direction>(static_cast<int>(direction) + 1);

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
  Wire.beginTransmission(MPU_addr); // Começa a transmissao de dados para o sensor
  Wire.write(0x3B); // Registrador dos dados medidos (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);

  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  int16_t copiaZ = GyZ;

  while(abs(copiaZ - GyZ) < 90){
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
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, LOW);
}
