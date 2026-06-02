#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h" 

//Criação do livro 
Livro* criarLivro(
    int codigo,
    char titulo[],
    char autor[],
    int ano,
    int quantidadeTotal
)
{
    Livro *livro = (Livro*) malloc(sizeof(Livro));

    if (livro != NULL)
    {
        livro->codigo = codigo;
        strcpy(livro->titulo, titulo);
        strcpy(livro->autor, autor);
        livro->ano = ano;
        livro->quantidadeTotal = quantidadeTotal;
        livro->quantidadeDisponivel = quantidadeTotal; 
    }


    return livro;
}

void exibirLivro(Livro *livro)
{
    if (livro != NULL)
    {
        printf("Codigo: %d\n", livro->codigo);
        printf("Titulo: %s\n", livro->titulo);
        printf("Autor: %s\n", livro->autor);
        printf("Ano: %d\n", livro->ano);
        printf("Quantidade Total: %d\n", livro->quantidadeTotal);
        printf("Quantidade Disponivel: %d\n", livro->quantidadeDisponivel);
    }
    
}

int obterCodigoLivro(Livro *livro)
{
    if (livro != NULL)
    {
        return livro->codigo;
    }
    return -1; // Retorno de erro
}

int obterQuantidadeDisponivel(Livro *livro)
{
    if (livro != NULL)
    {
        return livro->quantidadeDisponivel;
    }
    return 0; // Se o livro não existe, a quantidade disponível é zero
}


void emprestarExemplar(Livro *livro)
{
   
    if (livro != NULL && livro->quantidadeDisponivel > 0)
    {
        livro->quantidadeDisponivel--;
    
    }
}

void devolverExemplar(Livro *livro)
{
    if (livro != NULL && livro->quantidadeDisponivel < livro->quantidadeTotal)
    {
        livro->quantidadeDisponivel++;
    }
}