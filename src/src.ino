#include "ultrassom.h"

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

int threshDist = 10;

enum Direction{
	N,
	D,
	S,
	E
}

//Inicializa Pinos
void setup() {
  Serial.begin(9600);

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

}

void loop(){
  Direction direction = N;
  int distEsquerda = readDistEsquerda();
  int distDireita = readDistDireita();
  int distFrente = readDistFrente();

  if(distFrente < threshDist){

    if(distEsquerda < threshDist){

      if(distDireita < threshDist){
        direita();
        direita();

      }else{
        direita();
        Serial.print("direita: ");
        Serial.println(distDireita);
      }

    }else{
        esquerda();
        Serial.print("esquerda: ");
        Serial.println(distEsquerda);
    }
  }else{
    frente();
    Serial.print("frente: ");
    Serial.println(distFrente);
  }
  delay(2000);
}

void frente(){

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

void direita(){
	direction++;

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

void esquerda(){
	direction--;

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

void parar(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(IN5,LOW);
  digitalWrite(IN6,LOW);
  digitalWrite(IN7,LOW);
  digitalWrite(IN8,LOW);
}

int readDistFrente(){
  // Cria variavel do tipo int
  int distancia = 0;
    
  // Variável recebe o valor da função da biblioteca
  distancia = distanceSensorF.measureDistanceCm();
    
  // Exibe na porta serial o valor de distancia medido
    
  return distancia;
}

int readDistDireita(){

  // Cria variavel do tipo int
  int distancia = 0;
    
  // Variável recebe o valor da função da biblioteca
  distancia = distanceSensorD.measureDistanceCm();
    
  // Exibe na porta serial o valor de distancia medido
    
  return distancia;
}

int readDistEsquerda(){
  // Cria variavel do tipo int
  int distancia = 0;
    
  // Variável recebe o valor da função da biblioteca
  distancia = distanceSensorE.measureDistanceCm();
    
  // Exibe na porta serial o valor de distancia medido

  return distancia;
}
