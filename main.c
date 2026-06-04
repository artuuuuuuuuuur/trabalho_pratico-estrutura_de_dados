#include <stdio.h>
#include <stdlib.h>
#include "src/interfaces/acoes.h"
#include "src/utils/utils.h"

int main(void) {
    Arvore *arvore = (Arvore *)malloc(sizeof(Arvore)); // Inicializando Árvore
    arvore->raiz = NULL;

    int opcao;
    do {
        system("cls");
        printf("========== Menu Principal ==========\n");
        printf("1 - Cadastrar Novo Livro\n");
        printf("2 - Buscar Livro\n");
        printf("3 - Listar livros em ordem crescente de codigo\n");
        printf("4 - Listar livros em pre - ordem\n");
        printf("5 - Listar livros em pos - ordem\n");
        printf("6 - Realizar emprestimo de livro\n");
        printf("7 - Devolver livro\n");
        printf("8 - Exibir fila de reservas\n");
        printf("9 - Exibir historico de emprestimos\n");
        printf("10 - Exibir quantidade de livros cadastrados\n");
        printf("11 - Exibir altura da arvore\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);
        limparBuffer();
        switch (opcao) {
            case 1: {
                system("cls");
                int status = -1;
                while (status == -1 || status == 0) status = cadastrarNovoLivro(arvore);
                break;
            }
            case 2: {
                system("cls");
                int status = -1;
                while (status == -1 || status == 0) status = buscarLivroPorCodigo(arvore);
                break; 
            }
            case 3: {
                system("cls");
                int status = -1;
                while (status == -1 || status == 0) status = listarLivrosCrescente(arvore);
                break;
            }
            case 4:
                printf("Listar livros em pre - ordem\n");
                break;
            case 5:
                printf("Listar livros em pos - ordem\n");
                break;
            case 6:
                printf("Realizar emprestimo de livro\n");
                break;
            case 7:
                printf("Devolver livro\n");
                break;
            case 8:
                printf("Exibir fila de reservas\n");
                break;
            case 9:
                printf("Exibir historico de emprestimos\n");
                break;
            case 10:
                printf("Exibir quantidade de livros cadastrados\n");
                break;
            case 11:
                printf("Exibir altura da arvore\n");
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while(opcao != 0);

    return 0;
}