#include<TAD/livro.h>
#include<TAD/listaEncadeada.h>
#include<TAD/fila.h>
#include<TAD/arvore.h>

#ifndef ACOES_H
#define ACOES_H

int cadastrarNovoLivro(Livro* livro, Arvore* arvore) {}
int buscarLivroPorCodigo(Livro* livro, Arvore* arvore) {}
int listarLivrosCrescente(Arvore* arvore) {}
int listarLivrosPre(Arvore* arvore) {}
int listarLivrosPos(Arvore* arvore) {}
int emprestimoLivro(Livro* livro, Lista* listaDeEmprestimos) {}
int devolverLivro(Livro* Livro, Lista* listaDeEmprestimos) {}
void exibirReservas(Fila* filaDeReservas) {}
int exibirQuantidadeLivros(Arvore* arvore) {}
int exibirAlturaArvore(Arvore* arvore) {}


#endif ACOES_H
