#include <HCSR04.h>

#define TRIGGERF 27
#define ECHOF 26

#define TRIGGERD 27
#define ECHOD 26

#define TRIGGERE 29
#define ECHOE 28

// Inicializa o sensor usando os pinos TRIGGER and ECHO.
UltraSonicDistanceSensor distanceSensorF(TRIGGERF, ECHOF);
UltraSonicDistanceSensor distanceSensorE(TRIGGERE, ECHOE);
UltraSonicDistanceSensor distanceSensorD(TRIGGERD, ECHOD);

// Distância mínima robô-parede
int threshDist = 10;

int readDistFrente() {
  int distancia = 0;

  // Variável recebe o valor da função da biblioteca
  distancia = distanceSensorF.measureDistanceCm();

  return distancia;
}

int readDistDireita() {
  int distancia = 0;

  // Variável recebe o valor da função da biblioteca
  distancia = distanceSensorD.measureDistanceCm();

  return distancia;
}

int readDistEsquerda() {
  int distancia = 0;

  // Variável recebe o valor da função da biblioteca
  distancia = distanceSensorE.measureDistanceCm();

  return distancia;
}
