#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquivo.h"

/* Compatibilidade de criação de diretório entre Windows e Unix */
#ifdef _WIN32
    #include <direct.h>
    #define CRIAR_DIR(path)  _mkdir(path)
#else
    #include <sys/stat.h>
    #define CRIAR_DIR(path)  mkdir((path), 0755)
#endif

#define PASTA_DADOS      "data"
#define ARQ_LIVROS       "data/livros.csv"
#define ARQ_EMPRESTIMOS  "data/emprestimos.csv"
#define ARQ_RESERVAS     "data/reservas.csv"

/* =========================================================================
 * Auxiliares internas (estáticas)
 * ========================================================================= */

/* Garante que a pasta 'data/' existe antes de qualquer escrita. */
static void garantirDiretorio(void) {
    CRIAR_DIR(PASTA_DADOS);   /* ignora erro se já existir */
}

/* Percorre a árvore em-ordem e grava cada livro no arquivo. */
static void _salvarLivrosEmOrdem(NoArvore *no, FILE *arq) {
    if (no == NULL) return;
    _salvarLivrosEmOrdem(no->esquerda, arq);
    fprintf(arq, "%d,%s,%s,%d,%d,%d\n",
            no->livro->codigo,
            no->livro->titulo,
            no->livro->autor,
            no->livro->ano,
            no->livro->quantidadeTotal,
            no->livro->quantidadeDisponivel);
    _salvarLivrosEmOrdem(no->direita, arq);
}

/* Percorre a árvore em-ordem e, para cada livro, grava sua fila de reservas. */
static void _salvarReservasEmOrdem(NoArvore *no, FILE *arq) {
    if (no == NULL) return;
    _salvarReservasEmOrdem(no->esquerda, arq);
    NoFila *temp = no->filaEspera->inicio;
    while (temp != NULL) {
        fprintf(arq, "%d,%s\n",
                temp->reserva.codigoLivro,
                temp->reserva.nomeUsuario);
        temp = temp->prox;
    }
    _salvarReservasEmOrdem(no->direita, arq);
}

/* =========================================================================
 * Livros
 * ========================================================================= */

void salvarTodosLivros(Arvore *arvore) {
    if (arvore == NULL) return;
    garantirDiretorio();

    FILE *arq = fopen(ARQ_LIVROS, "w");
    if (arq == NULL) {
        printf("Erro: nao foi possivel salvar '%s'.\n", ARQ_LIVROS);
        return;
    }
    _salvarLivrosEmOrdem(arvore->raiz, arq);
    fclose(arq);
    printf("Livros salvos em '%s'.\n", ARQ_LIVROS);
}

/*
 * Lê livros.csv e insere cada livro na árvore AVL.
 * Restaura quantidadeDisponivel diretamente do arquivo, sem precisar
 * recalcular a partir dos empréstimos.
 */
void carregarLivros(Arvore *arvore) {
    if (arvore == NULL) return;

    FILE *arq = fopen(ARQ_LIVROS, "r");
    if (arq == NULL) return;
    int  codigo, ano, total, disponivel;
    char titulo[100], autor[100];

    while (fscanf(arq, "%d,%99[^,],%99[^,],%d,%d,%d\n",
                &codigo, titulo, autor, &ano, &total, &disponivel) == 6) {
        Livro *livro = criarLivro(codigo, titulo, autor, ano, total);
        if (livro != NULL) {
            livro->quantidadeDisponivel = disponivel;
            inserirLivroArvore(arvore, livro);
        }
    }
    fclose(arq);
    printf("Livros carregados de '%s'.\n", ARQ_LIVROS);
}

/* =========================================================================
 * Empréstimos
 * ========================================================================= */

/*
 * Reescreve emprestimos.csv com todos os empréstimos ativos da lista.
 */
void salvarTodosEmprestimos(Lista *lista) {
    if (lista == NULL) return;
    garantirDiretorio();

    FILE *arq = fopen(ARQ_EMPRESTIMOS, "w");
    if (arq == NULL) {
        printf("Erro: nao foi possivel salvar '%s'.\n", ARQ_EMPRESTIMOS);
        return;
    }
    NoLista *no = lista->inicio;
    while (no != NULL) {
        fprintf(arq, "%s,%d,%s\n",
                no->emprestimo.nomeUsuario,
                no->emprestimo.codigoLivro,
                no->emprestimo.tituloLivro);
        no = no->prox;
    }
    fclose(arq);
    printf("Emprestimos salvos em '%s'.\n", ARQ_EMPRESTIMOS);
}

/*
 * Lê emprestimos.csv e insere cada registro na lista encadeada.
 * Não altera quantidadeDisponivel dos livros (isso já vem de livros.csv).
 */
void carregarEmprestimos(Lista *lista) {
    if (lista == NULL) return;

    FILE *arq = fopen(ARQ_EMPRESTIMOS, "r");
    if (arq == NULL) return;

    Emprestimo e;
    while (fscanf(arq, "%99[^,],%d,%99[^\n]\n",
                e.nomeUsuario, &e.codigoLivro, e.tituloLivro) == 3) {
        inserirEmprestimo(lista, e);
    }
    fclose(arq);
    printf("Emprestimos carregados de '%s'.\n", ARQ_EMPRESTIMOS);
}

/* =========================================================================
 * Reservas
 * ========================================================================= */

/*
 * Reescreve reservas.csv percorrendo a fila de espera de cada livro da árvore.
 * Formato: codigoLivro,nomeUsuario  (uma linha por reserva, em ordem de fila).
 */
void salvarTodasReservas(Arvore *arvore) {
    if (arvore == NULL) return;
    garantirDiretorio();

    FILE *arq = fopen(ARQ_RESERVAS, "w");
    if (arq == NULL) {
        printf("Erro: nao foi possivel salvar '%s'.\n", ARQ_RESERVAS);
        return;
    }
    _salvarReservasEmOrdem(arvore->raiz, arq);
    fclose(arq);
    printf("Reservas salvas em '%s'.\n", ARQ_RESERVAS);
}

/*
 * Lê reservas.csv e reinsere cada reserva na fila do livro correspondente.
 * Depende de os livros já terem sido carregados (carregarLivros primeiro).
 */
void carregarReservas(Arvore *arvore) {
    if (arvore == NULL) return;

    FILE *arq = fopen(ARQ_RESERVAS, "r");
    if (arq == NULL) return;

    int  codigoLivro;
    char nomeUsuario[100];

    while (fscanf(arq, "%d,%99[^\n]\n", &codigoLivro, nomeUsuario) == 2) {
        NoArvore *no = buscarNoLivroArvore(arvore, codigoLivro);
        if (no != NULL) {
            Reserva r;
            r.codigoLivro = codigoLivro;
            strcpy(r.nomeUsuario, nomeUsuario);
            enfileirarReserva(no->filaEspera, r);
        }
    }
    fclose(arq);
    printf("Reservas carregadas de '%s'.\n", ARQ_RESERVAS);
}