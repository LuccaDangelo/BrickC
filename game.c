#include "game.h"
#include <stdlib.h>
#include <time.h>

void iniciarBola(Ball *ball, Paddle *paddle) {
    ball->x = paddle->x + paddle->largura / 2;
    ball->y = paddle->y - 10;
    ball->dx = 4;
    ball->dy = -4;
    ball->raio = 8;
}

void moverPaddle(Paddle *paddle) {
    if (IsKeyDown(KEY_LEFT) && paddle->x > 0)
        paddle->x -= paddle->velocidade;
    if (IsKeyDown(KEY_RIGHT) && paddle->x + paddle->largura < LARGURA)
        paddle->x += paddle->velocidade;
}

void gerarBlocos(Bloco blocos[][COLUNAS]) {
    srand(time(NULL));
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            blocos[i][j].ativo = (rand() % 10) < 8;
            blocos[i][j].rect = (Rectangle){
                j * (LARGURA_BLOCO + 5) + 15,
                i * (ALTURA_BLOCO + 5) + 50,
                LARGURA_BLOCO,
                ALTURA_BLOCO
            };
            blocos[i][j].cor = WHITE;
        }
    }
}

void moverBola(Ball *ball, Paddle *paddle, Bloco blocos[][COLUNAS], int *pontos, bool *ganhou) {
    ball->x += ball->dx;
    ball->y += ball->dy;

    // colisão com paredes laterais
    if (ball->x - ball->raio <= 0 || ball->x + ball->raio >= LARGURA)
        ball->dx = -ball->dx;

    // colisão com teto
    if (ball->y - ball->raio <= 0)
        ball->dy = -ball->dy;

    // colisão com paddle
    Rectangle rectPaddle = { paddle->x, paddle->y, paddle->largura, paddle->altura };
    if (CheckCollisionCircleRec((Vector2){ball->x, ball->y}, ball->raio, rectPaddle))
        ball->dy = -ball->dy;

    // colisão com blocos
    int ativos = 0;
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (blocos[i][j].ativo) {
                ativos++;
                if (CheckCollisionCircleRec((Vector2){ball->x, ball->y}, ball->raio, blocos[i][j].rect)) {
                    blocos[i][j].ativo = false;
                    ball->dy = -ball->dy;
                    *pontos += 10;
                }
            }
        }
    }

    if (ativos == 0) *ganhou = true;
}

void desenharJogo(Ball *ball, Paddle *paddle, Bloco blocos[][COLUNAS], int pontos) {
    // paddle
    DrawRectangle(paddle->x, paddle->y, paddle->largura, paddle->altura, WHITE);

    // bola
    DrawCircle(ball->x, ball->y, ball->raio, WHITE);

    // blocos
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            if (blocos[i][j].ativo)
                DrawRectangleRec(blocos[i][j].rect, WHITE);

    // pontuação
    DrawText(TextFormat("Pontos: %d", pontos), 10, 10, 20, WHITE);
}