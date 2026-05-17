#include <stdio.h>
#include <stdlib.h> // Necessário para usar a função free()
#include "livro.h"  // Alterado para o singular conforme o edital

int main()
{
    Livro *livro;

    int codigo;
    char titulo[100];
    char autor[100];
    int ano;
    int quantidadeTotal;

    printf("Digite o codigo: ");
    scanf("%d", &codigo);

    printf("Digite o titulo: ");
    scanf(" %[^\n]", titulo);

    printf("Digite o autor: ");
    scanf(" %[^\n]", autor);

    printf("Digite o ano: ");
    scanf("%d", &ano);

    printf("Digite a quantidade total: ");
    scanf("%d", &quantidadeTotal);

    livro = criarLivro(
        codigo,
        titulo,
        autor,
        ano,
        quantidadeTotal
    );

    printf("\n--- Dados do Livro Cadastrado ---\n");
    exibirLivro(livro);

    // Libera a memória alocada dinamicamente pelo TAD
    free(livro); 

    return 0;
}