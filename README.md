<div align="center" id="top"> 
  <img src="./public/ufrn.png" alt="UNO" width="8%"/>
  &#xa0;
</div>

<h1 align="center">Introdução às técnicas de programação - UNO</h1>
<h2 align="right">Pablo Deyvid de Paiva</h2>
<br>

<p align="center">
  <a href="#dart-sobre">Sobre</a> &#xa0; | &#xa0; 
  <a href="#sparkles-estrutura-do-código">Estrutura</a> &#xa0; | &#xa0;
  <a href="#sparkles-main">main.c</a> &#xa0; | &#xa0;
  <a href="#rocket-definitions">Definitions</a> &#xa0; | &#xa0;
  <a href="#joystick-helpers">Helpers</a> &#xa0; | &#xa0;
  <a href="#memo-license">License</a> &#xa0; | &#xa0;
  <a href="https://github.com/ITP-UFRN/UNO" target="_blank">GitHub</a>
</p>

<br>

## :dart: Sobre ##

Projeto prático apresentado à disciplina de Introdução às Técnicas de Programação do Bacharelado em Tecnologia da Informação da Universidade Federal do Rio Grande do Norte. Orientado pelo Prof. Dr. André Mauricio Campos.

O projeto tem como objetivo o desenvolvimento de um Bot em C capaz de jogar o jogo UNO.

## :sparkles: Estrutura do código ##

A estrutura basica do código conta com um arquivo principal main.c, as subpastas definitions e helpers. Além dos arquivos de compilação e de configuração.

<img align="center" src="./public/org-code.png" alt="UNO" width="50%"/>

A pasta definitions conta com os arquivos de definição .h que definem constantes, enums e structs.

<img align="center" src="./public/definitions.png" alt="UNO" width="50%"/>

<br>
Já a pasta helpers conta com arquivos que possuem a lógica do bot e seus arquivos de cabeçalho.

## :sparkles: main ##

O arquivo main.c inicialmente importa todas as dependências necessárias para sua execução.
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./definitions/constants.h"
#include "./definitions/suits.h"

#include "./helpers/handHelper.h"
#include "./helpers/printHelper.h"
#include "./helpers/creationHelper.h"
#include "./helpers/logicHelper.h"
```

Iniciando o código, os arquivos stdin, stdout e stderr tem seus buffer setados como NULL.
Logo após, é feita a definição das variáveis que guardarão o id do bot, os players, a mão em formato de string e a carta inicial do jogo em formato de string.

As primeiras leituras feitas são a dos players e o do id do bot.

Depois, a mão em formato de string é lida e convertida em um objeto do tipo HAND com o método createHand().

Logo após, a carta que representará a carta em cima da mesa é criada a partir da leitura de sua representação em string.

Em seguida, é criada a variável que representará a ação e também a o complemento da ação de outro jogador.

```c
int main()
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    char *myself = calloc(MAX_ID_SIZE, sizeof(char));
    char players[MAX_LINE];
    char handString[MAX_LINE];
    char initialTopTableString[MAX_LINE];

    scanf("PLAYERS %[^\n]\n", players);
    scanf("YOU %s\n", myself);

    scanf("HAND %[^\n]\n", handString);
    HAND *hand = createHand(handString);

    scanf("TABLE %s\n", initialTopTableString);
    CARD *topTable = createCard(initialTopTableString);

    char action[MAX_ACTION];
    char complement[MAX_LINE];
```
Por fim, a partida é iniciada. Dentro de um while infinito é lida a ação dos outros jogadores e depois é feita a ação do próprio bot.
```c
    while (1)
    {
        do
        {
            scanf("%s %s", action, complement);
            actionAnotherPlayer(action, topTable, complement);
        } while (strcmp(action, "TURN") || strcmp(complement, myself));
        myAction(topTable, hand);
    }

    return 0;
}
```

## :rocket: Definitions ##

## card.h
O primeiro arquivo de definição é o card.h, nele é contido a definição básica de uma carta, contendo o seu valor completo (número e naipe), além dos próprios número e naipe separados.
```h
#ifndef _CARD_
#define _CARD_
typedef struct{
    char *value;
    char *number;
    char *suit;
} CARD;
#endif
```

## constants.h
O arquivo constants.h contém a definição básica das constantes padrão do sistema já entregue pelo professor.
```h
#ifndef MAX_LINE
#define MAX_LINE 100
#endif

#ifndef MAX_ACTION
#define MAX_ACTION 10
#endif

#ifndef MAX_ID_SIZE
#define MAX_ID_SIZE 10
#endif
```

## field.h
O arquivo field.h conta com a definição de um enum que define os campos de uma carta.
```h
#ifndef _FIELDS_
#define _FIELDS_
typedef enum {
    VALUE,
    VALUE_OR,
    VALUE_AND,
    NUMBER,
    SUIT
} FIELD;
#endif
```

## hand.h
O arquivo hand.h define uma struct que representa uma mão (HAND), onde contém um array de ponteiros para CARD e um inteiro que representa a quantidade de cartas.
```h
#include "./card.h"

#ifndef _HAND_
#define _HAND_
typedef struct{
    CARD **cards;
    int amountCards;
} HAND;
#endif
```

## phrases.h
O arquivo phrases.h define frases aleatórias do filme O alto da Compadecida.
```h
#ifndef _PHRASES_
#define _PHRASES_
char *PHRASES[] = {
    "Não sei, só sei que foi assim!",
    "Matar padre dá um azar danado. Sobretudo para o padre.",
    "Valha-me Nossa Senhora, Mãe de Deus de Nazaré! A vaca mansa dá leite, a braba dá quando quer.",
    "Fui logo dizendo “I love you”, e ela se derreteu todinha. Quer dizer “morena” em francês.",
    "⁠Ô, promessa desgraçada. Ô, promessa sem jeito!",
    "Depois que morre, todo mundo fica bonzinho!",
    "O inferno vai terminar como disse Murilo: feito repartição pública, que existe, mas não funciona.",
    "Tá aí duas coisas que eu não sabia: uma que eu era corno, outra que defunto falava.",
    "Trair você era lhe matar um pouquinho dentro do meu coração.",
    "Já fui menino, fui homem, só me falta ser mulher."
};
#endif
```

## suits.h
Arquivo que define constantes que representam os naipes.
```h
#ifndef HEARTS_U
#define HEARTS_U "♥"
#endif

#ifndef DIAMONDS_U
#define DIAMONDS_U "♦"
#endif

#ifndef CLUBS_U
#define CLUBS_U "♣"
#endif

#ifndef SPADES_U
#define SPADES_U "♠"
#endif
```

## :joystick: Helpers ##

## printHelper

O primeiro e mais simples helper é o printHelper, onde o cabeçalho expõe apenas o método debug():
```h
void debug(char *);
```
O arquivo printHelper.c contém a implementação do método debug() já disponibilizado pelo professor, possuindo como parâmetro uma string que será impressa no stderr e sem retorno.
```c
#include <stdio.h>

void debug(char *message)
{
    fprintf(stderr, "%s\n", message);
}
```

## :memo: License ##

This project is under license from GLP. For more details, see the [LICENSE](LICENSE.md) file.


Feito com ❤️ por <a href="https://github.com/pablodeyvid11" target="_blank">Pablo Deyvid</a>
&#xa0;

<a href="#top">Voltar ao início</a>
