#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int numeroSecreto, tentativa, maxTentativas = 10;

    srand(time(NULL));
    numeroSecreto = rand() % 100 + 1;

    printf("=== Jogo de Adivinhacao ===\n");
    printf("Tente adivinhar o numero entre 1 e 100.\n");
    printf("Voce tem %d tentativas.\n\n", maxTentativas);

    for (int i = 1; i <= maxTentativas; i++) {
        printf("Tentativa %d: ", i);
        scanf("%d", &tentativa);

        if (tentativa == numeroSecreto) {
            printf("Parabens! Voce acertou em %d tentativas!\n", i);
            return 0;
        } else if (tentativa < numeroSecreto) {
            printf("O numero e maior!\n");
        } else {
            printf("O numero e menor!\n");
        }
    }

    printf("Game over! O numero secreto era: %d\n", numeroSecreto);
    return 0;
}
