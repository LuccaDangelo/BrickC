#include <raylib.h>
#include <stdbool.h>
#include "game.h"
#include "score.h"

int main() {
    InitWindow(LARGURA, ALTURA, "BrickC");
    SetTargetFPS(60);

    Ball ball;
    Paddle paddle = { LARGURA / 2 - 50, ALTURA - 40, 100, 15, 6 };
    Bloco blocos[LINHAS][COLUNAS];

    int pontos = 0;
    bool lancou = false;
    bool ganhou = false;
    bool perdeu = false;

    gerarBlocos(blocos);
    iniciarBola(&ball, &paddle);

    while (!WindowShouldClose()) {

        // input
        if (!lancou && IsKeyPressed(KEY_SPACE)) {
            lancou = true;
        }

        if (!perdeu && !ganhou) {
            moverPaddle(&paddle);

            if (lancou) {
                moverBola(&ball, &paddle, blocos, &pontos, &ganhou);
            } else {
                // bola segue o paddle antes de lançar
                ball.x = paddle.x + paddle.largura / 2;
            }

            // perdeu — bola caiu
            if (ball.y + ball.raio >= ALTURA) {
                perdeu = true;
                salvarScore(pontos);
            }
        }

        // reiniciar
        if ((ganhou || perdeu) && IsKeyPressed(KEY_R)) {
            pontos = 0;
            lancou = false;
            ganhou = false;
            perdeu = false;
            gerarBlocos(blocos);
            paddle.x = LARGURA / 2 - 50;
            iniciarBola(&ball, &paddle);
        }

        // desenhar
        BeginDrawing();
        ClearBackground(BLACK);

        if (!perdeu && !ganhou) {
            desenharJogo(&ball, &paddle, blocos, pontos);
            if (!lancou)
                DrawText("Pressione ESPACO para lancar", LARGURA / 2 - 150, ALTURA / 2, 20, WHITE);
        }

        if (ganhou) {
            DrawText("VOCE GANHOU!", LARGURA / 2 - 100, ALTURA / 2 - 20, 30, WHITE);
            DrawText(TextFormat("Pontos: %d", pontos), LARGURA / 2 - 60, ALTURA / 2 + 20, 20, WHITE);
            DrawText("Pressione R para jogar novamente", LARGURA / 2 - 160, ALTURA / 2 + 60, 20, WHITE);
        }

        if (perdeu) {
            DrawText("GAME OVER", LARGURA / 2 - 80, ALTURA / 2 - 20, 30, WHITE);
            DrawText(TextFormat("Pontos: %d", pontos), LARGURA / 2 - 60, ALTURA / 2 + 20, 20, WHITE);
            DrawText("Pressione R para jogar novamente", LARGURA / 2 - 160, ALTURA / 2 + 60, 20, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}