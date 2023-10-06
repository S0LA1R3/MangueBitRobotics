#include <HCSR04.h>

//Define os pinos do Arduino D8 e D9 como porta do ECHO e TRIGGER  
#define TRIGGERF   30
#define ECHOF      31

#define TRIGGERE   32
#define ECHOE      33

#define TRIGGERD   34
#define ECHOD      35

// Inicializa o sensor usando os pinos TRIGGER and ECHO.
UltraSonicDistanceSensor distanceSensorF(TRIGGERF, ECHOF);
UltraSonicDistanceSensor distanceSensorE(TRIGGERE, ECHOE);
UltraSonicDistanceSensor distanceSensorD(TRIGGERD, ECHOD);
