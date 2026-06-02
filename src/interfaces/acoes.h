#include "../TAD/livro.h"
#include "../TAD/listaEncadeada.h"
#include "../TAD/fila.h"
#include "../TAD/arvore.h"

#ifndef ACOES_H
#define ACOES_H

int cadastrarNovoLivro(Livro *livro, Arvore *arvore);
int removerLivro(Livro *livro, Arvore *arvore, Lista* emprestimos, Fila* reservas);
int buscarLivroPorCodigo(int codigo, Arvore* arvore);
int listarLivrosCrescente(Arvore* arvore);
int listarLivrosPre(Arvore* arvore);
int listarLivrosPos(Arvore* arvore);
int emprestimoLivro(Livro * livro, Lista* listaDeEmprestimos, char * nomeUsuario);
int devolverLivro(Livro* livro, Lista* listaDeEmprestimos, char* nomeUsuario);
void exibirReservas(Fila* filaDeReservas);
int exibirQuantidadeLivros(Arvore* arvore);
int exibirAlturaArvore(Arvore* arvore);

#endif