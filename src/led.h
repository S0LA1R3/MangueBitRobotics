/*void setup() {
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);
}*/

void Sinal(int sinal){
  switch(sinal){
    // vitima vermelha
    case 1:
      Serial.println("Vítima Vermelha");
      digitalWrite(30, HIGH);
      delay(5000);
      digitalWrite(30, LOW);
      break;
    // vitima amarela
    case 2:
      Serial.println("Vítima Amarela");
      digitalWrite(31, HIGH);
      delay(5000);
      digitalWrite(31, LOW);
      break;
    // vitima H
    case 3:
      Serial.println("Vítima H");
      digitalWrite(30, HIGH);
      digitalWrite(31, HIGH);
      delay(5000);
      digitalWrite(30, LOW);
      digitalWrite(31, LOW);
      break;
    // vitima verde
    case 4:
      Serial.println("Vítima Verde");
      digitalWrite(32, HIGH);
      delay(5000);
      digitalWrite(32, LOW);
      break;
    // vitima S
    case 5:
      Serial.println("Vítima S");
      digitalWrite(30, HIGH);
      digitalWrite(32, HIGH);
      delay(5000);
      digitalWrite(30, LOW);
      digitalWrite(32, LOW);
      break;
    // vitima U
    case 6:
      Serial.println("Vítima U");
      digitalWrite(31, HIGH);
      digitalWrite(32, HIGH);
      delay(5000);
      digitalWrite(31, LOW);
      digitalWrite(32, LOW);
      break;
    // checkpoint
    case 7:
      Serial.println("CheckPoint");
      digitalWrite(30, HIGH);
      digitalWrite(31, HIGH);
      digitalWrite(32, HIGH);
      delay(5000);
      digitalWrite(30, LOW);
      digitalWrite(31, LOW);
      digitalWrite(32, LOW);
      break;
    // buraco
    case 8:
      Serial.println("Buraco");
      digitalWrite(33, HIGH);
      delay(5000);
      digitalWrite(33, LOW);
      break;
    // azul
    case 9:
      Serial.println("Tile Azul");
      digitalWrite(30, HIGH);
      digitalWrite(33, HIGH);
      delay(5000);
      digitalWrite(30, LOW);
      digitalWrite(33, LOW);
      break;
    default:
      Serial.println("NADA!");
      digitalWrite(33, LOW);
      digitalWrite(32, LOW);
      digitalWrite(31, LOW);
      digitalWrite(30, LOW);
      break;
  }
}
