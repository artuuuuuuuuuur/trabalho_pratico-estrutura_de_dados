#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

// Funções auxiliares para balanceamento e implementação da árvore AVL

NoArvore* criarNo(Livro *livro) {
    NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
    if (novo == NULL) {
        printf("Erro ao alocar memória para o novo nó da árvore.\n");
        return NULL;
    }

    novo->livro = livro;
    novo->altura = 0;
    novo->filaEspera = criarFila();
    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
};

int fatorBalanceamento(NoArvore *n) {
    if (n == NULL) {
        return 0;
    }
    Arvore left, right;
    left.raiz = n->esquerda;
    right.raiz = n->direita;
    return calcularAlturaArvore(&left) - calcularAlturaArvore(&right);
};

int maior(int a, int b) {
    return (a > b) ? a : b;
};

NoArvore* rotacaoDireita(NoArvore *y) {
    NoArvore *x = y->esquerda;
    NoArvore *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    Arvore subLeft, subRight;
    subLeft.raiz = y->esquerda;
    subRight.raiz = y->direita;
    y->altura = 1 + maior(calcularAlturaArvore(&subLeft), calcularAlturaArvore(&subRight));
    subLeft.raiz = x->esquerda;
    subRight.raiz = x->direita;
    x->altura = 1 + maior(calcularAlturaArvore(&subLeft), calcularAlturaArvore(&subRight));

    return x;
};

NoArvore* rotacaoEsquerda(NoArvore *x) {
    NoArvore *y = x->direita;
    NoArvore *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    Arvore subLeft2, subRight2;
    subLeft2.raiz = x->esquerda;
    subRight2.raiz = x->direita;
    x->altura = 1 + maior(calcularAlturaArvore(&subLeft2), calcularAlturaArvore(&subRight2));
    subLeft2.raiz = y->esquerda;
    subRight2.raiz = y->direita;
    y->altura = 1 + maior(calcularAlturaArvore(&subLeft2), calcularAlturaArvore(&subRight2));

    return y;
};

NoArvore* inserirAVL(NoArvore *raiz, Livro *livro){
    if (raiz == NULL){
        return criarNo(livro);
    }

    if (livro->codigo < raiz->livro->codigo){
        raiz->esquerda = inserirAVL(raiz->esquerda, livro);
    }else if (livro->codigo > raiz->livro->codigo){
        raiz->direita = inserirAVL(raiz->direita, livro);
    }else{
        return raiz;
    }
    raiz->altura = 1 + maior(calcularAlturaArvore(&(Arvore){raiz->esquerda}), calcularAlturaArvore(&(Arvore){raiz->direita}));

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

void liberarArvore(NoArvore *no) {
    if (no != NULL) {
        liberarArvore(no->esquerda);
        liberarArvore(no->direita);
        free(no->livro);
        free(no);
    }
};

// Implementação das funções obrigatórias

Arvore * criarArvore (){
    Arvore * arvore = (Arvore *) malloc(sizeof(Arvore));
    if (arvore != NULL) {
        arvore->raiz = NULL;
    }
    return arvore;
};

NoArvore* inserirLivroArvore(Arvore *arvore, Livro *livro) {
    if (arvore == NULL) {
        return NULL;
    }

    arvore->raiz = inserirAVL(arvore->raiz, livro);
    return arvore->raiz;
};

Livro * buscarLivroArvore ( Arvore * arvore , int codigo ){
    NoArvore* atual = arvore -> raiz;
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

NoArvore * buscarNoLivroArvore ( Arvore * arvore , int codigo ){
    NoArvore* atual = arvore -> raiz;
    while (atual != NULL){
        if (codigo == atual -> livro -> codigo){
            return atual;
        }else if (codigo < atual -> livro -> codigo){
            atual = atual -> esquerda;
        }else{
            atual = atual -> direita;
        }
    }
    return NULL;
};

void listarLivrosEmOrdem ( Arvore * arvore ){
    NoArvore * no = arvore -> raiz;
    if (no != NULL){
        Arvore subArvore;
        subArvore.raiz = no->esquerda;
        listarLivrosEmOrdem(&subArvore);
        printf("- Código: %d, Título: %s\n", no -> livro -> codigo, no -> livro -> titulo);
        subArvore.raiz = no->direita;
        listarLivrosEmOrdem(&subArvore);
    }
};

void listarLivrosPreOrdem ( Arvore * arvore ){
    NoArvore * no = arvore -> raiz;
    if (no != NULL){
        printf("Código: %d, Título: %s\n", no -> livro -> codigo, no -> livro -> titulo);
        Arvore subArvore;
        subArvore.raiz = no->esquerda;
        listarLivrosPreOrdem(&subArvore);
        subArvore.raiz = no->direita;
        listarLivrosPreOrdem(&subArvore);
    }
};

void listarLivrosPosOrdem ( Arvore * arvore ){
    NoArvore * no = arvore -> raiz;
    if (no != NULL){
        Arvore subArvore;
        subArvore.raiz = no->esquerda;
        listarLivrosPosOrdem(&subArvore);
        subArvore.raiz = no->direita;
        listarLivrosPosOrdem(&subArvore);
        printf("Código: %d, Título: %s\n", no -> livro -> codigo, no -> livro -> titulo);
    }
};

int contarLivros ( Arvore * arvore ){
    NoArvore * no = arvore -> raiz;
    Arvore * subArvoreEsquerda = (Arvore *) malloc(sizeof(Arvore));
    Arvore * subArvoreDireita = (Arvore *) malloc(sizeof(Arvore));
    if (no == NULL){
        return 0;
    }else{
        subArvoreEsquerda->raiz = no->esquerda;
        subArvoreDireita->raiz = no->direita;
        return 1 + contarLivros(subArvoreEsquerda) + contarLivros(subArvoreDireita);
    }
};

int calcularAlturaArvore ( Arvore * arvore ){
    NoArvore * no = arvore -> raiz;
    if (no == NULL){
        return -1;
    }

    return no->altura;
};

NoArvore* removerNoLivro(NoArvore *raiz, Livro *livro) {
    if(raiz == NULL) {
        printf("Erro: árvore vazia.\n");
        return raiz;
    }
    
    // Busca, recursivamente, o nó pelo código do livro
    if(livro->codigo < raiz->livro->codigo) {
        raiz->esquerda = removerNoLivro(raiz->esquerda, livro);
    } else if (livro->codigo > raiz->livro->codigo) {
        raiz->direita = removerNoLivro(raiz->direita, livro);
    } else {
        // Encontrou o nó
        
        if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {  // Caso o nó possua 0 ou 1 filho
            NoArvore *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if(temp == NULL) { // Sem filhos
                temp = raiz;
                raiz = NULL;
            } else { // 1 filho
                *raiz = *temp; // Nó filho passa a ser a raiz atual
            }
            free(temp);
            free(temp->livro);
        } else { // Caso o nó possua 2 filhos
            NoArvore *temp = menorValorNo(raiz->direita); // Procura sucessor em ordem
            raiz->livro = temp->livro; // Substitui os ponteiros
            raiz->direita = removerNoLivro(raiz->direita, temp->livro); // Remove o sucessor copiado
        }
    }
    
    if(raiz == NULL) return raiz;
    raiz->altura = 1 + maior(raiz->esquerda->altura, raiz->direita->altura);
    int fb = fatorBalanceamento(raiz);
    
    // Rebalanceamento
    // - Caso Esquerda-Esquerda (LL)
    if(fb > 1 && fatorBalanceamento(raiz->esquerda) >= 0) {
        return rotacaoDireita(raiz);
    }
    // - Caso Esquerda-Direita (LR)
    if(fb > 1 && fatorBalanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }
    // - Caso Direita-Direita (RR)
    if(fb < -1 && fatorBalanceamento(raiz->direita) <= 0) {
        return rotacaoEsquerda(raiz);
    }
    // - Caso Direita-Esquerda (RL)
    if(fb < -1 && fatorBalanceamento(raiz->direita) > 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }
    return raiz;
};

NoArvore* menorValorNo(NoArvore* no) {
    NoArvore* atual = no;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
};
