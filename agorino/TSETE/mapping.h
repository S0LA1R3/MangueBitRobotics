#include <EEPROM.h>
#include "ultrassom.h"
#include "point.h"
#include "List.h"

// Estrutura com as proximidades das paredes
struct Sonic {
  int F, E, D;
};

// Variável usada para inicializar os GraphElements do mapa
int tamanhoMapa = 0;

// Inicializa o mapa com tamanhoMaximo linhas e colunas
const int tamanhoMaximo = 10; // Tamanho máximo da lista
GraphElement mapa[tamanhoMaximo][tamanhoMaximo];
List<List<GraphElement>> graph;

// Tile inicial (meio do mapa)
Point actualTile = {tamanhoMaximo / 2 - 1, tamanhoMaximo / 2 - 1};

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
  for (int y = 0; y < tamanhoMaximo; y++) {
    for (int x = 0; x < tamanhoMaximo; x++) {
      if (mapa[y][x].getValue() != 2) {
        Serial.print(mapa[y][x].getValue());
      } else {
        Serial.print(" ");
      }
      Serial.print(" ");
    }
    Serial.println();
  }
}

List<Point> getPlaces() {
  List<Point> places;
  for (int y = 0; y < tamanhoMaximo; y++) {
    for (int x = 0; x < tamanhoMaximo; x++) {
      if (y == 0 && x == 0) {
        if (mapa[y + 1][x].getValue() == 2 || mapa[y][x + 1].getValue() == 2)
          places.push_back({y, x});
      } else if (y == 0 && x == tamanhoMaximo) {
        if (mapa[y + 1][x].getValue() == 2 || mapa[y][x - 1].getValue() == 2)
          places.push_back({y, x});
      } else if (y == tamanhoMaximo && x == 0) {
        if (mapa[y - 1][x].getValue() == 2 || mapa[y][x + 1].getValue() == 2)
          places.push_back({y, x});
      } else if (y == tamanhoMaximo && x == tamanhoMaximo) {
        if (mapa[y - 1][x].getValue() == 2 || mapa[y][x - 1].getValue() == 2)
          places.push_back({y, x});
      } else {
        if (mapa[y + 1][x].getValue() == 2 || mapa[y][x + 1].getValue() == 2 ||
            mapa[y - 1][x].getValue() == 2 || mapa[y][x - 1].getValue() == 2)
          places.push_back({y, x});
      }
    }
  }
}

void upload() {
  for (int y = 0; y < tamanhoMaximo; y++) {
    for (int x = 0; x < tamanhoMaximo; x++) {
      if (mapa[y][x].getType() == GraphElement::VICTIM &&
          mapa[y][x].getValue() == 0) {
        EEPROM.write(0, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::VICTIM &&
          mapa[y][x].getValue() == 1) {
        EEPROM.write(1, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::VICTIM &&
          mapa[y][x].getValue() == 2) {
        EEPROM.write(2, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::POOL &&
          mapa[y][x].getValue() == 0) {
        EEPROM.write(3, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::POOL &&
          mapa[y][x].getValue() == 1) {
        EEPROM.write(4, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::POOL &&
          mapa[y][x].getValue() == 2) {
        EEPROM.write(5, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::CHECKPOINT &&
          mapa[y][x].getValue() == 0) {
        EEPROM.write(6, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::CHECKPOINT &&
          mapa[y][x].getValue() == 1) {
        EEPROM.write(7, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::CHECKPOINT &&
          mapa[y][x].getValue() == 2) {
        EEPROM.write(8, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::HOLE &&
          mapa[y][x].getValue() == 0) {
        EEPROM.write(9, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::HOLE &&
          mapa[y][x].getValue() == 1) {
        EEPROM.write(10, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::HOLE &&
          mapa[y][x].getValue() == 2) {
        EEPROM.write(11, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::LEVELCHANGE &&
          mapa[y][x].getValue() == 0) {
        EEPROM.write(12, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::LEVELCHANGE &&
          mapa[y][x].getValue() == 1) {
        EEPROM.write(13, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::LEVELCHANGE &&
          mapa[y][x].getValue() == 2) {
        EEPROM.write(14, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::PADRAO &&
          mapa[y][x].getValue() == 0) {
        EEPROM.write(15, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::PADRAO &&
          mapa[y][x].getValue() == 1) {
        EEPROM.write(16, y * 10 + x);
      }
      if (mapa[y][x].getType() == GraphElement::PADRAO &&
          mapa[y][x].getValue() == 2) {
        EEPROM.write(17, y * 10 + x);
      }
    }
  }
}

List<List<GraphElement>> download() {
  List<List<GraphElement>> data;
  GraphElement mapa[tamanhoMaximo][tamanhoMaximo];
  for (int y = 0; y < tamanhoMaximo; y++) {
    for (int x = 0; x < tamanhoMaximo; x++) {
      if (EEPROM.read(y * 10 + x) == 0) {
        mapa[y][x] = GraphElement(0, GraphElement::VICTIM);
      } else if (EEPROM.read(y * 10 + x) == 1) {
        mapa[y][x] = GraphElement(1, GraphElement::VICTIM);
      } else if (EEPROM.read(y * 10 + x) == 2) {
        mapa[y][x] = GraphElement(2, GraphElement::VICTIM);
      } else if (EEPROM.read(y * 10 + x) == 0) {
        mapa[y][x] = GraphElement(0, GraphElement::POOL);
      } else if (EEPROM.read(y * 10 + x) == 1) {
        mapa[y][x] = GraphElement(1, GraphElement::POOL);
      } else if (EEPROM.read(y * 10 + x) == 2) {
        mapa[y][x] = GraphElement(2, GraphElement::POOL);
      } else if (EEPROM.read(y * 10 + x) == 0) {
        mapa[y][x] = GraphElement(0, GraphElement::CHECKPOINT);
      } else if (EEPROM.read(y * 10 + x) == 1) {
        mapa[y][x] = GraphElement(1, GraphElement::CHECKPOINT);
      } else if (EEPROM.read(y * 10 + x) == 2) {
        mapa[y][x] = GraphElement(2, GraphElement::CHECKPOINT);
      } else if (EEPROM.read(y * 10 + x) == 0) {
        mapa[y][x] = GraphElement(0, GraphElement::HOLE);
      } else if (EEPROM.read(y * 10 + x) == 1) {
        mapa[y][x] = GraphElement(1, GraphElement::HOLE);
      } else if (EEPROM.read(y * 10 + x) == 2) {
        mapa[y][x] = GraphElement(2, GraphElement::HOLE);
      } else if (EEPROM.read(y * 10 + x) == 0) {
        mapa[y][x] = GraphElement(0, GraphElement::LEVELCHANGE);
      } else if (EEPROM.read(y * 10 + x) == 1) {
        mapa[y][x] = GraphElement(1, GraphElement::LEVELCHANGE);
      } else if (EEPROM.read(y * 10 + x) == 2) {
        mapa[y][x] = GraphElement(2, GraphElement::LEVELCHANGE);
      } else if (EEPROM.read(y * 10 + x) == 0) {
        mapa[y][x] = GraphElement(0, GraphElement::PADRAO);
      } else if (EEPROM.read(y * 10 + x) == 1) {
        mapa[y][x] = GraphElement(1, GraphElement::PADRAO);
      } else if (EEPROM.read(y * 10 + x) == 2) {
        mapa[y][x] = GraphElement(2, GraphElement::PADRAO);
      }
    }
  }
}
