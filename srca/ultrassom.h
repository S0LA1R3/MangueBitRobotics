#include <HCSR04.h>

//Define os pinos do Arduino D8 e D9 como porta do ECHO e TRIGGER  
#define TRIGGERD   32
#define ECHOD      33

#define TRIGGERE   34
#define ECHOE      35

#define TRIGGERF   36
#define ECHOF      37

// Inicializa o sensor usando os pinos TRIGGER and ECHO.
UltraSonicDistanceSensor distanceSensorF(TRIGGERF, ECHOF);
UltraSonicDistanceSensor distanceSensorE(TRIGGERE, ECHOE);
UltraSonicDistanceSensor distanceSensorD(TRIGGERD, ECHOD);

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

