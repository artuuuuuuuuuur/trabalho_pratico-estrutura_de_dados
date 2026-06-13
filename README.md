# 📚 Sistema de Gerenciamento de Biblioteca

> Trabalho Prático — Estrutura de Dados (2026.1) | UECE
> Professor: Bonfim Amaro Junior

---

## 👥 Equipe

| Nome                                  |
| ------------------------------------- |
| Helen Braga Alves                     |
| Artur de Maria Ribeiro                |
| Fernando Bruno Façanha de Albuquerque |

---

## 📋 Descrição do Sistema

Sistema de gerenciamento de acervo bibliotecário desenvolvido em **linguagem C**, utilizando Tipos Abstratos de Dados (TADs) e estruturas de dados implementadas manualmente, sem uso de bibliotecas externas para armazenamento.

O sistema permite cadastrar livros, realizar buscas, controlar empréstimos e devoluções, gerenciar filas de reserva por livro e manter um histórico completo das operações.

### Estruturas de Dados Utilizadas

| Estrutura                      | Implementação                         | Finalidade                                                              |
| ------------------------------ | ------------------------------------- | ----------------------------------------------------------------------- |
| 🌳 Árvore AVL (ABB balanceada) | `arvore.h / arvore.c`                 | Armazenamento e busca de livros por código com balanceamento automático |
| 📋 Fila (FIFO)                 | `fila.h / fila.c`                     | Fila de reservas por livro, vinculada a cada nó da árvore               |
| 🔗 Lista Encadeada             | `listaEncadeada.h / listaEncadeada.c` | Histórico global de empréstimos ativos                                  |

> **Destaque:** a árvore implementada vai além do requisito mínimo — trata-se de uma **Árvore AVL**, que realiza rotações automáticas (LL, RR, LR, RL) para manter o balanceamento após cada inserção ou remoção, garantindo O(log n) em todos os casos.

---

## 🗂️ Estrutura do Projeto

```
trabalho_biblioteca/
│
├── main.c                        # Menu principal e integração dos módulos
├── src/
│   ├── interfaces/
│   │   ├── acoes.h               # Declaração das ações do menu
│   │   └── acoes.c               # Implementação das ações do menu
│   │
│   ├── TAD/
│   │   ├── livro.h               # Definição do TAD Livro
│   │   ├── livro.c               # Implementação do TAD Livro
│   │   ├── arvore.h              # Definição da Árvore AVL
│   │   ├── arvore.c              # Implementação da Árvore AVL
│   │   ├── fila.h                # Definição da Fila de Reservas
│   │   ├── fila.c                # Implementação da Fila
│   │   ├── listaEncadeada.h      # Definição da Lista de Histórico
│   │   └── listaEncadeada.c      # Implementação da Lista Encadeada
│   │
│   └── utils/
│       ├── utils.h               # Utilitários (leitura de input, buffer)
│       └── utils.c               # Implementação dos utilitários
│
├── main.c                        # Comando PowerShell para compilar projeto de forma simples
└── README.md                     # Este arquivo
└── .gitignore                    # Especificação de arquivos/diretórios a serem ignorados pelo Git
```

---

## ⚙️ Compilação

### Pré-requisitos

- Compilador **GCC** instalado
- Sistema operacional Linux, macOS ou Windows (com MinGW ou WSL)

### Comando de compilação

Caso você esteja em um Windows, execute:

```bash
./build.ps1
```

Se não,

```bash
gcc main.c src/interfaces/acoes.c src/TAD/livro.c src/TAD/arvore.c src/TAD/fila.c src/TAD/listaEncadeada.c src/utils/utils.c -o biblioteca
```

### Com avisos ativados (recomendado para desenvolvimento)

```bash
gcc -Wall -Wextra main.c src/interfaces/acoes.c src/TAD/livro.c src/TAD/arvore.c src/TAD/fila.c src/TAD/listaEncadeada.c src/utils/utils.c -o biblioteca
```

> **Nota:** o programa usa `setlocale(LC_ALL, "pt_BR.UTF-8")` para suporte a caracteres acentuados. Certifique-se de que seu sistema possui o locale `pt_BR.UTF-8` disponível.

---

## ▶️ Execução

**Linux / macOS:**

```bash
./biblioteca
```

**Windows:**

```bash
biblioteca.exe
```

**Windows PowerShell:**

```bash
./build.ps1
```

---

## 🖥️ Menu do Sistema

```
========== Menu Principal ==========
1  - Cadastrar Novo Livro
2  - Buscar Livro
3  - Listar livros em ordem crescente de código
4  - Listar livros em pré-ordem
5  - Listar livros em pós-ordem
6  - Realizar empréstimo de livro
7  - Devolver livro
8  - Remover livro
9  - Exibir fila de reservas
10 - Exibir histórico de empréstimos
11 - Exibir quantidade de livros cadastrados
12 - Exibir altura da árvore
0  - Sair
=====================================
```

---

## 💡 Exemplos de Uso

### 1. Cadastrando um livro

```
=== Cadastrar Livro ===
  Codigo: 101
  Titulo (max 99 char): Algoritmos em C
  Autor (max 99 char): Robert Sedgewick
  Ano: 1997
  Quantidade total: 3

Livro cadastrado com sucesso.
```

> Tentativa de cadastrar código duplicado resulta em erro e retorno ao menu.

### 2. Buscando um livro

```
=== Buscar livro por codigo ===
Codigo: 101

======= Livro encontrado =======
Código: 101
Título: Algoritmos em C
Autor: Robert Sedgewick
Ano: 1997
Quantidade Total: 3
Quantidade Disponível: 3
=========================================
```

### 3. Realizando um empréstimo com exemplar disponível

```
======= Empréstimo de Livros =======
  Codigo: 101
  Nome do Usuario: João Silva

Empréstimo feito com sucesso!
```

### 4. Tentando emprestar livro sem exemplares disponíveis

```
======= Empréstimo de Livros =======
  Codigo: 101
  Nome do Usuario: Maria Souza

Sem mais exemplares disponíveis!
Deseja adicionar o usuário à fila de reservas? (S / N): S

Adicionado à fila de reservas!
```

### 5. Devolvendo um livro com reservas pendentes (atendimento automático)

```
======= Devolução de Livros =======
  Codigo: 101
  Nome do Usuario: João Silva

Empréstimo deletado.
```

> O sistema verifica automaticamente se há reservas na fila do livro. Se houver, o primeiro usuário da fila recebe o exemplar de forma automática e a reserva é removida da fila.

### 6. Removendo um livro

```
======= Remover Livros =======
  Código: 101

Livro removido com sucesso.
```

> Se o livro possuir empréstimos ativos ou reservas pendentes, a remoção é bloqueada e o sistema exibe as pendências encontradas.

### 7. Listagem em ordem crescente de código

```
==== Lista de livros em ordem crescente ====
- Código: 50,  Título: The C Programming Language
- Código: 101, Título: Algoritmos em C
- Código: 204, Título: Estrutura de Dados e Algoritmos
=====================================
```

---

## ✅ Funcionalidades Implementadas

### Obrigatórias

- [x] TAD `Livro` com controle de exemplares disponíveis
- [x] TAD `Reserva` (fila FIFO por livro)
- [x] TAD `Emprestimo` (lista encadeada global)
- [x] Árvore Binária de Busca com inserção por código
- [x] Percurso em ordem, pré-ordem e pós-ordem
- [x] Busca de livro por código
- [x] Contagem de nós da árvore
- [x] Cálculo da altura da árvore
- [x] Fila de reservas por livro (política FIFO)
- [x] Lista encadeada de histórico de empréstimos
- [x] Cadastro com validação de código duplicado
- [x] Empréstimo com verificação de disponibilidade
- [x] Devolução com busca por código e nome do usuário
- [x] Liberação de memória ao encerrar (`liberarArvore`, `liberarLista`, `liberarFila`)
- [x] Menu interativo com limpeza de tela

### Extras Implementados

- [x] **Árvore AVL** — balanceamento automático com rotações (LL, RR, LR, RL), garantindo O(log n) mesmo no pior caso
- [x] **Remoção de livro da árvore** com rebalanceamento AVL e bloqueio por pendências
- [x] **Atendimento automático da fila de reservas** na devolução — o primeiro usuário da fila recebe o exemplar sem interação manual
- [x] **Fila de reservas vinculada ao nó** — cada livro possui sua própria fila, eliminando ambiguidade
- [x] **Módulo `utils`** — funções auxiliares de leitura segura de strings (`getString`) e limpeza de buffer (`limparBuffer`)
- [x] **Módulo `acoes`** — camada de interface entre o menu e as estruturas de dados, com retorno de status para controle de fluxo

### Planejado / Em desenvolvimento

- [ ] Salvamento e carregamento de dados em arquivo

---

## ⚠️ Limitações Conhecidas

- Os dados **não são persistidos** entre execuções — ao fechar o programa, todas as informações são perdidas (funcionalidade de arquivo planejada)
- A busca é feita **exclusivamente por código**; busca por título ou autor não está disponível
- O comando `system("cls")` para limpar a tela é compatível apenas com **Windows**. Em Linux/macOS, substitua por `system("clear")`

---

## 📊 Complexidade das Operações

| Operação                      | Caso Médio | Pior Caso    | Observação                         |
| ----------------------------- | ---------- | ------------ | ---------------------------------- |
| Inserção na AVL               | O(log n)   | **O(log n)** | Balanceamento garante pior caso    |
| Busca na AVL                  | O(log n)   | **O(log n)** | Idem                               |
| Remoção na AVL                | O(log n)   | **O(log n)** | Com rebalanceamento pós-remoção    |
| Percurso em ordem / pré / pós | O(n)       | O(n)         | Visita todos os nós                |
| Inserção na fila              | O(1)       | O(1)         | Acesso direto ao ponteiro `fim`    |
| Remoção da fila               | O(1)       | O(1)         | Acesso direto ao ponteiro `inicio` |
| Inserção na lista             | O(n)       | O(n)         | Percorre até o último nó           |
| Remoção da lista              | O(n)       | O(n)         | Busca linear por código e nome     |

> A escolha da **Árvore AVL** elimina o pior caso O(n) da ABB simples (que ocorreria com inserções ordenadas), garantindo desempenho logarítmico consistente em todas as operações sobre o acervo.
