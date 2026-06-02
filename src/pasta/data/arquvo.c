#include <stdio.h>
#include "arquivo.h"
#include <stdio.h>
#include "TAD/livro.h"
#include "TAD/arvore.h"
#include "TAD/listaEncadeada.h"

void salvarLivro(Livro *livro)
{
    FILE *arquivo = fopen("arquivo/livros.csv", "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(
        arquivo,
        "%d,%s,%s,%d,%d\n",
        livro->codigo,
        livro->titulo,
        livro->autor,
        livro->ano,
        livro->quantidadeTotal
    );

    fclose(arquivo);
}

void carregarLivros(Arvore *arvore)
{
    FILE *arquivo = fopen("arquivo/livros.csv", "r");

    if (arquivo == NULL)
    {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    int codigo;
    int ano;
    int quantidadeTotal;

    char titulo[100];
    char autor[100];

    while (
        fscanf(
            arquivo,
            "%d,%99[^,],%99[^,],%d,%d\n",
            &codigo,
            titulo,
            autor,
            &ano,
            &quantidadeTotal
        ) == 5
    )
    {
        Livro *livro = criarLivro(
            codigo,
            titulo,
            autor,
            ano,
            quantidadeTotal
        );

        inserirLivroArvore(arvore, livro);
    }

    fclose(arquivo);
}

void salvarEmprestimo(Emprestimo emprestimo)
{
    FILE *arquivo = fopen("arquivo/emprestimos.csv", "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir emprestimos.csv\n");
        return;
    }

    fprintf(
        arquivo,
        "%s,%d,%s\n",
        emprestimo.nomeUsuario,
        emprestimo.codigoLivro,
        emprestimo.tituloLivro
    );
    }
    fclose(arquivo);



void carregarEmprestimos(Lista *lista)
{
    FILE *arquivo = fopen("arquivo/emprestimos.csv", "r");

    if (arquivo == NULL)
    {
        printf("emprestimos.csv nao encontrado.\n");
        return;
    }

    Emprestimo emprestimo;

    while (
        fscanf(
            arquivo,
            "%99[^,],%d,%99[^\n]\n",
            emprestimo.nomeUsuario,
            &emprestimo.codigoLivro,
            emprestimo.tituloLivro
        ) == 3
    )
    {
        inserirEmprestimo(lista, emprestimo);
    }

    fclose(arquivo);
}