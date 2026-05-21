#include<acoes.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int emprestimoLivro(const Livro * livro, Lista* listaDeEmprestimos, const char * nomeUsuario) {
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

int devolverLivro(const Livro* livro, Lista* listaDeEmprestimos, const char* nomeUsuario) {
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