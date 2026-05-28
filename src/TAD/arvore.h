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

NoArvore* rotacaoDireita(NoArvore *y);

NoArvore* rotacaoEsquerda(NoArvore *x);

void liberarArvore(NoArvore *no);