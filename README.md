
# Troco

## Sobre o Troco

* É um jogo pvp

* O jogo deve ser executado no Arduino.

* Desenvolvido no Wokwi

### Material necessário:

* 5 LEDs coloridos (2-2-1)

* 5 botões 

* 1 protoboard

* 1 placa Arduino

* +/_ 20 cabos de conexão

* Sugestão de simulador Wokwi (https://wokwi.com/)

 ## FORMA DE JOGAR

*  O jogo Troco é feito por rodadas.
 
* Cada rodada tem duas etapas: desafio e troco.
 
* Cada jogador possui dois botões que ligam seus LEDs correspondentes. (BOTAO_2 e BOTAO3 para LED_2 e LED_3; BOTAO_5 e BOTAO_6 para LED_5 e LED_6).
 
* No início de cada etapa, LEDs piscarão para indicar o respectivo jogador que deve jogar.

* O jogador iniciante da rodada deve criar um DESAFIO apertando seus botões e criando uma sequencia de ativações dos LEDs (máximo 20; valor pode ser alterado nas variáveis).
 
* No final de cada jogada, o jogador deve apertar o botão de finalizar jogada (BOTAO_4).

* Após a jogada de DESAFIO o jogador adversário de REPETIR a sequência do adversário mas com as cores invertidas. Exemplo: Desafio de Verde, Verde, Vermelho deve ser repetida Vermelho, Vermelho, Verde.

* A segunda etapa de cada rodada é o TROCO. 

* O jogador que respondeu o desafio agora é o desafiador e deve criar um desafio com o mesmo número de ativações do desafiante anterior mas pode usar uma sequencia de cores diferente.

* Errar faz o jogador atual perder 1 pontos e acertar faz o jogador adversário perder 2 pontos. 

* O primeiro jogador que ficar com zero pontos (0) perde.

# EXEMPLO DE JOGO 

## RODADA 1

### DESAFIO

* jogador 1 criar sequencia (até 20).

* jogador 2 repete a sequencia com cores invertidas.

### TROCO

* jogador 2 cria sequencia no mesmo número ações da sequencia anterior do jogador adversário.

* jogador 1 repete a sequencia com cores invertidas.

## RODADA 2

### DESAFIO

* jogador 2 cria sequencia (até 20)
...
