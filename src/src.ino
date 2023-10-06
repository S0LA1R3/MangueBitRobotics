#include "ultrassom.h"
#include "graphElement.hpp"

// motor_A
int IN1 = 22 ;
int IN2 = 23 ;
int velocidadeA = 2;

// motor_B
int IN3 = 24 ;
int IN4 = 25 ;
int velocidadeB = 3;

// motor_C
int IN5 = 26;
int IN6 = 27;
int velocidadeC = 4;

// motor_D
int IN7 = 28;
int IN8 = 29;
int velocidadeD = 5;

int speed = 255;

// Distância mínima robô-parede
int threshDist = 10;

// Direções absolutas do robô
enum Direction{
    N,
    D,
    S,
    E
};

// Direção absoluta padrão
Direction direction = N;

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
Sonic sonic(readDistFrente, readDistEsquerda, readDistDireita);

// Usado para indicar que o encoder detectou a chegada em um novo tile
bool tile = false;

void setup() {
    // Inicializa monitor serial
    Serial.begin(9600);

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
            mapa[tamanhoMaximo][tamanhoMaximo] = GraphElement();
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

void loop() {
    // encoder medindo os giros até chegar no próximo tile, quando chega bota a variável tile em true

    // Verifica se o robô já chegou no próximo tile
    if (tile) {
        // Atualiza tiles adjacentes
        updateTile();

        // Printa o mapa no monitor serial
        printMap();

        // Verifica para onde o robô deve ir (sequência padrão: F -> E -> D -> S)
        if (sonic.F < threshDist) {

            if (sonic.E < threshDist) {

                if (sonic.D < threshDist) {
                    direita();
                    direita();
                    Serial.print("fazendo a volta");

                } else {
                    direita();
                    Serial.print("direita: ");
                    Serial.println(sonic.D);
                }

            } else {
                esquerda();
                Serial.print("esquerda: ");
                Serial.println(sonic.E);
            }
        } else {
            frente();
            Serial.print("frente: ");
            Serial.println(sonic.F);
        }
    }
}

void frente() {

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

void direita() {
    // Muda direção absoluta
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

void esquerda() {
    // Muda direção absoluta
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

void parar() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, LOW);
}

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

void updateTile() {
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

void printMap() {
    for (GraphElement linha[] : mapa) {
        for (GraphElement elemento : linha) {
            Serial.print(element.getValue());
            Serial.print(" ");
        }
        Serial.println();
    }
}
