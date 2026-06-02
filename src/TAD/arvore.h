#include "livro.h"

typedef struct NoArvore {
    Livro * livro;
    int altura;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

typedef struct Arvore {
    NoArvore * raiz ;
} Arvore ;

// Requisitos Obrigatórios

Arvore * criarArvore ();

NoArvore* inserirLivroArvore ( Arvore * arvore , Livro * livro );

NoArvore* removerNoLivro(NoArvore *raiz, Livro *Livro);

Livro * buscarLivroArvore ( Arvore * arvore , int codigo );

void listarLivrosEmOrdem ( Arvore * arvore );

void listarLivrosPreOrdem ( Arvore * arvore );

void listarLivrosPosOrdem ( Arvore * arvore );

int contarLivros ( Arvore * arvore );

int calcularAlturaArvore ( Arvore * arvore );

// Opcionais (Implementação de funções auxiliares para balanceamento da árvore AVL)

NoArvore* criarNo(Livro *livro);

int fatorBalanceamento(NoArvore *n);

int maior(int a, int b);

NoArvore *menorValorNo(NoArvore *no);

NoArvore* rotacaoDireita(NoArvore *y);

NoArvore* rotacaoEsquerda(NoArvore *x);

NoArvore* inserirAVL(NoArvore *raiz, Livro *livro);

void liberarArvore(NoArvore *no);