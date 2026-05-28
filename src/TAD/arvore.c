#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

NoArvore* criarNo(Livro *livro) {
    NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para o novo no da arvore.\n");
        return NULL;
    }

    novo->livro = livro;
    novo->altura = 0;
    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
};

int fatorBalanceamento(NoArvore *n) {
    if (n == NULL){
        return 0;
    }
    return calcularAlturaArvore(n->esquerda) - calcularAlturaArvore(n->direita);
};

int maior(int a, int b) {
    return (a > b) ? a : b;
};

NoArvore* rotacaoDireita(NoArvore *y) {
    NoArvore *x = y->esquerda;
    NoArvore *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = maior(calcularAlturaArvore(y->esquerda),
    calcularAlturaArvore(y->direita)) + 1;
    x->altura = maior(calcularAlturaArvore(x->esquerda),
    calcularAlturaArvore(x->direita)) + 1;

    return x;
};

NoArvore* rotacaoEsquerda(NoArvore *x) {
    NoArvore *y = x->direita;
    NoArvore *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = maior(calcularAlturaArvore(x->esquerda),
    calcularAlturaArvore(x->direita)) + 1;
    y->altura = maior(calcularAlturaArvore(y->esquerda),
    calcularAlturaArvore(y->direita)) + 1;

    return y;
};

Arvore * criarArvore (){
    Arvore * arvore = (Arvore *) malloc(sizeof(Arvore));
    if (arvore != NULL) {
        arvore->raiz = NULL;
    }
    return arvore;
};

NoArvore* inserirLivroArvore(NoArvore *raiz, Livro *livro) {
    if (raiz == NULL){
        return criarNo(livro);
    }

    if (livro->codigo < raiz->livro->codigo){
        raiz->esquerda = inserirLivroArvore(raiz->esquerda, livro);
    }else if (livro->codigo > raiz->livro->codigo){
        raiz->direita = inserirLivroArvore(raiz->direita, livro);
    }else{
        return raiz;
    }
    raiz->altura = 1 + maior(calcularAlturaArvore(raiz->esquerda),
    calcularAlturaArvore(raiz->direita));

    int fb = fatorBalanceamento(raiz);
    if (fb > 1 && livro->codigo < raiz->esquerda->livro->codigo){
        return rotacaoDireita(raiz);
    }

    if (fb < -1 && livro->codigo > raiz->direita->livro->codigo){
        return rotacaoEsquerda(raiz);
    }

    if (fb > 1 && livro->codigo > raiz->esquerda->livro->codigo) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (fb < -1 && livro->codigo < raiz->direita->livro->codigo) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
};

Livro * buscarLivroArvore ( NoArvore * no , int codigo ){
    NoArvore* atual = no;
    while (atual != NULL){
        if (codigo == atual -> livro -> codigo){
            return atual -> livro;
        }else if (codigo < atual -> livro -> codigo){
            atual = atual -> esquerda;
        }else{
            atual = atual -> direita;
        }
    }
    return NULL;
};

void listarLivrosEmOrdem ( NoArvore * no ){
    if (no != NULL){
        listarLivrosPreOrdem(no -> esquerda);
        printf("Codigo: %d, Titulo: %s\n", no -> livro -> codigo, no -> livro -> titulo);
        listarLivrosPreOrdem(no -> direita);
    }
};

void listarLivrosPreOrdem ( NoArvore * no ){
    if (no != NULL){
        printf("Codigo: %d, Titulo: %s\n", no -> livro -> codigo, no -> livro -> titulo);
        listarLivrosPreOrdem(no -> esquerda);
        listarLivrosPreOrdem(no -> direita);
    }
};

void listarLivrosPosOrdem ( NoArvore * no ){
    if (no != NULL){
        listarLivrosPosOrdem(no -> esquerda);
        listarLivrosPosOrdem(no -> direita);
        printf("Codigo: %d, Titulo: %s\n", no -> livro -> codigo, no -> livro -> titulo);
    }
};

int contarLivros ( NoArvore * no ){
    if (no == NULL){
        return 0;
    }else{
        return 1 + contarLivros(no -> esquerda) + contarLivros(no -> direita);
    }
};

int calcularAlturaArvore ( NoArvore * no ){
    if (no == NULL){
        return -1;
    }

    return no->altura;
};

void liberarArvore(NoArvore *no) {
    if (no != NULL) {
        liberarArvore(no->esquerda);
        liberarArvore(no->direita);
        free(no->livro);
        free(no);
    }
};