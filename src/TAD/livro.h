#ifndef LIVRO_H
#define LIVRO_H

typedef struct
{
    int codigo;                  
    char titulo[100];         
    char autor[100];             
    int ano;                  
    int quantidadeTotal;        
    int quantidadeDisponivel;    
} Livro;

// Criação do livro 

Livro* criarLivro(
    int codigo,
    char titulo[],
    char autor[],
    int ano,
    int quantidadeTotal
);

void exibirLivro(Livro *livro);

// Funções para acessar os dados encapsulados de forma segura
int obterCodigoLivro(Livro *livro);
int obterQuantidadeDisponivel(Livro *livro);

// Funções que alteram o estado da quantidade disponível do livro
void emprestarExemplar(Livro *livro);
void devolverExemplar(Livro *livro);

#endif