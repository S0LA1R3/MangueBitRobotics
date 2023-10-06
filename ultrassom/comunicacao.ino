#include <HCSR04.h>

//Define os pinos do Arduino D8 e D9 como porta do ECHO e TRIGGER  
#define TRIGGER   6
#define ECHO      7

// Inicializa o sensor usando os pinos TRIGGER and ECHO.
UltraSonicDistanceSensor distanceSensor(TRIGGER, ECHO);  

void setup () {
  //Inicializa a porta serial do Arduino com 9600 de baud rate
    Serial.begin(9600);  
}

void loop () {
    //Cria variavel do tipo int
    int distancia = 0;
    
    //Variável recebe o valor da função da biblioteca
    distancia = distanceSensor.measureDistanceCm();
    
    //exibe na porta serial o valor de distancia medido
    Serial.println(distancia);
    
    //Espera 1 segundo
    delay(1000);
}