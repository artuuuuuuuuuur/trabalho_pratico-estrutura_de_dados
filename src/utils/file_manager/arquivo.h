#include "../../TAD/arvore.h"
#include "../../TAD/listaEncadeada.h"

#ifndef ARQUIVO_H
#define ARQUIVO_H

/* Livros ------------------------------------------------------------------ */
void salvarTodosLivros(Arvore *arvore);
void carregarLivros(Arvore *arvore);

/* Empréstimos ------------------------------------------------------------- */
void salvarTodosEmprestimos(Lista *lista);
void carregarEmprestimos(Lista *lista);

/* Reservas ---------------------------------------------------------------- */
void salvarTodasReservas(Arvore *arvore);
void carregarReservas(Arvore *arvore);

#endif