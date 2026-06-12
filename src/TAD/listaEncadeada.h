#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

typedef struct Emprestimo {
    char nomeUsuario [100];
    int codigoLivro ;
    char tituloLivro [100];
} Emprestimo ;

typedef struct NoLista {
    Emprestimo emprestimo ;
    struct NoLista * prox ;
} NoLista ;

typedef struct Lista {
    NoLista * inicio ;
} Lista ;

Lista * criarLista () ;

void inserirEmprestimo ( Lista * lista , Emprestimo emprestimo ) ;

void deletarEmprestimo(Lista *lista, Emprestimo emprestimo);

void listarEmprestimos ( Lista * lista ) ;

int listaVazia ( Lista * lista ) ;

void liberarLista(Lista *lista);

#endif