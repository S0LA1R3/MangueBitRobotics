#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Inicializa com os valores padrÃµes(int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_300MS, TCS34725_GAIN_1X);

int pinoBlue = 9; //PINO DIGITAL UTILIZADO PELO TERMINAL VERMELHO
int pinoGreen = 10; //PINO DIGITAL UTILIZADO PELO TERMINAL VERDE
int pinoRed = 11; //PINO DIGITAL UTILIZADO PELO TERMINAL AZUL


void setup(){
  Serial.begin(9600);

  pinMode(pinoBlue, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoGreen, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoRed, OUTPUT); //DEFINE O PINO COMO SAÍDA

}
void loop (){

  uint16_t r, g, b, c;

  tcs.getRawData(&r, &g, &b, &c);

  if(r>255)
  {
    r = 255;
  }
  if(g>255)
  {
    g = 255;
  }
  if(b>255)
  {
    b = 255;
  }

  

  Serial.print("Vermelho : "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("Verde    : "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("Azul     : "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("Tile     : "); Serial.print(getTile(r, g, b));
  Serial.println(" ");
  
  if(r>g && r>b){
  analogWrite(pinoRed, 255); //PINO RECEBE O VALOR
  analogWrite(pinoBlue, 0); //PINO RECEBE O VALOR
  analogWrite(pinoGreen, 0); //PINO RECEBE O VALOR
  }
  else if(b < g && b < r){
  analogWrite(pinoRed, 0); //PINO RECEBE O VALOR
  analogWrite(pinoBlue, 255); //PINO RECEBE O VALOR
  analogWrite(pinoGreen, 0); //PINO RECEBE O VALOR
  }
  else{
  analogWrite(pinoRed, 0); //PINO RECEBE O VALOR
  analogWrite(pinoBlue, 0); //PINO RECEBE O VALOR
  analogWrite(pinoGreen, 255); //PINO RECEBE O VALOR
  }
  delay (10); //INTERVALO DE 10 MILISSEGUNDOS
}

char getTile(uint16_t r, uint16_t g, uint16_t b){
  
  uint16_t soma = r + g + b;
  char t;

  if(soma < 240)
  {
    t = "p";  
  } else if (b < g && b < r){
    t = "a";
  } else{
    t = "b";
  } 

  return t;

};

