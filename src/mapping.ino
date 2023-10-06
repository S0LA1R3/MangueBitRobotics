#include "graphElement.hpp"

const int tamanhoMaximo = 10; // Tamanho máximo da lista
GraphElement mapa[tamanhoMaximo][tamanhoMaximo];

struct Point {
    int y, x;
};

Point actualTile = {tamanhoMaximo / 2 - 1, tamanhoMaximo / 2 - 1};

int tamanhoMapa = 0;

void setup() {
    Serial.begin(9600);
    // Adicione objetos às listas usando o construtor com argumento
    for (int i = 0; i < tamanhoMaximo; i++) {
        for (int j = 0; j < tamanhoMaximo; j++) {
            mapa[tamanhoMaximo][tamanhoMaximo] = GraphElement();
        }
    }
    tamanhoMapa++;

    if (distFrente < threshDist) {
        mapa[actualTile.y - 1][actualTile.x].setValue(1);
    }

    if (distEsquerda < threshDist) {
        mapa[actualTile.y][actualTile.x - 1].setValue(1);
    }

    if (distDireita < threshDist) {
        mapa[actualTile.y][actualTile.x + 1].setValue(1);
    }
}

void loop() {
    if (nextTile) {
      updateTile();
    }
}

void updateTile(){
  if(direction == N){
    actualTile.y--;

    if (distFrente < threshDist) {
        mapa[actualTile.y - 1][actualTile.x].setValue(1);
    }

    if (distEsquerda < threshDist) {
        mapa[actualTile.y][actualTile.x - 1].setValue(1);
    }

    if (distDireita < threshDist) {
        mapa[actualTile.y][actualTile.x + 1].setValue(1);
    }
    
  }else if(direction == S){
    actualTile.y++;

    if (distFrente < threshDist) {
        mapa[actualTile.y + 1][actualTile.x].setValue(1);
    }

    if (distEsquerda < threshDist) {
        mapa[actualTile.y][actualTile.x + 1].setValue(1);
    }

    if (distDireita < threshDist) {
        mapa[actualTile.y][actualTile.x - 1].setValue(1);
    }
    
  }else if(direction == D){
    actualTile.x++;

    if (distFrente < threshDist) {
        mapa[actualTile.y][actualTile.x + 1].setValue(1);
    }

    if (distEsquerda < threshDist) {
        mapa[actualTile.y - 1][actualTile.x].setValue(1);
    }

    if (distDireita < threshDist) {
        mapa[actualTile.y + 1][actualTile.x].setValue(1);
    }
    
  }else{
    actualTile.x--;

    if (distFrente < threshDist) {
        mapa[actualTile.y][actualTile.x - 1].setValue(1);
    }

    if (distEsquerda < threshDist) {
        mapa[actualTile.y + 1][actualTile.x].setValue(1);
    }

    if (distDireita < threshDist) {
        mapa[actualTile.y - 1][actualTile.x + 1].setValue(1);
    }
  }
}
