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

NoArvore* criarNo(Livro *livro);

int fatorBalanceamento(NoArvore *n);

int maior(int a, int b);

NoArvore* rotacaoDireita(NoArvore *y);

NoArvore* rotacaoEsquerda(NoArvore *x);

Arvore * criarArvore ();

NoArvore* inserirLivroArvore ( NoArvore * raiz , Livro * livro );

Livro * buscarLivroArvore ( NoArvore * no , int codigo );

void listarLivrosEmOrdem ( NoArvore * no );

void listarLivrosPreOrdem ( NoArvore * no );

void listarLivrosPosOrdem ( NoArvore * no );

int contarLivros ( NoArvore * no );

int calcularAlturaArvore ( NoArvore * no );

void liberarArvore(NoArvore *no);