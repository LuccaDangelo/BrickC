# BrickC

Um jogo inspirado no Arkanoid desenvolvido 100% em C utilizando a biblioteca Raylib.

## Integrantes
- Lucca Albuquerque Dangelo
- Gabriel Gueiros Tabosa
- Victor Rodrigues Tavares

## Sobre o jogo
BrickC é um jogo de quebra-blocos onde o jogador controla um paddle na base da tela e deve destruir todos os blocos sem deixar a bola cair. A disposição dos blocos é gerada aleatoriamente a cada partida.

## Requisitos
- GCC
- Raylib

### Instalando a Raylib no Linux
```bash
sudo apt update
sudo apt install libraylib-dev
```

## Compilação
```bash
make run
```

## Como jogar
- **Seta esquerda / Seta direita** — move o paddle
- **Espaço** — lança a bola
- **R** — reinicia o jogo
- **ESC** — sai do jogo

## Objetivo
Destrua todos os blocos sem deixar a bola cair abaixo do paddle. Cada bloco destruído vale 10 pontos. Ao final da partida, sua pontuação é salva no ranking de top scores.

## Estrutura do projeto
BrickC/
├── main.c       — loop principal do jogo
├── game.c       — lógica do jogo (bola, paddle, blocos, colisão)
├── game.h       — structs e protótipos das funções
├── score.c      — leitura e escrita de pontuação em arquivo
├── score.h      — protótipos das funções de pontuação
├── scores.txt   — arquivo de top scores
└── Makefile     — compilação do projeto
