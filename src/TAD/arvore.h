#include "livro.h"
#include "fila.h"

typedef struct NoArvore {
    Livro * livro;
    int altura;
    Fila* filaEspera;
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

// Opcionais (Implementação de funções auxiliares para balanceamento da árvore AVL ou extras)

NoArvore* criarNo(Livro *livro);

int fatorBalanceamento(NoArvore *n);

int maior(int a, int b);

NoArvore *menorValorNo(NoArvore *no);

NoArvore* rotacaoDireita(NoArvore *y);

NoArvore* rotacaoEsquerda(NoArvore *x);

NoArvore* inserirAVL(NoArvore *raiz, Livro *livro);

void liberarArvore(NoArvore *no);

NoArvore * buscarNoLivroArvore ( Arvore * arvore , int codigo );

NoArvore* removerNoLivro(NoArvore *raiz, Livro *livro);