#include "utils.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void getString(char texto[], char *string) {
    printf("%s", texto);
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = 0;
}