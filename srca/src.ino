#include <Wire.h>
#include "ultrassom.h"
#include "graphElement.hpp"
#include "motor.h"

// Distância mínima robô-parede
int threshDist = 10;

// Inicializa o mapa com tamanhoMaximo linhas e colunas
const int tamanhoMaximo = 10; // Tamanho máximo da lista
GraphElement mapa[tamanhoMaximo][tamanhoMaximo];

// Variável usada para inicializar os GraphElements do mapa
int tamanhoMapa = 0;

// Estrutura coordenada
struct Point {
    int y, x;
};

// Tile inicial (meio do mapa)
Point actualTile = {tamanhoMaximo / 2 - 1, tamanhoMaximo / 2 - 1};

// Estrutura com as proximidades das paredes
struct Sonic {
    int F, E, D;
};

// Inicializa sonic
Sonic sonic = {readDistFrente(), readDistEsquerda(), readDistDireita()};


void updateTile() {
  mapa[actualTile.y][actualTile.x].setValue(0);

    if (direction == N) {
        actualTile.y--;

        if (sonic.F < threshDist) {
            mapa[actualTile.y - 1][actualTile.x].setValue(1);
        }

        if (sonic.E < threshDist) {
            mapa[actualTile.y][actualTile.x - 1].setValue(1);
        }

        if (sonic.D < threshDist) {
            mapa[actualTile.y][actualTile.x + 1].setValue(1);
        }

    } else if (direction == S) {
        actualTile.y++;

        if (sonic.F < threshDist) {
            mapa[actualTile.y + 1][actualTile.x].setValue(1);
        }

        if (sonic.E < threshDist) {
            mapa[actualTile.y][actualTile.x + 1].setValue(1);
        }

        if (sonic.D < threshDist) {
            mapa[actualTile.y][actualTile.x - 1].setValue(1);
        }

    } else if (direction == D) {
        actualTile.x++;

        if (sonic.F < threshDist) {
            mapa[actualTile.y][actualTile.x + 1].setValue(1);
        }

        if (sonic.E < threshDist) {
            mapa[actualTile.y - 1][actualTile.x].setValue(1);
        }

        if (sonic.D < threshDist) {
            mapa[actualTile.y + 1][actualTile.x].setValue(1);
        }

    } else {
        actualTile.x--;

        if (sonic.F < threshDist) {
            mapa[actualTile.y][actualTile.x - 1].setValue(1);
        }

        if (sonic.E < threshDist) {
            mapa[actualTile.y + 1][actualTile.x].setValue(1);
        }

        if (sonic.D < threshDist) {
            mapa[actualTile.y - 1][actualTile.x + 1].setValue(1);
        }
    }
}

bool printMap() {
    for (GraphElement linha[tamanhoMaximo] : mapa) {
        for (GraphElement elemento : linha) {
            Serial.print(elemento.getValue());
            Serial.print(" ");
        }
        Serial.println();
    }
}

void setup() {
    // Inicializa monitor serial
    Serial.begin(9600);

    Wire.begin(); // Inicia a comunicação I2C
  Wire.beginTransmission(MPU_addr); // Começa a transmissao de dados para o sensor
  Wire.write(0x6B); // Registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o MPU 6050
  Wire.endTransmission(true);
  
    mapa[actualTile.y][actualTile.x].setValue(0);
    
    pinMode(YELLOW, INPUT);
    pinMode(BLUE, INPUT);
    degrees = 0;
    
    attachInterrupt(digitalPinToInterrupt(YELLOW), countDegrees, CHANGE);

    // Inicializa Pinos
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

    // robô inicia indo para frente
    frente();

    // Inicializa GraphElements do mapa
    for (int i = 0; i < tamanhoMaximo; i++) {
        for (int j = 0; j < tamanhoMaximo; j++) {
            mapa[i][j] = GraphElement();
        }
    }
    tamanhoMapa++;

    // coloca paredes e caminhos adjacentes ao tile inicial no mapa
    if (sonic.F < threshDist) {
        mapa[actualTile.y - 1][actualTile.x].setValue(1);
    }

    if (sonic.E < threshDist) {
        mapa[actualTile.y][actualTile.x - 1].setValue(1);
    }

    if (sonic.D < threshDist) {
        mapa[actualTile.y][actualTile.x + 1].setValue(1);
    }
}

bool finish = false;
static long deg;

void loop() {
  deg = 0;

  if(deg != degrees){
    Serial.print("Degrees: ");
    Serial.println(degrees);
    deg = degrees;
  }
    char c = 6;
    // encoder medindo os giros até chegar no próximo tile, quando chega bota a variável tile em true

    // Verifica se o robô já chegou no próximo tile
    if(degrees >= 614){
        Serial.print("Frente: ");
        Serial.println(sonic.F);
        Serial.print("Esquerda: ");
        Serial.println(sonic.E);
        Serial.print("Direita: ");
        Serial.println("sonic.E");

        if(Serial.available()){
            c = Serial.read();
        }
        if(true){
            if(c != 6){
              if (direction == N) {
                  mapa[actualTile.y][actualTile.x + 1].setType(GraphElement::VICTIM);

              } else if (direction == S) {
                  mapa[actualTile.y][actualTile.x - 1].setType(GraphElement::VICTIM);

              } else if (direction == D) {
                  mapa[actualTile.y + 1][actualTile.x].setType(GraphElement::VICTIM);

              } else {
                  mapa[actualTile.y - 1][actualTile.x].setType(GraphElement::VICTIM);
              }
            }
            // Atualiza tiles adjacentes
            updateTile();

            // Printa o mapa no monitor serial
            finish = printMap();

            // Verifica para onde o robô deve ir (sequência padrão: F -> E -> D -> S)
            sonic = {readDistFrente(), readDistEsquerda(), readDistDireita()};
            if (sonic.F < threshDist) {
                if (sonic.E < 15) {
                    if (sonic.D < 15) {
                        direita();
                        direita();
                        Serial.println("fazendo a volta");
                    } else {
                        direita();
                        Serial.println("direita");
                    }
                } else {
                    esquerda();
                    Serial.println("esquerda");
                }
            } else {
                frente();
                Serial.println("frente");
            }
            if (static_cast<int>(direction) == 4) {
                direction = N;
            }
          }
      }
      degrees = 0;
}
