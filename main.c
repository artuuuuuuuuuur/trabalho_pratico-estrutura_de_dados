#include <stdio.h>
#include <stdlib.h>
#include "src/interfaces/acoes.h"
#include "src/utils/utils.h"
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    // Inicializando TADs
    Arvore *arvore = criarArvore();
    Lista *lista = criarLista();

    int opcao;
    do {
        system("cls");
        printf("========== Menu Principal ==========\n");
        printf("1 - Cadastrar Novo Livro\n");
        printf("2 - Buscar Livro\n");
        printf("3 - Listar livros em ordem crescente de código\n");
        printf("4 - Listar livros em pré - ordem\n");
        printf("5 - Listar livros em pós - ordem\n");
        printf("6 - Realizar empréstimo de livro\n");
        printf("7 - Devolver livro\n");
        printf("8 - Remover livro\n");
        printf("9 - Exibir fila de reservas\n");
        printf("10 - Exibir histórico de empréstimos\n");
        printf("11 - Exibir quantidade de livros cadastrados\n");
        printf("12 - Exibir altura da árvore\n");
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
            case 4: {
                system("cls");
                int status = -1;
                while (status == -1 || status == 0) status = listarLivrosPre(arvore);
                break;
            }
            case 5: {
                system("cls");
                int status = -1;
                while (status == -1 || status == 0) status = listarLivrosPos(arvore);
                break;
            }
            case 6: {
                system("cls");
                int status = -1;
                while (status == -1 || status == 0) status = emprestimoLivro(arvore, lista);
                break;
            }
            case 7: {
                system("cls");
                int status = -1;
                while (status == -1 || status == 0) status = devolverLivro(arvore, lista);
                break;
            }
            case 8: {
                system("cls");
                int status = -1;
                while (status == -1 || status == 0) status = removerLivro(arvore, lista);
                break;
            }
            case 9: {
                system("cls");
                int status = -1;
                while (status == -1 || status == 0) status = imprimirReservas(arvore);
                break;
            }
            case 10: {
                system("cls");
                int status = -1;
                while (status == -1 || status == 0) status = imprimirEmprestimos(lista);
                break;
            }
            case 11: {
                system("cls");
                int status = -1;
                while (status == -1 || status == 0) status = exibirQuantidadeLivros(arvore);
                break;
            }
            case 12: {
                system("cls");
                int status = -1;
                while (status == -1 || status == 0) status = exibirAlturaArvore(arvore);
                break;
            }
            case 0: {
                printf("Saindo do programa...\n");
                break;
            }
            default: {
                printf("Opcao invalida. Tente novamente.\n");
                break;
            }
        }
        printf("Pressione 'ENTER' para prosseguir");
        getchar();
    } while(opcao != 0);

    return 0;
}