#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITULO 100
#define MAX_AUTOR 100

// Armazenar as informações de um livro
typedef struct {
    int id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int ano;
} Livro;

// Gerenciar a biblioteca
typedef struct {
    Livro *livros;
    int tamanho;
    int capacidade;
} Biblioteca;

// Auxiliares
void inicializarBiblioteca(Biblioteca *biblioteca) {
    biblioteca->tamanho = 0;
    biblioteca->capacidade = 10;
    biblioteca->livros = (Livro *)malloc(biblioteca->capacidade * sizeof(Livro));
}

void redimensionarBiblioteca(Biblioteca *biblioteca) {
    biblioteca->capacidade *= 2;
    biblioteca->livros = (Livro *)realloc(biblioteca->livros, biblioteca->capacidade * sizeof(Livro));
}

void adicionarLivro(Biblioteca *biblioteca) {
    if (biblioteca->tamanho == biblioteca->capacidade) {
        redimensionarBiblioteca(biblioteca);
    }

    Livro novoLivro;
    novoLivro.id = biblioteca->tamanho + 1; // ID único

    printf("\nDigite o título do livro: ");
    getchar(); // Limpar buffer do teclado
    fgets(novoLivro.titulo, MAX_TITULO, stdin);
    novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = '\0';
    printf("Digite o autor do livro: ");
    fgets(novoLivro.autor, MAX_AUTOR, stdin);
    novoLivro.autor[strcspn(novoLivro.autor, "\n")] = '\0';

    printf("Digite o ano de publicação: ");
    scanf("%d", &novoLivro.ano);

    biblioteca->livros[biblioteca->tamanho] = novoLivro;
    biblioteca->tamanho++;

    printf("\nLivro adicionado com sucesso!\n");
}

void removerLivro(Biblioteca *biblioteca) {
    int id;
    printf("\nDigite o ID do livro a ser removido: ");
    scanf("%d", &id);

    int encontrado = 0;
    for (int i = 0; i < biblioteca->tamanho; i++) {
        if (biblioteca->livros[i].id == id) {
            encontrado = 1;
            for (int j = i; j < biblioteca->tamanho - 1; j++) {
                biblioteca->livros[j] = biblioteca->livros[j + 1];
            }
            biblioteca->tamanho--;
            printf("\nLivro removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nLivro com ID %d não encontrado.\n", id);
    }
}

void listarLivros(Biblioteca *biblioteca) {
    if (biblioteca->tamanho == 0) {
        printf("\nNenhum livro na biblioteca.\n");
        return;
    }

    printf("\nLista de Livros:\n");
    for (int i = 0; i < biblioteca->tamanho; i++) {
        Livro l = biblioteca->livros[i];
        printf("ID: %d | Título: %s | Autor: %s | Ano: %d\n", l.id, l.titulo, l.autor, l.ano);
    }
}

void salvarBiblioteca(Biblioteca *biblioteca) {
    FILE *arquivo = fopen("biblioteca.dat", "wb");
    if (arquivo == NULL) {
        printf("\nErro ao salvar a biblioteca.\n");
        return;
    }

    fwrite(&biblioteca->tamanho, sizeof(int), 1, arquivo);
    fwrite(biblioteca->livros, sizeof(Livro), biblioteca->tamanho, arquivo);

    fclose(arquivo);
    printf("\nBiblioteca salva com sucesso!\n");
}

void carregarBiblioteca(Biblioteca *biblioteca) {
    FILE *arquivo = fopen("biblioteca.dat", "rb");
    if (arquivo == NULL) {
        printf("\nNenhum arquivo de biblioteca encontrado.\n");
        return;
    }

    fread(&biblioteca->tamanho, sizeof(int), 1, arquivo);
    biblioteca->livros = (Livro *)realloc(biblioteca->livros, biblioteca->tamanho * sizeof(Livro));
    fread(biblioteca->livros, sizeof(Livro), biblioteca->tamanho, arquivo);

    fclose(arquivo);
    printf("\nBiblioteca carregada com sucesso!\n");
}

void buscarLivro(Biblioteca *biblioteca) {
    char termo[MAX_TITULO];
    printf("\nDigite o título ou autor para buscar: ");
    getchar();
    fgets(termo, MAX_TITULO, stdin);
    termo[strcspn(termo, "\n")] = '\0';

    printf("\nResultados da busca:\n");
    for (int i = 0; i < biblioteca->tamanho; i++) {
        if (strstr(biblioteca->livros[i].titulo, termo) || strstr(biblioteca->livros[i].autor, termo)) {
            Livro l = biblioteca->livros[i];
            printf("ID: %d | Título: %s | Autor: %s | Ano: %d\n", l.id, l.titulo, l.autor, l.ano);
        }
    }
}

int main() {
    Biblioteca biblioteca;
    inicializarBiblioteca(&biblioteca);

    int opcao;
    carregarBiblioteca(&biblioteca);

    do {
        printf("\n===== Gerenciador de Biblioteca =====\n");
        printf("1. Adicionar livro\n");
        printf("2. Remover livro\n");
        printf("3. Buscar livro\n");
        printf("4. Listar todos os livros\n");
        printf("5. Salvar biblioteca\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarLivro(&biblioteca);
                break;
            case 2:
                removerLivro(&biblioteca);
                break;
            case 3:
                buscarLivro(&biblioteca);
                break;
            case 4:
                listarLivros(&biblioteca);
                break;
            case 5:
                salvarBiblioteca(&biblioteca);
                break;
            case 6:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 6);

    free(biblioteca.livros);
    return 0;
}
