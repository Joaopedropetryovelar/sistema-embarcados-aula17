///Definir os apelidos do pino
#define led_LIB 8
#define led_LOT 9
#define led_VER 10
#define pin_botao1 2
#define pin_botao2 3
#define pin_botao3 4

//contadores
int cont = 0;
int tic1 = 0;
int tic2 = 0;

void setup() {
  //define os leds como uma saída
  pinMode(led_LIB, OUTPUT);
  pinMode(led_LOT, OUTPUT);
  pinMode(led_VER, OUTPUT);
 
 //define os botões como uma entrada
  pinMode(pin_botao1, INPUT);
  pinMode(pin_botao2, INPUT);
  pinMode(pin_botao3, INPUT);
  
  //inicia uma comunicação com o arduino
  Serial.begin(9600);


}

void loop() {
  // Faz a leitura dos botões, armazenando o valor (1 = pressionado, 0 = não pressionado)
bool SEV = digitalRead(pin_botao1); // Botão de entrada (SEV) — carro entrou
bool SSV = digitalRead(pin_botao2); // Botão de saída (SSV) — carro saiu
bool BOT = digitalRead(pin_botao3); // Botão de reset (BOT) — zera a contagem

// Exibe no monitor serial o valor atual do contador
Serial.println(cont);

// Se o botão de entrada (SEV) for pressionado, o controle (tic1) estiver liberado
// e o estacionamento NÃO estiver cheio (cont < 10), então soma +1 no contador
if (SEV == 1 && tic1 == 0 && cont < 10) {
  cont += 1;   // Incrementa a quantidade de carros
  tic1 += 1;   // Bloqueia até soltar o botão (evita múltiplas contagens)
}

// Quando solta o botão SEV, libera novamente tic1 para a próxima leitura
if (SEV == 0) {
  tic1 = 0;
}

// Se o botão de saída (SSV) for pressionado, tic2 estiver liberado
// e houver pelo menos 1 carro no estacionamento (cont > 0), então subtrai -1
if (SSV == 1 && tic2 == 0 && cont > 0) {
  cont -= 1;   // Decrementa a quantidade de carros
  tic2 += 1;   // Bloqueia até soltar o botão (evita múltiplas contagens)
}

// Quando solta o botão SSV, libera novamente tic2 para a próxima leitura
if (SSV == 0) {
  tic2 = 0;
}

// Se o contador chegar a 10, acende o LED de lotado (led_LOT) e apaga o de livre
if (cont == 10) {
  digitalWrite(led_LOT, HIGH); // LED de lotado aceso
  digitalWrite(led_LIB, LOW);  // LED de livre apagado
} else {
  digitalWrite(led_LOT, LOW);  // LED de lotado apagado quando não está cheio
}

// Se o contador for menor que 10, acende o LED de livre (led_LIB)
if (cont < 10) {
  digitalWrite(led_LIB, HIGH); // LED de livre aceso
  digitalWrite(led_LOT, LOW);  // LED de lotado apagado
} else {
  digitalWrite(led_LIB, LOW);  // LED de livre apagado quando estiver cheio
}

// Se o contador for 0, acende o LED de verificação (led_VER) para o operador conferir
if (cont == 0) {
  digitalWrite(led_VER, HIGH); // LED de verificação aceso
  digitalWrite(led_LOT, LOW);  // LED de lotado apagado
} else {
  digitalWrite(led_VER, LOW);  // LED de verificação apagado se houver carros
}

// Se o botão BOT for pressionado, o contador volta para zero, zerando tudo
if (BOT == 1) {
  cont = 0;

}
}
