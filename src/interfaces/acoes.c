#include<acoes.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int emprestimoLivro(const Livro * livro, Lista* listaDeEmprestimos, const char * nomeUsuario) {
    if(livro == NULL) {
        printf("Erro: o livro não existe.");
    }
    Emprestimo novo_emprestimo;
    novo_emprestimo.codigoLivro = livro->codigo;
    strcpy(novo_emprestimo.tituloLivro, livro->titulo);
    strcpy(novo_emprestimo.nomeUsuario, nomeUsuario);
    inserirEmprestimo(listaDeEmprestimos, novo_emprestimo);
}