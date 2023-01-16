
/*-----TROCO-----*/

// Regras no final do código.

// DEFINIÇÕES
#define LED_2 2 //Vermelho para Jogador 1
#define LED_3 3 //Verde para Jogador 1
#define LED_4 4 //Amarelo 
#define LED_5 5 //Vermelho para Jogador 2
#define LED_6 6 //Verde para Jogador 2

#define BOTAO_2 8 //para o LED Vermelho do Jogador 1
#define BOTAO_3 9 //para o LED Verde so Jogador 1
#define BOTAO_4 10 //Amarelo
#define BOTAO_5 11 //para o LED Vermelho do Jogador 2
#define BOTAO_6 12 //para o LED Verde so Jogador 2

// VARIÁVEIS

int pontoInicial = 7; // Aumentar pontosInicial dá mais pontos a cada jogador no inicio da partida.
int pontosPlayer1 = pontoInicial;
int pontosPlayer2 = pontoInicial;
enum Etapas {GERAR_RODADA, TROCO, PLAYER_1_JOGANDO, PLAYER_2_JOGANDO, VITORIA};
int vinganca = 1;
int numerodarodada = 1;
int jogador = 1;
int etapa = -1;
int momento = 0;
// Alterar sequencia/sequenciaRepeticao/sequenciaDesafio (todos com mesmo valor) muda o limite máximo de repetições das sequências.
int sequencia = 20;
int sequenciaRepeticao[20];
int sequenciaDesafio[20];
int c1 = 0;
int c2 = 0;
int i = 0;

void setup() {
  Serial.begin(9600);
  Serial.println(">Partida iniciada<");
  Serial.print("\n");
  Serial.print("Pondos do Jogador 1 = ");
  Serial.println(pontosPlayer1);
  Serial.print("Pondos do Jogador 2 = ");
  Serial.println(pontosPlayer2);
  Serial.print("\r\n");
  //Serial.print("\n");
  iniciaPortas();
  delay(1000);
}
void loop() {
  switch (etapaAtual()) {
    case GERAR_RODADA:
      momento = 1;
      delay(500);
      Serial.print("---> RODADA ");
      Serial.print(numerodarodada);
      Serial.print("\r\n");
      Serial.print("\n");
      numerodarodada++;
      zeraLista();
      break;

    case PLAYER_1_JOGANDO:
      ativaLedJogador(LED_2, LED_3);
      if (etapa == -1) {
        etapa = 1;
        Serial.println("Jogador 1, faça o seu desafio!!!");
        Serial.print("\n");
        desafioJogada();
        jogador = 2;
        break;
      }
      else if (etapa == 1) {
        Serial.println("Jogador 1, digite a mesma sequência usando cores opostas!!!");
        Serial.print("\n");
        etapa = -1;
        repeteJogada();
        break;
      }
    case PLAYER_2_JOGANDO:
      ativaLedJogador(LED_5, LED_6);
      if (etapa == -1) {
        etapa = 1;
        Serial.println("Jogador 2, faça o seu desafio!!!");
        Serial.print("\n");
        desafioJogada();
        jogador = 1;
        break;
      }
      else if (etapa == 1) {
        Serial.println("Jogador 2, digite a mesma sequência usando cores opostas!!!");
        Serial.print("\n");
        etapa = -1;
        repeteJogada();
        break;
      }
    case TROCO:
      if (vinganca == 1) {
        contaPontos();
        if (pontosPlayer1 > 0 && pontosPlayer2 > 0) {

          Serial.print("----!!!TROCO!!!----");
          Serial.print("\r\n");
          Serial.print("\n");
          Serial.print("Faça uma sequência de: ");
          Serial.print(i);
          Serial.print("\r\n");
          Serial.print("\n");
        }
        zeraLista();
        momento = 1;
        vinganca = 2;
        break;
      }
      else if (vinganca == 2) {
        contaPontos();
        momento = 0;
        c1 = 0;
        c2 = 0;
        vinganca = 1;
        zeraLista();
        if (jogador == 1) {
          jogador = 2;
          break;
        }
        else if (jogador == 2) {
          jogador = 1;
          break;
        }
      }
    case VITORIA:
      
      if (pontosPlayer1 <= 0) {
        Serial.println("----Vitória do Jogador 2----");
        delay(500);
        ativaLedVitoria(LED_2,LED_3,LED_6,LED_5);
        exit(0);
      }
      if (pontosPlayer2 <= 0) {
        Serial.println("----Vitória do Jogador 1----");
        delay(500);
        ativaLedVitoria(LED_2,LED_3,LED_6,LED_5);
        exit(0);
      }
      break;
  }
}

//--------FUNÇÕES----------

//-----ETAPA ATUAL-----

int etapaAtual() {
  if (pontosPlayer1 > 0 && pontosPlayer2 > 0 && momento == 0) {
    return GERAR_RODADA;
  }
  else if (pontosPlayer1 > 0 && pontosPlayer2 > 0 && jogador == 1  && momento == 1) {
    return PLAYER_1_JOGANDO;
  }
  else if (pontosPlayer1 > 0 && pontosPlayer2 > 0 && jogador == 2  && momento == 1) {
    return PLAYER_2_JOGANDO;
  }
  else if (pontosPlayer1 > 0 && pontosPlayer2 > 0 && momento == 2) {
    return TROCO;
  }
  else if (pontosPlayer1 <= 0) {
    return VITORIA;
  }
  else if (pontosPlayer2 <= 0) {
    return VITORIA;
  }
}

//-----DESAFIO-----

void desafioJogada() {

  if (vinganca == 1) {
    desafioNormal();
  }

  if (vinganca == 2) {
    desafioVinganca();
  }


}
void desafioNormal() {
  i = 0;
  int x = 0;

  if (jogador == 1) {
    while (x == 0 and i < sequencia) {
      if (digitalRead(BOTAO_2) == LOW) {
        sequenciaDesafio[i] = 1;
        //Serial.println("Vermelho");
        ativaLedRapido(LED_2);
        i++;
        c1++;
        while (digitalRead(BOTAO_2) == LOW) {}
      }
      if (digitalRead(BOTAO_3) == LOW) {
        sequenciaDesafio[i] = 2;
        //Serial.println("Verde");
        ativaLedRapido(LED_3);
        i++;
        c1++;
        while (digitalRead(BOTAO_3) == LOW) {}
      }
      if (digitalRead(BOTAO_4) == LOW) {
        ativaLedRapido(LED_4);
        Serial.print("Sequência de ");
        Serial.print(i);
        Serial.print("\r\n");
        Serial.print("\n");
        x = 1;
        while (digitalRead(BOTAO_4) == LOW) {}
      }
    }
  }

  else if (jogador == 2) {
    while (x == 0 and i < sequencia) {
      if (digitalRead(BOTAO_5) == LOW) {
        sequenciaDesafio[i] = 1;
        //Serial.println("Vermelho");
        ativaLedRapido(LED_5);
        i++;
        c2++;
        while (digitalRead(BOTAO_5) == LOW) {}
      }
      if (digitalRead(BOTAO_6) == LOW) {
        sequenciaDesafio[i] = 2;
        //Serial.println("Verde");
        ativaLedRapido(LED_6);
        i++;
        c2++;
        while (digitalRead(BOTAO_6) == LOW) {}
      }
      if (digitalRead(BOTAO_4) == LOW) {
        ativaLedRapido(LED_4);
        Serial.print("Sequência de ");
        Serial.print(i);
        Serial.print("\r\n");
        Serial.print("\n");
        x = 1;
        while (digitalRead(BOTAO_4) == LOW) {}
      }
    }
  }
}
void desafioVinganca() {
  i = 0;
  int x = 0;
  //Serial.println(c2);
  //Serial.println(c1);
  if (jogador == 1) {
    while (x == 0) {
      while (i < c2) {
        if (digitalRead(BOTAO_2) == LOW) {
          sequenciaDesafio[i] = 1;
          //Serial.println("Vermelho");
          ativaLedRapido(LED_2);
          i++;
          while (digitalRead(BOTAO_2) == LOW) {}
        }
        if (digitalRead(BOTAO_3) == LOW) {
          sequenciaDesafio[i] = 2;
          //Serial.println("Verde");
          ativaLedRapido(LED_3);
          i++;
          while (digitalRead(BOTAO_3) == LOW) {}
        }
      }
      if (digitalRead(BOTAO_4) == LOW) {
        ativaLedRapido(LED_4);
        Serial.print("Sequência de ");
        Serial.print(i);
        //Serial.print(" cores");
        Serial.print("\r\n");
        Serial.print("\n");
        x = 1;
        while (digitalRead(BOTAO_4) == LOW) {}
      }
    }
  }
  else if (jogador == 2) {
    while (x == 0) {
      while (i < c1) {
        if (digitalRead(BOTAO_5) == LOW) {
          sequenciaDesafio[i] = 1;
          //Serial.println("Vermelho");
          ativaLedRapido(LED_5);
          i++;
          while (digitalRead(BOTAO_5) == LOW) {}
        }
        if (digitalRead(BOTAO_6) == LOW) {
          sequenciaDesafio[i] = 2;
          //Serial.println("Verde");
          ativaLedRapido(LED_6);
          i++;
          while (digitalRead(BOTAO_6) == LOW) {}
        }
      }
      if (digitalRead(BOTAO_4) == LOW) {
        ativaLedRapido(LED_4);
        Serial.print("Sequência de ");
        Serial.print(i);
        Serial.print("\r\n");
        Serial.print("\n");
        x = 1;
        while (digitalRead(BOTAO_4) == LOW) {}
      }
    }
  }
}

//-----REPETIÇÃO-----

void repeteJogada() {
  int r = 0;
  int x = 0;
  if (jogador == 2) {
    while (x == 0) {
      if (digitalRead(BOTAO_5) == LOW) {
        sequenciaRepeticao[r] = 2;
        //Serial.println("Vermelho");
        //Serial.println(sequenciaRepeticao[r]);
        ativaLedRapido(LED_5);
        r++;
        while (digitalRead(BOTAO_5) == LOW) {}
      }
      if (digitalRead(BOTAO_6) == LOW) {
        sequenciaRepeticao[r] = 1;
        //Serial.println("Verde");
        //Serial.println(sequenciaRepeticao[r]);
        ativaLedRapido(LED_6);
        r++;
        while (digitalRead(BOTAO_6) == LOW) {}
      }
      if (digitalRead(BOTAO_4) == LOW) {
        ativaLedRapido(LED_4);
        Serial.print("Sequência de ");
        Serial.print(r);
        //Serial.print(" cores");
        Serial.print("\r\n");
        Serial.print("\n");
        x = 1;
        while (digitalRead(BOTAO_4) == LOW) {}
      }
    }
  }

  else if (jogador == 1) {
    while (x == 0) {
      if (digitalRead(BOTAO_2) == LOW) {
        sequenciaRepeticao[r] = 2;
        //Serial.println("Vermelho");
        //Serial.println(sequenciaRepeticao[r]);
        ativaLedRapido(LED_2);
        r++;
        while (digitalRead(BOTAO_2) == LOW) {}
      }
      if (digitalRead(BOTAO_3) == LOW) {
        sequenciaRepeticao[r] = 1;
        //Serial.println("Verde");
        //Serial.println(sequenciaRepeticao[r]);
        ativaLedRapido(LED_3);
        r++;
        while (digitalRead(BOTAO_3) == LOW) {}
      }
      if (digitalRead(BOTAO_4) == LOW) {
        ativaLedRapido(LED_4);
        Serial.print("Sequência de ");
        Serial.print(r);
        //Serial.print(" cores");
        Serial.print("\r\n");
        Serial.print("\n");
        x = 1;
        while (digitalRead(BOTAO_4) == LOW) {}
      }
    }
  }
  momento++;
}

void iniciaPortas() {
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);

  pinMode(BOTAO_2, INPUT_PULLUP);
  pinMode(BOTAO_3, INPUT_PULLUP);
  pinMode(BOTAO_4, INPUT_PULLUP);
  pinMode(BOTAO_5, INPUT_PULLUP);
  pinMode(BOTAO_6, INPUT_PULLUP);
}

//----ZERA LISTAS DAS SEQUÊNCIAS----
void zeraLista() {
  for (int z = 0; z < sequencia; z++) {
    sequenciaRepeticao[z] = 0;
    sequenciaDesafio[z] = 0;
  }
}

//----CONTAGEM DE PONTOS----
void contaPontos() {
  int contador = 0;
  for (int k = 0; k < sequencia; k++) {
    if (sequenciaDesafio[k] != sequenciaRepeticao[k]) {
      contador++;
    }
  }
  if (jogador == 1) {
    if (contador == 0) {
      pontosPlayer2 = pontosPlayer2 - 2;
      Serial.println("> Jogador 1 acertou! Jogador 2 perde 2 pontos");
    }
    else {
      pontosPlayer1 = pontosPlayer1 - 1;
      Serial.println("> Jogador 1 errou! Jogador 1 perde 1 pontos");
    }
  }
  if (jogador == 2) {
    if (contador == 0) {
      pontosPlayer1 = pontosPlayer1 - 2;
      Serial.println("> Jogador 2 acertou! Jogador 1 perde 2 pontos");
    }
    else {
      pontosPlayer2 = pontosPlayer2 - 1;
      Serial.println("> Jogador 2 errou! Jogador 2 perde 1 pontos");
    }
  }
  if (pontosPlayer1 < 0) {
    pontosPlayer1 = 0;
  }
  if (pontosPlayer2 < 0) {
    pontosPlayer2 = 0;
  }
  Serial.print("Pondos do Jogador 1 = ");
  Serial.println(pontosPlayer1);
  Serial.print("Pondos do Jogador 2 = ");
  Serial.println(pontosPlayer2);
  Serial.print("\r\n");
  //Serial.print("\n");
  contador = 0;
}

//Ativação de LEDs
void ativaLedRapido(int portaLed) {
  digitalWrite(portaLed, HIGH);
  delay(50);
  digitalWrite(portaLed, LOW);
  delay(50);
}
void ativaLedJogador(int portaLed1, int portaLed2) {
  digitalWrite(portaLed1, HIGH);
  digitalWrite(portaLed2, HIGH);
  delay(500);
  digitalWrite(portaLed1, LOW);
  digitalWrite(portaLed2, LOW);
  delay(200);
  digitalWrite(portaLed1, HIGH);
  digitalWrite(portaLed2, HIGH);
  delay(500);
  digitalWrite(portaLed1, LOW);
  digitalWrite(portaLed2, LOW);
}
void ativaLedVitoria(int portaLed1, int portaLed2, int portaLed3, int portaLed4) {
  for (int d = 0; d < 5; d++) {

    digitalWrite(portaLed1, HIGH);
    delay(300);
    digitalWrite(portaLed1, LOW);
    digitalWrite(portaLed2, HIGH);
    delay(300);
    digitalWrite(portaLed2, LOW);
    digitalWrite(portaLed3, HIGH);
    delay(300);
    digitalWrite(portaLed3, LOW);
    digitalWrite(portaLed4, HIGH);
    delay(300);
    digitalWrite(portaLed4, LOW);
  }
}

/* ---FORMA DE JOGAR---

> O jogo Troco é feito por rodadas.

> Cada rodada tem duas etapas: desafio e troco.

> Cada jogador possui dois botões que ligam seus LEDs correspondentes. (BOTAO_2 e BOTAO3 para LED_2 e LED_3; BOTAO_5 e BOTAO_6 para LED_5 e LED_6)

> No início de cada etapa, LEDs piscarão para indicar o respectivo jogador que deve jogar.

> O jogador iniciante da rodada deve criar um DESAFIO apertando seus botões e criando uma sequencia de ativações dos LEDs (máximo 20; valor pode ser alterado nas variáveis).

> No final de cada jogada, o jogador deve apertar o botão de finalizar jogada (BOTAO_4).

> Após a jogada de DESAFIO o jogador adversário de REPETIR a sequência do adversário mas com as cores invertidas. Exemplo: Desafio de Verde, Verde, Vermelho deve ser repetida Vermelho, Vermelho, Verde.

> A segunda etapa de cada rodada é o TROCO. 

> O jogador que respondeu o desafio agora é o desafiador e deve criar um desafio com o mesmo número de ativações do desafiante anterior mas pode usar uma sequencia de cores diferente.

> Errar faz o jogador atual perder 2 pontos e acertar faz o jogador adversário perder 2 pontos. 

> O primeiro jogador que ficar com zero pontos (0) perde.

  >>  EXEMPLO DE JOGO  <<

--RODADA 1--

>DESAFIO
jogador 1 criar sequencia (até 20)/
jogador 2 repete a sequencia com cores invertidas/

>TROCO
jogador 2 cria sequencia no mesmo número ações da sequencia anterior do jogador adversário/
jogador 1 repete a sequencia com cores invertidas/

--RODADA 2--

>DESAFIO/
jogador 2 cria sequencia (até 20)
...

*/