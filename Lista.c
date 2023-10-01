#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Defini��o da estrutura de dados Filme
struct Filme {
    char titulo[150];
    char sinopse[500];
    struct Filme* proximo;
};

// Cria��o de um tipo Filme
typedef struct Filme Filme;

// Declara��o de vari�veis globais
Filme* primeiro = NULL;  // Ponteiro para o primeiro filme na lista
Filme* ultimo = NULL;    // Ponteiro para o �ltimo filme na lista

// Fun��o para alocar mem�ria para um novo filme
Filme* criarFilme() {
    Filme* novoFilme = (Filme*)calloc(1, sizeof(Filme));  // Usa calloc para inicializar as strings com valores nulos

    if (novoFilme == NULL) {
        printf("!!!! |Erro ao alocar mem�ria.| !!!!\n");
        exit(1);
    }

    return novoFilme;
}

// Fun��o para adicionar um filme � lista
void adicionarFilme() {
    Filme* novoFilme = criarFilme();  // Aloca mem�ria para um novo filme

    printf("|Digite o t�tulo do filme: ");
    scanf(" %[^\n]", novoFilme->titulo);  // L� o t�tulo do filme

    printf("|Digite a sinopse do filme: ");
    scanf(" %[^\n]", novoFilme->sinopse);  // L� a sinopse do filme

    novoFilme->proximo = NULL;  // Inicializa o pr�ximo como nulo

    if (primeiro == NULL) {  // Se a lista est� vazia
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

// Fun��o para contar o n�mero de filmes na lista
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

// Fun��o para remover filmes da lista
void removerFilmes() {
    int escolha, i;

    if (primeiro == NULL) {
        printf("|||A lista est� vazia.|||\n");
        return;
    }

    printf("|Digite o n�mero do filme a ser removido: ");
    scanf("%d", &escolha);

    int totalFilmes = contarFilmes();

    if (escolha < 1 || escolha > totalFilmes) {
        printf("!!!!|Escolha inv�lida: %d\n", escolha);
        return;
    }

    Filme* atual = primeiro;
    Filme* anterior = NULL;

    // Localiza o filme a ser removido
    for (i = 1; i < escolha; i++) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Exibe o t�tulo do filme removido
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

// Fun��o para listar filmes da lista
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
    printf("|Selecione um filme pelo n�mero: ");
    scanf("%d", &escolha);

    if (escolha >= 1 && escolha < numero) {
        atual = primeiro;
        int i;
        for (i = 1; i < escolha; i++) {
            atual = atual->proximo;
        }
		system("cls");
        printf(">>>|T�tulo: %s\n", atual->titulo);
        printf(">>>|Sinopse: %s\n", atual->sinopse);
    }

    // Adicionar funcionalidade de navega��o
    int opcao;
    int i;
    while (1) {
        printf("\n|1 - Pr�ximo|\n|0 - Voltar ao menu anterior|\n");
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
        printf(">>>|T�tulo: %s\n", atual->titulo);
        printf(">>>|Sinopse: %s\n", atual->sinopse);
    }   
    printf(">>>|T�tulo: %s\n", atual->titulo);
    printf(">>>|Sinopse: %s\n", atual->sinopse);
	
}

void buscarFilmePorTitulo() {
    if (primeiro == NULL) {
        printf(">>>>|Lista vazia.|<<<<\n");
        return;
    }

    char tituloBusca[1050];
    printf("|Digite o t�tulo do filme a ser buscado: ");
    scanf(" %[^\n]", tituloBusca);

    Filme* atual = primeiro;
    int encontrado = 0;

    do {
        if (strcmp(atual->titulo, tituloBusca) == 0) {
            printf(">>>|T�tulo: %s\n", atual->titulo);
            printf(">>>|Sinopse: %s\n", atual->sinopse);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    } while (atual != primeiro);

    if (!encontrado) {
        printf("!!! Filme n�o encontrado na lista. !!!\n");
    }
}
void liberarFilme(Filme* filme) {
    free(filme);
}
// Fun��o para liberar a mem�ria de todos os filmes
void liberarMemoria() {
    Filme* atual = primeiro;
    do {
        Filme* temp = atual;
        atual = atual->proximo;
        liberarFilme(temp); // Libera a mem�ria de cada filme
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
        printf("| 4 - Buscar Filme por T�tulo\n"); // Adiciona a op��o de busca por t�tulo
        printf("| 5 - Encerrar\n");
        printf("_-_-_-|Escolha uma op��o|-_-_-_ \n | ");
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
                liberarMemoria();  // Libera a mem�ria alocada para a lista de filmes
                exit(0);
            default:
                printf("!!! Op��o inv�lida. Tente novamente. !!!\n");
                break;
        }
    }
	
    return 0;
}
