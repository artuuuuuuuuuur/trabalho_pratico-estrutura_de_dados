#include "utils.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void getString(char texto[], char *string, size_t tamanho) {
    printf("%s", texto);
    fgets(string, tamanho, stdin);
    while(string[0] == '\n') {
        printf("Entrada vazia. Tente novamente.\n");
        printf("%s", texto);
        fgets(string, tamanho, stdin);
    }
    string[strcspn(string, "\n")] = 0;
}