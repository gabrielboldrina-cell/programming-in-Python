#include <stdio.h>

char tabuleiro[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

void imprimirTabuleiro() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

char verificarVencedor() {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2])
            return tabuleiro[i][0];
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i])
            return tabuleiro[0][i];
    }

    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2])
        return tabuleiro[0][0];
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0])
        return tabuleiro[0][2];

    return ' ';
}

int main(void) {
    int linha, coluna, jogada = 0;
    char simbolo = 'X';
    char vencedor = ' ';

    printf("=== Jogo da Velha ===\n");
    imprimirTabuleiro();

    while (jogada < 9) {
        printf("Jogador %c, escolha uma posicao (1-9): ", simbolo);
        scanf("%d", &linha);

        if (linha < 1 || linha > 9) {
            printf("Posicao invalida!\n");
            continue;
        }

        linha--; 
        coluna = linha % 3;
        linha = linha / 3;

        if (tabuleiro[linha][coluna] == 'X' || tabuleiro[linha][coluna] == 'O') {
            printf("Essa posicao ja foi escolhida!\n");
            continue;
        }

        tabuleiro[linha][coluna] = simbolo;
        jogada++;
        imprimirTabuleiro();

        vencedor = verificarVencedor();
        if (vencedor == 'X' || vencedor == 'O') {
            printf("Jogador %c venceu!\n", vencedor);
            return 0;
        }

        if (jogada == 9) {
            printf("Empate!\n");
            return 0;
        }

        simbolo = (simbolo == 'X') ? 'O' : 'X';
    }

    return 0;
}
