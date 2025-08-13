#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para armazenar os dados do aluno
struct aluno {
    char nome[81];
    char matricula[8];
    char turma;
    float p1;
    float p2;
    float p3;
};
typedef struct aluno Aluno;

// Protótipos das funções
void inicializa(int n, Aluno** tab);
void adiciona(int n, Aluno** tab, int i);
void retira(int n, Aluno** tab, int i);
void imprime_aprovados(int n, Aluno** tab);
float media_turma(int n, Aluno** turmas, char turma);
void limpar_buffer();

// Função para limpar o buffer de entrada
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inicializa(int n, Aluno** tab) {
    for (int i = 0; i < n; i++) {
        tab[i] = NULL;
    }
}

void adiciona(int n, Aluno** tab, int i) {
    if (i < 0 || i >= n) {
        printf("Indice fora do limite do vetor!\n");
        return;
    }

    if (tab[i] == NULL) {
        tab[i] = (Aluno*) malloc(sizeof(Aluno));
        if (tab[i] == NULL) {
            printf("Erro na alocacao de memoria!\n");
            exit(1);
        }
    }

    printf("--- Inserindo/Atualizando dados do aluno na posicao %d ---\n", i);
    
    printf("Digite o nome: ");
    scanf(" %80[^\n]", tab[i]->nome);
    limpar_buffer();

    printf("Digite a matricula (7 chars): ");
    scanf("%7s", tab[i]->matricula);
    limpar_buffer();

    printf("Digite a turma (A, B, C...): ");
    scanf(" %c", &tab[i]->turma);
    limpar_buffer();

    printf("Digite a nota da P1: ");
    scanf("%f", &tab[i]->p1);
    limpar_buffer();

    printf("Digite a nota da P2: ");
    scanf("%f", &tab[i]->p2);
    limpar_buffer();

    printf("Digite a nota da P3: ");
    scanf("%f", &tab[i]->p3);
    limpar_buffer();
    
    printf("Aluno adicionado/atualizado com sucesso!\n");
}

void retira(int n, Aluno** tab, int i) {
    if (i < 0 || i >= n) {
        printf("Indice fora do limite do vetor!\n");
        return;
    }
    
    if (tab[i] != NULL) {
        free(tab[i]);
        tab[i] = NULL;
        printf("Dados do aluno na posicao %d removidos.\n", i);
    } else {
        printf("Nao ha aluno para remover na posicao %d.\n", i);
    }
}

void imprime_aprovados(int n, Aluno** tab) {
    printf("\n--- Alunos Aprovados (Media > 5.0) ---\n");
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (tab[i] != NULL) {
            float media = (tab[i]->p1 + tab[i]->p2 + tab[i]->p3) / 3.0;
            if (media > 5.0) {
                printf("Matricula: %s | Nome: %s | Turma: %c | Media: %.2f\n", 
                       tab[i]->matricula, tab[i]->nome, tab[i]->turma, media);
                count++;
            }
        }
    }
    if (count == 0) {
        printf("Nenhum aluno aprovado encontrado.\n");
    }
}

/*
 * e) Função que imprime a nota de cada aluno e retorna a média final 
 * dos alunos de uma determinada turma.
 */
float media_turma(int n, Aluno** turmas, char turma) {
    float soma_medias = 0.0;
    int contador_alunos = 0;
    float media_aluno;

    printf("\n--- Detalhes da Turma %c ---\n", turma);

    for (int i = 0; i < n; i++) {
        // Verifica se o aluno pertence à turma especificada
        if (turmas[i] != NULL && turmas[i]->turma == turma) {
            // Calcula a média individual do aluno
            media_aluno = (turmas[i]->p1 + turmas[i]->p2 + turmas[i]->p3) / 3.0;
            
            // Imprime os detalhes do aluno
            printf("Aluno: %-20s | Matricula: %s | Media: %.2f\n", 
                   turmas[i]->nome, turmas[i]->matricula, media_aluno);

            soma_medias += media_aluno;
            contador_alunos++;
        }
    }

    // Se nenhum aluno foi encontrado, imprime uma mensagem
    if (contador_alunos == 0) {
        printf("Nenhum aluno encontrado para a turma %c.\n", turma);
        return 0.0;
    }

    // Retorna a média geral da turma
    return soma_medias / contador_alunos;
}

int main() {
    #define MAX_ALUNOS 50
    Aluno* tab[MAX_ALUNOS];
    int opcao, indice;
    char turma_busca;

    inicializa(MAX_ALUNOS, tab);

    do {
        printf("\n--- MENU DE GERENCIAMENTO DE ALUNOS ---\n");
        printf("1. Adicionar/Atualizar Aluno\n");
        printf("2. Remover Aluno\n");
        printf("3. Imprimir Alunos Aprovados\n");
        printf("4. Calcular Media de uma Turma\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
                printf("Digite a posicao para adicionar/atualizar (0 a %d): ", MAX_ALUNOS - 1);
                scanf("%d", &indice);
                limpar_buffer();
                adiciona(MAX_ALUNOS, tab, indice);
                break;
            case 2:
                printf("Digite a posicao para remover (0 a %d): ", MAX_ALUNOS - 1);
                scanf("%d", &indice);
                limpar_buffer();
                retira(MAX_ALUNOS, tab, indice);
                break;
            case 3:
                imprime_aprovados(MAX_ALUNOS, tab);
                break;
            case 4:
                printf("Digite a turma para calcular a media (A, B, C...): ");
                scanf(" %c", &turma_busca);
                limpar_buffer();
                
                float media_final = media_turma(MAX_ALUNOS, tab, turma_busca);
                
                if (media_final > 0.0) {
                    printf("------------------------------------------------------\n");
                    printf("Media geral da Turma %c: %.2f\n", turma_busca, media_final);
                }
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    for (int i = 0; i < MAX_ALUNOS; i++) {
        if (tab[i] != NULL) {
            free(tab[i]);
        }
    }

    return 0;
}