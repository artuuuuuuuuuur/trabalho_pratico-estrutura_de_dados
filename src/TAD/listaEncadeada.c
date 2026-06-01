#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listaEncadeada.h" 

Lista * criarLista () {
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    if (lista != NULL) {
        lista->inicio = NULL;
    }
    return lista;
};

void inserirEmprestimo ( Lista * lista , Emprestimo emprestimo ){
    NoLista* novo = (NoLista*) malloc(sizeof(NoLista));
    if(novo == NULL){
        printf("Erro ao alocar memoria para emprestimo.\n");
        return;
    }
    novo->emprestimo = emprestimo;
    novo->prox = NULL;
    if(lista->inicio == NULL){
        lista->inicio = novo;
    }else{
        NoLista* temp = lista->inicio;
        while(temp->prox != NULL){
            temp = temp->prox;
        }
        temp->prox = novo;
    }
};

void deletarEmprestimo(Lista * lista , Emprestimo emprestimo ){
    if(lista->inicio == NULL){
        printf("A lista está vazia.\n");
        return;
    } else {
        NoLista* curr = lista->inicio;
        NoLista* prev = NULL;
        while(curr != NULL){
            if (curr->emprestimo.codigoLivro == emprestimo.codigoLivro &&
                strcmp(curr->emprestimo.nomeUsuario, emprestimo.nomeUsuario) == 0) {
                if (prev == NULL) {
                    lista->inicio = curr->prox;
                } else {
                prev->prox = curr->prox;
                }
                free(curr);
                printf("Emprestimo deletado.\n");
                return ;
            }
            prev = curr;
            curr = curr->prox;
        }
        printf("Emprestimo nao encontrado.\n");
    }
};

void listarEmprestimos ( Lista * lista ){
    if(listaVazia(lista)){
        printf("Lista vazia. Nao ha emprestimos para exibir.\n");
        return;
    }
    NoLista* temp = lista->inicio;
    while(temp != NULL){
        printf("Usuario: %s\n", temp->emprestimo.nomeUsuario);
        printf("Codigo do Livro: %d\n", temp->emprestimo.codigoLivro);
        printf("Titulo do Livro: %s\n", temp->emprestimo.tituloLivro);
        printf("-------------------------\n");
        temp = temp->prox;
    }
};

int listaVazia ( Lista * lista ) {
    return lista->inicio == NULL;
};
