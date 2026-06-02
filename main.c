#include <stdio.h>

int main(void) {
    int opcao;
    do{
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
        switch (opcao)
        {
            case 1:
                printf("Cadastrar Novo Livro\n");
                break;
            case 2:
                printf("Buscar Livro\n");
                break; 
                printf("Listar livros em ordem crescente de codigo\n");
                break;
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