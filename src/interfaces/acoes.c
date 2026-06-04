#include "acoes.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int cadastrarNovoLivro(Arvore* arvore) {
    if (arvore == NULL) {
        printf("Erro: a árvore não existe.\n");
        return 0;    
    }

    char tituloLivro[100], autorLivro[100];
    int anoLivro, quantidadeTotalLivro;
    printf("=== Cadastrar Árvore ===\n  Título (max 100 char): ");
    scanf("%s", tituloLivro);
    printf("\nAutor (max 100 char): ");
    scanf("%s", autorLivro);
    printf("\nAno: ");
    scanf("%d", anoLivro);
    printf("\nQuantidade total: ");
    scanf("%d", quantidadeTotalLivro);
    
    if(!tituloLivro || !autorLivro || !anoLivro || !quantidadeTotalLivro) {
        printf("Erro: preencha todos os espaços corretamente.\n");
        return 0;
    }

    Livro *novoLivro = criarLivro(contarLivros(arvore) + 1, tituloLivro, autorLivro, anoLivro, quantidadeTotalLivro);
    if(novoLivro) inserirLivroArvore(arvore, novoLivro);
    return 1;
}

int removerLivro(Livro *livro, Arvore *arvore, Lista* emprestimos, Fila* reservas) {
    if (livro == NULL) {
        printf("Erro: o livro não existe.\n");
        return 0;
    }
    if (arvore == NULL) {
        printf("Erro: a árvore não existe.\n");
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
        printf("Erro: Você precisa quitar todas as pendências do livro.\n");
        char errorMessage[100]= "Há pendências de ";
        if(emprestimoEncontrado) strcat(errorMessage, "emprestimos ");
        if(emprestimoEncontrado && reservaEncontrada) strcat(errorMessage, "e ");
        if(reservaEncontrada) strcat(errorMessage, "reservas ");
        printf("$s.\n", errorMessage);
        return 0;
    }
    
    arvore->raiz = removerNoLivro(arvore->raiz, livro);
    return 1;
}


int buscarLivroPorCodigo(int codigo, Arvore* arvore) {
    if (codigo < 0) {
        printf("Erro: o código não é válido.\n");
        return 0;
    }
    if (arvore == NULL) {
        printf("Erro: a árvore não existe.\n");
        return 0;    
    }
    Livro* livroEncontrado = buscarLivroArvore(arvore, codigo);
    if(livroEncontrado == NULL) {
        printf("Livro não encontrado.\n");
        return 0;
    }    
    exibirLivro(livroEncontrado);
    return 1;
}

int listarLivrosCrescente(Arvore* arvore) {
    if(arvore->raiz == NULL) {
        printf("Erro: árvore está vazia.\n");
        return 0;
    }

    listarLivrosEmOrdem(arvore);
    return 1;
}

int listarLivrosPre(Arvore* arvore) {
    if(arvore->raiz == NULL) {
        printf("Erro: árvore está vazia.\n");
        return 0;
    }

    listarLivrosPreOrdem(arvore);
    return 1;
}

int listarLivrosPos(Arvore* arvore) {
    if(arvore->raiz == NULL) {
        printf("Erro: árvore está vazia.\n");
        return 0;
    }

    listarLivrosPosOrdem(arvore);
    return 1;
}

int emprestimoLivro(Livro * livro, Lista* listaDeEmprestimos, char * nomeUsuario) {
    if(livro == NULL) {
        printf("Erro: o livro não existe.\n");
        return 0;
    }
    Emprestimo novo_emprestimo;
    novo_emprestimo.codigoLivro = livro->codigo;
    strcpy(novo_emprestimo.tituloLivro, livro->titulo);
    strcpy(novo_emprestimo.nomeUsuario, nomeUsuario);
    inserirEmprestimo(listaDeEmprestimos, novo_emprestimo);
    // Emprestar apenas se a inserção na lista ocorrer
    emprestarExemplar(livro);
    return 1;
}

int devolverLivro(Livro* livro, Lista* listaDeEmprestimos, char* nomeUsuario) {
    if (livro == NULL) {
        printf("Erro: o livro não existe.\n");
        return 0;
    }
    Emprestimo emprestimoEncontrado;
    NoLista *no = listaDeEmprestimos->inicio;
    while(no != NULL) {
        if(no->emprestimo.codigoLivro == livro->codigo &&
            strcmp(no->emprestimo.nomeUsuario, nomeUsuario) == 0) {
            emprestimoEncontrado = no->emprestimo;
            deletarEmprestimo(listaDeEmprestimos, emprestimoEncontrado);
            // Devolver apenas se a deleção na lista ocorrer
            devolverExemplar(livro);
            return 1;
        }
        no = no->prox;
    }
    printf("Não foi possível devolver o livro.\n");
}

void exibirReservas(Fila* filaDeReservas) {
    exibirReservas(filaDeReservas);
}

int exibirQuantidadeLivros(Arvore* arvore) {
    if(arvore->raiz == NULL) {
        printf("A árvore está vazia.\n");
        return 0;
    }
    int qtLivros = contarLivros(arvore);
    return qtLivros;
}

int exibirAlturaArvore(Arvore* arvore) {
    if(arvore->raiz == NULL) {
        printf("A árvore está vazia.\n");
        return 0;
    }
    int alturaArvore = calcularAlturaArvore(arvore);
    return alturaArvore;
}