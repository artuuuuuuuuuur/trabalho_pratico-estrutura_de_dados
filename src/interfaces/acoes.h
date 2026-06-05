#include "../TAD/livro.h"
#include "../TAD/listaEncadeada.h"
#include "../TAD/fila.h"
#include "../TAD/arvore.h"

#ifndef ACOES_H
#define ACOES_H

int cadastrarNovoLivro(Arvore *arvore);
int removerLivro(Livro *livro, Arvore *arvore, Lista* emprestimos, Fila* reservas);
int buscarLivroPorCodigo(Arvore* arvore);
int listarLivrosCrescente(Arvore* arvore);
int listarLivrosPre(Arvore* arvore);
int listarLivrosPos(Arvore* arvore);
int emprestimoLivro(Arvore* arvore, Lista* listaDeEmprestimos, Fila* filaDeReservas);
int devolverLivro(Arvore* arvore, Lista* listaDeEmprestimos, Fila* filaDeReservas);
int imprimirReservas(Fila* filaDeReservas);
int imprimirEmprestimos(Lista* listaDeEmprestimos);
int exibirQuantidadeLivros(Arvore* arvore);
int exibirAlturaArvore(Arvore* arvore);

#endif