#include <Servo.h>

#define SERVO 8 // Porta Digital 6 PWM

Servo s; // Variável Servo
int pos; // Posição Servo

void servo() {
  for (pos = 0; pos < 180; pos++) {
    s.write(pos);
    delay(25);
  }
  for (pos = 180; pos >= 0; pos--) {
    s.write(pos);
    delay(25);
  }
}
