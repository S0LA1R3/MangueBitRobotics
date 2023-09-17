#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Inicializa com os valores padrÃµes(int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
#define BlackValue 50
#define SilverValue 150


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_300MS, TCS34725_GAIN_1X);

int pinoBlue = 9; //PINO DIGITAL UTILIZADO PELO TERMINAL VERMELHO
int pinoGreen = 10; //PINO DIGITAL UTILIZADO PELO TERMINAL VERDE
int pinoRed = 11; //PINO DIGITAL UTILIZADO PELO TERMINAL AZUL
uint16_t r, g, b, c, colorTemp, lux;

void setup(){
  Serial.begin(9600);

  pinMode(pinoBlue, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoGreen, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoRed, OUTPUT); //DEFINE O PINO COMO SAÍDA

}
void loop (){
  Serial.print("Vermelho : "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("Verde    : "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("Azul     : "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("Claridade: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.print("Black: "); Serial.print(BlackTileFound()); Serial.print(" ");
  Serial.print("Silver: "); Serial.print(SilverTileFound()); Serial.print(" ");
  Serial.print("Blue: "); Serial.print(BlueTileFound()); Serial.print(" ");
  Serial.println(" ");
}

void updateLight(){

  tcs.getRawData(&r, &g, &b, &c);

}

bool BlackTileFound(){
  updateLight();

  if(c < BlackValue){
    return true;
    
  }else{
    return false;
    
  }

}

bool SilverTileFound(){
  updateLight();

  if(c > SilverValue){
    return true;
    
  }else{
    return false;
    
  }

}

bool BlueTileFound(){
  updateLight();

  if(b > r && b > g){
    return true;
    
  }else{
    return false;
    
  }

}

