#include<TAD/livro.h>
#include<TAD/listaEncadeada.h>
#include<TAD/fila.h>

#ifndef ACOES_H
#define ACOES_H

int cadastrarNovoLivro(Livro* livro /*TAD Árvore*/) {}
int buscarLivroPorCodigo(Livro* livro /*TAD Árvore*/) {}
int listarLivrosCrescente(/*TAD Árvore*/) {}
int listarLivrosPre(/*TAD Árvore*/) {}
int listarLivrosPos(/*TAD Árvore*/) {}
int emprestimoLivro(Livro* livro, Lista* listaDeEmprestimos) {}
int devolverLivro(Livro* Livro, Lista* listaDeEmprestimos) {}
void exibirReservas(Fila* filaDeReservas) {}
int exibirQuantidadeLivros(/*TAD Árvore*/) {}
int exibirAlturaArvore(/*TAD Árvore*/) {}


#endif ACOES_H
