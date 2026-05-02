#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <stdbool.h>

#define LARGURA 800
#define ALTURA 600
#define LINHAS 5
#define COLUNAS 10
#define LARGURA_BLOCO 70
#define ALTURA_BLOCO 25
#define MAX_SCORES 5

typedef struct {
    float x, y;
    float dx, dy;
    float raio;
} Ball;

typedef struct {
    float x, y;
    float largura, altura;
    float velocidade;
} Paddle;

typedef struct {
    Rectangle rect;
    bool ativo;
    Color cor;
} Bloco;

typedef struct node {
    int pontuacao;
    struct node *next;
} ScoreNode;

// protótipos
void iniciarBola(Ball *ball, Paddle *paddle);
void moverBola(Ball *ball, Paddle *paddle, Bloco blocos[][COLUNAS], int *pontos, bool *ganhou);
void moverPaddle(Paddle *paddle);
void gerarBlocos(Bloco blocos[][COLUNAS]);
void desenharJogo(Ball *ball, Paddle *paddle, Bloco blocos[][COLUNAS], int pontos);

#endif