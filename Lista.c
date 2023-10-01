#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definição da estrutura de dados Filme
struct Filme {
    char titulo[150];
    char sinopse[500];
    struct Filme* proximo;
};

// Criação de um tipo Filme
typedef struct Filme Filme;

// Declaração de variáveis globais
Filme* primeiro = NULL;  // Ponteiro para o primeiro filme na lista
Filme* ultimo = NULL;    // Ponteiro para o último filme na lista

// Função para alocar memória para um novo filme
Filme* criarFilme() {
    Filme* novoFilme = (Filme*)calloc(1, sizeof(Filme));  // Usa calloc para inicializar as strings com valores nulos

    if (novoFilme == NULL) {
        printf("!!!! |Erro ao alocar memória.| !!!!\n");
        exit(1);
    }

    return novoFilme;
}

// Função para adicionar um filme à lista
void adicionarFilme() {
    Filme* novoFilme = criarFilme();  // Aloca memória para um novo filme

    printf("|Digite o título do filme: ");
    scanf(" %[^\n]", novoFilme->titulo);  // Lê o título do filme

    printf("|Digite a sinopse do filme: ");
    scanf(" %[^\n]", novoFilme->sinopse);  // Lê a sinopse do filme

    novoFilme->proximo = NULL;  // Inicializa o próximo como nulo

    if (primeiro == NULL) {  // Se a lista está vazia
        primeiro = novoFilme;
        ultimo = novoFilme;
        novoFilme->proximo = primeiro;
    } else {
        ultimo->proximo = novoFilme;  // Adiciona o novo filme no final da lista
        novoFilme->proximo = primeiro;
        ultimo = novoFilme;
    }

    printf("|Filme adicionado com sucesso! :)\n");
}

// Função para contar o número de filmes na lista
int contarFilmes() {
    if (primeiro == NULL) {
        return 0;
    }

    Filme* atual = primeiro;
    int count = 0;

    do {
        count++;
        atual = atual->proximo;
    } while (atual != primeiro);

    return count;
}

// Função para remover filmes da lista
void removerFilmes() {
    int escolha, i;

    if (primeiro == NULL) {
        printf("|||A lista está vazia.|||\n");
        return;
    }

    printf("|Digite o número do filme a ser removido: ");
    scanf("%d", &escolha);

    int totalFilmes = contarFilmes();

    if (escolha < 1 || escolha > totalFilmes) {
        printf("!!!!|Escolha inválida: %d\n", escolha);
        return;
    }

    Filme* atual = primeiro;
    Filme* anterior = NULL;

    // Localiza o filme a ser removido
    for (i = 1; i < escolha; i++) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Exibe o título do filme removido
    printf("!!!!|Filme removido: %s\n", atual->titulo);

    if (anterior != NULL) {
        anterior->proximo = atual->proximo;
    } else {
        primeiro = atual->proximo;
        ultimo->proximo = primeiro;
    }

    free(atual);

    printf("||Filme removido com sucesso.||\n");
}

// Função para listar filmes da lista
void listarFilmes() {
    if (primeiro == NULL) {
        printf("!!!!|Lista vazia.|!!!!\n");
        return;
    }

    Filme* atual = primeiro;
    int numero = 1;

    do {
        printf("%d - %s\n", numero, atual->titulo);
        atual = atual->proximo;
        numero++;
    } while (atual != primeiro);

    int escolha;
    printf("|Selecione um filme pelo número: ");
    scanf("%d", &escolha);

    if (escolha >= 1 && escolha < numero) {
        atual = primeiro;
        int i;
        for (i = 1; i < escolha; i++) {
            atual = atual->proximo;
        }
		system("cls");
        printf(">>>|Título: %s\n", atual->titulo);
        printf(">>>|Sinopse: %s\n", atual->sinopse);
    }

    // Adicionar funcionalidade de navegação
    int opcao;
    int i;
    while (1) {
        printf("\n|1 - Próximo|\n|0 - Voltar ao menu anterior|\n");
        scanf("%d", &opcao);

        if (opcao == 0) {
            return; // Retorna ao menu anterior
        } else if (opcao == 1) {
            atual = atual->proximo;
        } else if (opcao == 2) {
            atual = atual->proximo;
            // Navegar para o filme anterior
            for (i = 1; i < escolha - 1; i++) {
                atual = atual->proximo;
            }
        }
    system("cls");
        printf(">>>|Título: %s\n", atual->titulo);
        printf(">>>|Sinopse: %s\n", atual->sinopse);
    }   
    printf(">>>|Título: %s\n", atual->titulo);
    printf(">>>|Sinopse: %s\n", atual->sinopse);
	
}

void buscarFilmePorTitulo() {
    if (primeiro == NULL) {
        printf(">>>>|Lista vazia.|<<<<\n");
        return;
    }

    char tituloBusca[1050];
    printf("|Digite o título do filme a ser buscado: ");
    scanf(" %[^\n]", tituloBusca);

    Filme* atual = primeiro;
    int encontrado = 0;

    do {
        if (strcmp(atual->titulo, tituloBusca) == 0) {
            printf(">>>|Título: %s\n", atual->titulo);
            printf(">>>|Sinopse: %s\n", atual->sinopse);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    } while (atual != primeiro);

    if (!encontrado) {
        printf("!!! Filme não encontrado na lista. !!!\n");
    }
}
void liberarFilme(Filme* filme) {
    free(filme);
}
// Função para liberar a memória de todos os filmes
void liberarMemoria() {
    Filme* atual = primeiro;
    do {
        Filme* temp = atual;
        atual = atual->proximo;
        liberarFilme(temp); // Libera a memória de cada filme
    } while (atual != primeiro);

    if (primeiro != NULL) {
        liberarFilme(primeiro); // Libera o primeiro filme
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    while (1) {
        printf("\n-----| Menu |-----\n");
        printf("| 1 - Adicionar Filme\n");
        printf("| 2 - Remover Filme\n");
        printf("| 3 - Lista de Filmes Adicionados\n");
        printf("| 4 - Buscar Filme por Título\n"); // Adiciona a opção de busca por título
        printf("| 5 - Encerrar\n");
        printf("_-_-_-|Escolha uma opção|-_-_-_ \n | ");
        scanf("%d", &opcao);
        system("cls"); // Limpa a tela

        switch (opcao) {
            case 1:
                adicionarFilme();
                break;
            case 2:
                removerFilmes();
                break;
            case 3:
                listarFilmes();
                break;
            case 4:
                buscarFilmePorTitulo();
                break;
            case 5:
                liberarMemoria();  // Libera a memória alocada para a lista de filmes
                exit(0);
            default:
                printf("!!! Opção inválida. Tente novamente. !!!\n");
                break;
        }
    }
	
    return 0;
}
