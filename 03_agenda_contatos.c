#include <stdio.h>
#include <string.h>

#define MAX_CONTATOS 100

typedef struct {
    char nome[50];
    char telefone[20];
} Contato;

int main(void) {
    Contato agenda[MAX_CONTATOS];
    int total = 0;
    int opcao;

    while (1) {
        printf("\n=== Agenda de Contatos ===\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Listar contatos\n");
        printf("3 - Buscar contato\n");
        printf("4 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            if (total >= MAX_CONTATOS) {
                printf("Agenda cheia!\n");
                continue;
            }

            printf("Nome: ");
            scanf("%49s", agenda[total].nome);
            printf("Telefone: ");
            scanf("%19s", agenda[total].telefone);
            total++;
            printf("Contato adicionado com sucesso!\n");
        } else if (opcao == 2) {
            if (total == 0) {
                printf("Nenhum contato cadastrado.\n");
                continue;
            }

            printf("\nContatos cadastrados:\n");
            for (int i = 0; i < total; i++) {
                printf("%d - %s: %s\n", i + 1, agenda[i].nome, agenda[i].telefone);
            }
        } else if (opcao == 3) {
            char nomeBusca[50];
            int encontrado = 0;

            printf("Digite o nome para buscar: ");
            scanf("%49s", nomeBusca);

            for (int i = 0; i < total; i++) {
                if (strcmp(agenda[i].nome, nomeBusca) == 0) {
                    printf("Contato encontrado: %s - %s\n", agenda[i].nome, agenda[i].telefone);
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado) {
                printf("Contato nao encontrado.\n");
            }
        } else if (opcao == 4) {
            printf("Saindo da agenda...\n");
            break;
        } else {
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}
