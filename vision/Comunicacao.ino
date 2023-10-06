void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial com a taxa de 9600 bps
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    Serial.print(c); // Imprime o caractere recebido
  }
}
