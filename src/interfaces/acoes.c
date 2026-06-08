#include "acoes.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "../utils/utils.h"

int cadastrarNovoLivro(Arvore* arvore) {
    system("cls");
    if (arvore == NULL) {
        printf("Erro: a arvore nao existe.\n");
        return 0;    
    }

    char tituloLivro[100], autorLivro[100];
    int anoLivro, quantidadeTotalLivro;
    printf("=== Cadastrar Livro ===\n");
    getString("  Titulo (max 99 char): ", tituloLivro);
    getString("  Autor (max 99 char): ", autorLivro);
    printf("  Ano: ");
    if (scanf("%d", &anoLivro) != 1) {
        printf("Erro: entrada invalida para o ano.\n");
        limparBuffer();
        getchar();
        return 0;
    }

    printf("  Quantidade total: ");
    if (scanf("%d", &quantidadeTotalLivro) != 1) {
        printf("Erro: entrada invalida para a quantidade.\n");
        limparBuffer();
        getchar();
        return 0;
    }
    
    limparBuffer(); 
    if(strlen(tituloLivro) == 0 || strlen(autorLivro) == 0 || quantidadeTotalLivro < 0) {
        printf("Erro: preencha todos os espaços corretamente.\n");
        getchar();
        return 0;
    }

    Livro *novoLivro = criarLivro(contarLivros(arvore) + 1, tituloLivro, autorLivro, anoLivro, quantidadeTotalLivro);
    if(novoLivro) {
        inserirLivroArvore(arvore, novoLivro);
        printf("Livro cadastrado com sucesso.\n");
    } else {
        printf("Erro interno ao criar o livro.\n");
        return 0;
    }
    return 1;
}

int removerLivro(Livro *livro, Arvore *arvore, Lista* emprestimos, Fila* reservas) {
    if (livro == NULL) {
        printf("Erro: o livro nao existe.\n");
        return 0;
    }
    if (arvore == NULL) {
        printf("Erro: a arvore nao existe.\n");
        return 0;    
    }

    // Tratamento de exceções
    bool emprestimoEncontrado = false;
    bool reservaEncontrada = false;
    if(emprestimos->inicio != NULL) { // Livro emprestado
        NoLista *temp = emprestimos->inicio;
        while (temp != NULL && !emprestimoEncontrado) {
            if (temp->emprestimo.codigoLivro == livro->codigo) emprestimoEncontrado = true;
            else temp = temp->prox;
        }
    }
    
    if(reservas->inicio != NULL) { // Livro reservado
        NoFila *temp = reservas->inicio;
        while (temp != NULL && !reservaEncontrada) {
            if (temp->reserva.codigoLivro == livro->codigo) reservaEncontrada = true;
            else temp = temp->prox;
        }
    }
    
    if(emprestimoEncontrado || reservaEncontrada) {
        printf("Erro: Você precisa quitar todas as pendencias do livro.\n");
        char errorMessage[100]= "Ha pendencias de ";
        if(emprestimoEncontrado) strcat(errorMessage, "emprestimos ");
        if(emprestimoEncontrado && reservaEncontrada) strcat(errorMessage, "e ");
        if(reservaEncontrada) strcat(errorMessage, "reservas ");
        printf("$s.\n", errorMessage);
        return 0;
    }
    
    arvore->raiz = removerNoLivro(arvore->raiz, livro);
    return 1;
}

int buscarLivroPorCodigo(Arvore* arvore) {
    if (arvore == NULL) {
        printf("Erro: a arvore nao existe.\n");
        return 0;    
    }

    int codigoLivro = -1;
    printf("=== Buscar livro por codigo ===\nCodigo: ");
    if (scanf("%d", &codigoLivro) != 1) {
        printf("Erro: entrada invalida. Digite apenas numeros.\n");
        limparBuffer(); // Limpa o lixo (letras) antes de sair
        return 0;
    }    
    limparBuffer();

    if (codigoLivro < 0) {
        printf("Erro: o codigo nao é valido.\n");
        return 0;
    }

    Livro* livroEncontrado = buscarLivroArvore(arvore, codigoLivro);
    if(livroEncontrado == NULL) {
        printf("Livro nao encontrado.");
    } else {
        printf("======= Livro encontrado =======\n");
        exibirLivro(livroEncontrado);
        printf("=========================================\n");
    }
    return 1;
}

int listarLivrosCrescente(Arvore* arvore) {
    if(arvore->raiz == NULL) {
        printf("A arvore esta vazia.\n");
    } else {
        printf("==== Lista de livros em ordem ====\n");
        listarLivrosEmOrdem(arvore);
        printf("=====================================\n");
    }
    return 1;
}

int listarLivrosPre(Arvore* arvore) {
    if(arvore->raiz == NULL) {
        printf("Erro: arvore esta vazia.\n");
    } else {    
        printf("==== Lista de livros em ordem ====\n");
        listarLivrosPreOrdem(arvore);
        printf("=====================================\n");
    }
    return 1;
}

int listarLivrosPos(Arvore* arvore) {
    if(arvore->raiz == NULL) {
        printf("Erro: arvore esta vazia.\n");
    } else {
        printf("==== Lista de livros em ordem ====\n");
        listarLivrosPosOrdem(arvore);
        printf("=====================================\n");
    }
    return 1;
}

int emprestimoLivro(Arvore *arvore, Lista* listaDeEmprestimos) {
    printf("======= Emprestimo de Livros =======\n");
    if(arvore->raiz == NULL) {
        printf("Erro: nenhum livro cadastrado.\n");
        return 1;
    }
    int codigoLivro;
    char nomeUsuario[100];
    printf("  Codigo: ");
    if (scanf("%d", &codigoLivro) != 1) {
        printf("Erro: entrada invalida para o codigo.\n");
        limparBuffer();
        getchar();
        return 0;
    }
    Livro *livroEncontrado = buscarLivroArvore(arvore, codigoLivro);
    if(livroEncontrado == NULL) {
        printf("Erro: O livro nao existe.\n");
        return 1;
    }
    getchar();
    getString("  Nome do Usuario: ", nomeUsuario);
    if(livroEncontrado->quantidadeDisponivel > 0) { // Empresta apenas se tiver livros
        Emprestimo novo_emprestimo;
        novo_emprestimo.codigoLivro = livroEncontrado->codigo;
        strcpy(novo_emprestimo.tituloLivro, livroEncontrado->titulo);
        strcpy(novo_emprestimo.nomeUsuario, nomeUsuario);
        inserirEmprestimo(listaDeEmprestimos, novo_emprestimo);
        emprestarExemplar(livroEncontrado);
        printf("Emprestimo feito com sucesso!\n");
    } else { // Se todos os livros já foram emprestados
        NoArvore *noLivro = buscarNoLivroArvore(arvore, codigoLivro);
        if(noLivro == NULL) {
            printf("Erro: O livro nao existe.\n");
            return 1;
        }
        Fila* filaDeReservas = noLivro->filaEspera;
        char res;
        int entradaValida = 0;
        while (entradaValida == 0) {
            printf("Sem mais exemplares disponiveis!\nDeseja adicionar o usuario a fila de reservas? (S / N): ");
            if (scanf(" %c", &res) != 1) { 
            limparBuffer();
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }
        limparBuffer();

            switch (res) {
                case 'S': 
                case 's': {
                    Reserva nova_reserva;
                    nova_reserva.codigoLivro = codigoLivro;
                    strcpy(nova_reserva.nomeUsuario,nomeUsuario);
                    enfileirarReserva(filaDeReservas, nova_reserva);
                    printf("Adicionado a fila de reservas!\n");
                    entradaValida = 1;
                    break;
                }
                case 'N': 
                case 'n': {
                    printf("O usuario nao foi adicionado a fila de reservas.\n");
                    entradaValida = 1;
                    break;
                }    
            default:
                printf("Opção invalida. Tente novamente.\n");
                break;
            }
        }
        
    }
    return 1;
}

int devolverLivro(Arvore* arvore, Lista* listaDeEmprestimos) {
    printf("======= Devoluçao de Livros =======\n");
    if(arvore->raiz == NULL) {
        printf("Erro: nenhum livro cadastrado.\n");
        return 1;
    }
    int codigoLivro;
    char nomeUsuario[100];
    printf("  Codigo: ");
    if (scanf("%d", &codigoLivro) != 1) {
        printf("Erro: entrada invalida para o codigo.\n");
        limparBuffer();
        getchar();
        return 0;
    }
    Livro *livroEncontrado = buscarLivroArvore(arvore, codigoLivro);
    if(livroEncontrado == NULL) {
        printf("Erro: O livro nao existe.\n");
        return 1;
    }
    getchar();
    getString("  Nome do Usuario: ", nomeUsuario);

    NoArvore *noLivro = buscarNoLivroArvore(arvore, codigoLivro);
    Fila* filaDeReservas = noLivro->filaEspera;
    Emprestimo emprestimoEncontrado;
    NoLista *no = listaDeEmprestimos->inicio;
    while(no != NULL) { // Pesquisa o emprestimo na lista
        if(no->emprestimo.codigoLivro == livroEncontrado->codigo &&
            strcmp(no->emprestimo.nomeUsuario, nomeUsuario) == 0) {
            // Emprestimo encontrado
            emprestimoEncontrado = no->emprestimo;
            deletarEmprestimo(listaDeEmprestimos, emprestimoEncontrado); // Deleta o emprestimo da lista
            devolverExemplar(livroEncontrado);
            if(filaDeReservas->inicio != NULL) {
                Emprestimo novoEmprestimo;
                novoEmprestimo.codigoLivro = codigoLivro;
                strcpy(novoEmprestimo.nomeUsuario, filaDeReservas->inicio->reserva.nomeUsuario);
                strcpy(novoEmprestimo.tituloLivro, livroEncontrado->titulo);
                inserirEmprestimo(listaDeEmprestimos, novoEmprestimo);
                emprestarExemplar(livroEncontrado);
                desenfileirarReserva(filaDeReservas);
            }
            return 1;
        }
        no = no->prox;
    }
    printf("Nao foi possível devolver o livro.\n");
}

int imprimirEmprestimos(Lista* listaDeEmprestimos) {
    if(listaDeEmprestimos->inicio == NULL) {
        printf("A lista de emprestimos esta vazia.\n");
    } else {
        printf("==== Lista de emprestimos ====\n");
        listarEmprestimos(listaDeEmprestimos);
        printf("====================================== \n");
    }
    return 1;
}

int imprimirReservas(Arvore* arvore) {
    printf("======= Fila de Reservas =======\n");
    if(arvore->raiz == NULL) {
        printf("Erro: nenhum livro cadastrado.\n");
        return 1;
    }
    int codigoLivro;
    printf("  Código: ");
    if (scanf("%d", &codigoLivro) != 1) {
        printf("Erro: entrada invalida para o codigo.\n");
        limparBuffer();
        getchar();
        return 0;
    }
    limparBuffer();
    NoArvore *noLivro = buscarNoLivroArvore(arvore, codigoLivro);
    if(noLivro == NULL) {
        printf("Erro: O livro nao existe.\n");
        return 1;
    }
    Fila* filaDeReservas = noLivro->filaEspera;
    if(filaDeReservas->inicio == NULL) {
        printf("A fila de reservas esta vazia.\n");
    } else {
        printf("==== Lista de reservas ====\n");
        exibirReservas(filaDeReservas);
        printf("==============================\n");
    }
    return 1;
}

int exibirQuantidadeLivros(Arvore* arvore) {
    if(arvore->raiz == NULL) {
        printf("A arvore esta vazia.\n");
    } else {
        int qtLivros = contarLivros(arvore);
        printf("Livros cadastrados: %d\n", qtLivros);
    }
    return 1;
}

int exibirAlturaArvore(Arvore* arvore) {
    if(arvore->raiz == NULL) {
        printf("A arvore esta vazia.\n");
    } else {
        int alturaArvore = calcularAlturaArvore(arvore);
        printf("Altura da arvore: %d\n", alturaArvore);
    }
    return 1;
}