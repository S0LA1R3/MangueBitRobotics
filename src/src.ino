#include <Wire.h>
#include "graphElement.h"
#include "motor.h"
#include "mapping.h"
#include "sensorcor.h"
#include "mazeDFS.h"
#include "dispenser.h"
#include "led.h"
#include "button.h"

bool volta = false;

List<Point> checkpoints;
void check(){
  actualTile = checkpoints[-1];
}

void Frente(){
  while(degreesE <= 617){
    updateLight();
    if (BlackTileFound()){
      parar();
      mapa[actualTile.y][actualTile.x].setType(GraphElement::HOLE);
      Sinal(8);
      direita();
      direita();
      volta = true;
    }

    double Kp = 10;
    sonic = {readDistFrente(), readDistEsquerda(), readDistDireita()};
    int erro = sonic.E - sonic.D;
    int correcao = erro * Kp;

    if(correcao > 150){
      correcao = 0;
    }

    analogWrite(velocidadeA, int(abs(speed)) + correcao);
    analogWrite(velocidadeB, int(abs(speed)) - correcao);
    analogWrite(velocidadeC, int(abs(speed)) + correcao);
    analogWrite(velocidadeD, int(abs(speed)) - correcao);
    frente();
  }
}

void setup() {
  // Inicializa monitor serial
  Serial.begin(9600);

  int pushButtonP = 18;
  pinMode(pushButtonP, INPUT_PULLUP); // define o pino do botao como entrada
  attachInterrupt(digitalPinToInterrupt(pushButtonP), alternar, CHANGE);

  int pushButtonC = 19;
  pinMode(pushButtonC, INPUT_PULLUP); // define o pino do botao como entrada
  attachInterrupt(digitalPinToInterrupt(pushButtonC), check, CHANGE);

  s.attach(SERVO);
  s.write(0);

  Wire.begin(); // Inicia a comunicação I2C
  Wire.beginTransmission(MPU_addr); // Começa a transmissao de dados para o sensor
  Wire.write(0x6B); // Registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o MPU 6050
  Wire.endTransmission(true);

  pinMode(YELLOWD, INPUT);
  pinMode(BLUED, INPUT);
  degreesD = 0;

  pinMode(YELLOWE, INPUT);
  pinMode(BLUEE, INPUT);
  degreesE = 0;

  attachInterrupt(digitalPinToInterrupt(YELLOWD), countdegreesD, CHANGE);
  attachInterrupt(digitalPinToInterrupt(YELLOWE), countdegreesE, CHANGE);

  // Inicializa Pinos
  pinMode(velocidadeA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(velocidadeB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(velocidadeC, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);

  pinMode(velocidadeD, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);

  if(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
    Serial.println("Não foi possível encontrar um sensor MPU6050 válido, verifique a ligação!");
  }

  // Calibrar o giroscópio. A calibração deve estar em repouso.
  // Se você não quiser calibrar, comente esta linha.
  mpu.calibrateGyro();

  // Defina a sensibilidade do limite. Padrão 3.
  // Se você não quiser usar o limite, comente esta linha ou defina 0.
  mpu.setThreshold(1);

  // Inicializa GraphElements do mapa
  for (int i = 0; i < tamanhoMaximo; i++) {
    for (int j = 0; j < tamanhoMaximo; j++) {
      mapa[i][j] = GraphElement();
    }
  }
  tamanhoMapa++;

  mapa[actualTile.y][actualTile.x].setValue(0);
  mapa[actualTile.y][actualTile.x].setType(GraphElement::CHECKPOINT);

  for (int y = 0; y < tamanhoMaximo; y++) {
    List<GraphElement> row;
    for (int x = 0; x < tamanhoMaximo; x++) {
      row.push_back(graph[y][x]);
    }
    graph.push_back(row);
  }

  sonic = {readDistFrente(), readDistEsquerda(), readDistDireita()};
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
  mapa[actualTile.y + 1][actualTile.x].setValue(1);
}

void loop() {
  Serial.print("Frente: ");
  Serial.println(sonic.F);
  Serial.print("Direita: ");
  Serial.println(sonic.D);
  Serial.print("Esquerda: ");
  Serial.println(sonic.E);
  static long degD = 0;

  if (degD != degreesD) {
    Serial.print("degreesD: ");
    Serial.println(degreesD);
    degD = degreesD;
  }

  static long degE = 0;

  if (degE != degreesE) {
    Serial.print("degreesE: ");
    Serial.println(abs(degreesE));
    degE = degreesE;
  }

  updateLight();
  if (SilverTileFound()){
    mapa[actualTile.y][actualTile.x].setType(GraphElement::CHECKPOINT);
    checkpoints.push_back(actualTile);

  }else if (BlueTileFound()){
    mapa[actualTile.y][actualTile.x].setType(GraphElement::POOL);
    Sinal(9);
  }

  char visao = 6;

  // Verifica se o robô já chegou no próximo tile
    if (Serial.available()) {
      visao = Serial.read();
    }
      for(GraphElement element : findAdjacent(&mapa[actualTile.y][actualTile.x], graph, tamanhoMaximo)){
        if(element.getType() == GraphElement::VICTIM){
          visao = 6;
        }
      }
      if (visao != 6) {
        if (direction == N) {
          mapa[actualTile.y][actualTile.x - 1].setType(GraphElement::VICTIM);
        } else if (direction == S) {
          mapa[actualTile.y][actualTile.x + 1].setType(GraphElement::VICTIM);
        } else if (direction == D) {
          mapa[actualTile.y - 1][actualTile.x].setType(GraphElement::VICTIM);
        } else {
          mapa[actualTile.y + 1][actualTile.x].setType(GraphElement::VICTIM);
        }

        sonic = {readDistFrente(), readDistEsquerda(), readDistDireita()};
        if (sonic.E > 15) {
          esquerda();
          while (sonic.E > 15) {
            frente();
            sonic = {readDistFrente(), readDistEsquerda(), readDistDireita()};
            delay(1);
          }

          parar();
          direita();
        }

        if (visao == 0) {
          servo();
          servo();
          servo();
          Sinal(3);
        } else if (visao == 1) {
          servo();
          servo();
          Sinal(5);
        } else if (visao == 2) {
          Sinal(6);
        } else if (visao == 3) {
          servo();
          Sinal(1);
        } else if (visao == 4) {
          servo();
          Sinal(2);
        } else if (visao == 5) {
          Sinal(4);
        }
      }

      // Printa o mapa no monitor serial
      printMap();

      // Verifica para onde o robô deve ir (sequência padrão: F -> E -> D -> S)
      sonic = {readDistFrente(), readDistEsquerda(), readDistDireita()};
      if (!volta) {
        if (sonic.F < threshDist || (mapa[actualTile.y - 1][actualTile.x].getType() ==
                                     GraphElement::HOLE && direction == N) || (mapa[actualTile.y + 1][actualTile.x].getType() ==
                                     GraphElement::HOLE && direction == S) || (mapa[actualTile.y][actualTile.x + 1].getType() ==
                                     GraphElement::HOLE && direction == D) || (mapa[actualTile.y][actualTile.x - 1].getType() ==
                                     GraphElement::HOLE && direction == E)) {

          if (sonic.E < 15 || (mapa[actualTile.y][actualTile.x - 1].getType() ==
                               GraphElement::HOLE && direction == N) || (mapa[actualTile.y][actualTile.x + 1].getType() ==
                               GraphElement::HOLE && direction == S) || (mapa[actualTile.y - 1][actualTile.x].getType() ==
                               GraphElement::HOLE && direction == D) || (mapa[actualTile.y + 1][actualTile.x].getType() ==
                               GraphElement::HOLE && direction == E)) {

            if (sonic.D < 15 || (mapa[actualTile.y][actualTile.x + 1].getType() ==
                                 GraphElement::HOLE && direction == N) || (mapa[actualTile.y + 1][actualTile.x - 1].getType() ==
                                 GraphElement::HOLE && direction == S) || (mapa[actualTile.y - 1][actualTile.x].getType() ==
                                 GraphElement::HOLE && direction == D) || (mapa[actualTile.y + 1][actualTile.x].getType() ==
                                 GraphElement::HOLE && direction == E)) {

              direita();
              direita();
              Serial.println("fazendo a volta");

              Point shortestPlace = {99, 99};
              for (Point coord : getPlaces()) {
                if (abs(coord.x - actualTile.x) + abs(coord.y - actualTile.y) < shortestPlace.x + shortestPlace.y) {
                  shortestPlace = coord;
                }
              }

              if (getPlaces().empty()) {
                findPathDFS(actualTile, {tamanhoMaximo / 2, tamanhoMaximo / 2}, tamanhoMaximo, graph);
              } else {
                findPathDFS(actualTile, shortestPlace, tamanhoMaximo, graph);
              }

              volta = true;
            } else {
              direita();
              Serial.println("direita");
              Frente();
              Serial.println("frente");
              // Atualiza tiles adjacentes
              updateTile();
            }
          } else {
            esquerda();
            Serial.println("esquerda");
            Frente();
            Serial.println("frente");
            // Atualiza tiles adjacentes
            updateTile();
          }
        } else {
          Frente();
          Serial.println("frente");
          // Atualiza tiles adjacentes
          updateTile();
        }
      } else {
        for (Point coord : path) {
          if (&coord == &path[0]) {
            continue;
          } else if (actualTile.x - coord.x > 0) {
            if (direction == N) {
              esquerda();
              Frente();
            } else if (direction == S) {
              direita();
              Frente();
            } else if (direction == E) {
              Frente();
            } else if (direction == D) {
              esquerda();
              esquerda();
              Frente();
            }
          } else if (actualTile.x - coord.x < 0) {
            if (direction == N) {
              direita();
              Frente();
            } else if (direction == S) {
              esquerda();
              Frente();
            } else if (direction == E) {
              direita();
              direita();
              Frente();
            } else if (direction == D) {
              Frente();
            }
          } else if (actualTile.y - coord.y > 0) {
            if (direction == N) {
              Frente();
            } else if (direction == S) {
              direita();
              direita();
              Frente();
            } else if (direction == E) {
              direita();
              Frente();
            } else if (direction == D) {
              esquerda();
              Frente();
            }
          } else if (actualTile.y - coord.y < 0) {
            if (direction == N) {
              esquerda();
              esquerda();
              Frente();
            } else if (direction == S) {
              Frente();
            } else if (direction == E) {
              esquerda();
              Frente();
            } else if (direction == D) {
              direita();
              Frente();
            }
          }
          // Atualiza tiles adjacentes
          updateTile();
        }
      }
}
