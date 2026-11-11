#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define ALTURA 20
#define LARGURA 40
#define MAX_CAUDA 100

typedef struct {
    int x;
    int y;
} Posicao;

Posicao cobra[MAX_CAUDA];
int tamanho = 3;
int direcaoX = 1;
int direcaoY = 0;
int comidaX, comidaY;
int jogoAtivo = 1;

void inicializarJogo() {
    cobra[0].x = 10;
    cobra[0].y = 10;
    cobra[1].x = 9;
    cobra[1].y = 10;
    cobra[2].x = 8;
    cobra[2].y = 10;

    comidaX = rand() % (LARGURA - 2) + 1;
    comidaY = rand() % (ALTURA - 2) + 1;
}

void desenharMapa() {
    system("cls");
    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            int desenhou = 0;

            if (x == 0 || y == 0 || x == LARGURA - 1 || y == ALTURA - 1) {
                printf("#");
                desenhou = 1;
            }

            for (int i = 0; i < tamanho; i++) {
                if (cobra[i].x == x && cobra[i].y == y) {
                    printf("O");
                    desenhou = 1;
                    break;
                }
            }

            if (comidaX == x && comidaY == y) {
                printf("*");
                desenhou = 1;
            }

            if (!desenhou) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void moverCobra() {
    for (int i = tamanho - 1; i > 0; i--) {
        cobra[i] = cobra[i - 1];
    }

    cobra[0].x += direcaoX;
    cobra[0].y += direcaoY;

    if (cobra[0].x == comidaX && cobra[0].y == comidaY) {
        if (tamanho < MAX_CAUDA) tamanho++;
        comidaX = rand() % (LARGURA - 2) + 1;
        comidaY = rand() % (ALTURA - 2) + 1;
    }

    if (cobra[0].x == 0 || cobra[0].y == 0 || cobra[0].x == LARGURA - 1 || cobra[0].y == ALTURA - 1) {
        jogoAtivo = 0;
    }

    for (int i = 1; i < tamanho; i++) {
        if (cobra[0].x == cobra[i].x && cobra[0].y == cobra[i].y) {
            jogoAtivo = 0;
        }
    }
}

int main(void) {
    char tecla = 'd';
    inicializarJogo();

    printf("=== Snake em Console ===\n");
    printf("Use W A S D para mover.\n");
    printf("Pressione qualquer tecla para iniciar...\n");
    getch();

    while (jogoAtivo) {
        if (kbhit()) {
            tecla = getch();
            if (tecla == 'w' && direcaoY != 1) { direcaoX = 0; direcaoY = -1; }
            if (tecla == 's' && direcaoY != -1) { direcaoX = 0; direcaoY = 1; }
            if (tecla == 'a' && direcaoX != 1) { direcaoX = -1; direcaoY = 0; }
            if (tecla == 'd' && direcaoX != -1) { direcaoX = 1; direcaoY = 0; }
        }

        moverCobra();
        desenharMapa();
        Sleep(120);
    }

    printf("Game Over!\n");
    return 0;
}
