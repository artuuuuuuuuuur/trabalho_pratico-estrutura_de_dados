#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila.h" 

Fila * criarFila(){
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    if (fila != NULL){
        fila->inicio = NULL;
        fila->fim = NULL;
    }
    return fila;
};

void enfileirarReserva( Fila * fila , Reserva reserva ){
    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));
    if (novo == NULL){
        printf("Erro ao alocar memoria para reserva.\n");
        return;
    }
    novo->reserva = reserva;
    novo->prox = NULL;
    if(fila->inicio == NULL){
        fila->inicio = novo;
        fila->fim = novo;
    }else{
        fila->fim->prox = novo;
        fila->fim = novo;
    }
};

Reserva desenfileirarReserva( Fila * fila ){
    if(filaVazia(fila)){
        printf("Fila vazia. NNao ha reservas para desenfilerar.\n");
        Reserva vazia;
        strcpy(vazia.nomeUsuario, "");
        vazia.codigoLivro = -1;
        return vazia;
    }
    NoFila* temp = fila->inicio;
    fila->inicio = temp->prox;
    if(fila->inicio == NULL){
        fila->fim = NULL;
    }
    temp->prox = NULL;
    return temp->reserva;
};

int filaVazia( Fila * fila ){
    return (fila->inicio == NULL);
};

void exibirReservas( Fila * fila ){
    if(filaVazia(fila)){
        printf("Fila vazia. Nao ha reservas para exibir.\n");
        return;
    }
    NoFila* temp = fila->inicio;
    while (temp != NULL){
        printf("- Usuario: %s, Codigo do Livro: %d\n", temp->reserva.nomeUsuario, temp->reserva.codigoLivro);
        temp = temp->prox;
    }
};