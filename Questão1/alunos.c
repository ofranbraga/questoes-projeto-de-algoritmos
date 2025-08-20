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
    }//verifica se o índice é válido

    if (tab[i] == NULL) {// se não existe aluno nesse índice
        tab[i] = (Aluno*) malloc(sizeof(Aluno));// aloca memória
        if (tab[i] == NULL) {
            printf("Erro na alocacao de memoria!\n");
            exit(1);
        }
    }
    // os scanf leem dados do aluno via teclado e armazena na estrutura
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
    } // índice válido?
    
    if (tab[i] != NULL) { //se existe aluno na posição
        free(tab[i]); // libera memória alocada 
        tab[i] = NULL; // marca como vazio novamente
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

void salvar_alunos_em_arquivo(int n, Aluno** tab, const char* notas) {
    FILE* f = fopen(notas, "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo %s\n", notas);
        return;
    }

    fprintf(f, "===== LISTA DE ALUNOS =====\n\n");

    for (int i = 0; i < n; i++) {
        if (tab[i] != NULL) {
            float media = (tab[i]->p1 + tab[i]->p2 + tab[i]->p3) / 3.0;
            fprintf(f, "Matricula: %s\n", tab[i]->matricula);
            fprintf(f, "Nome: %s\n", tab[i]->nome);
            fprintf(f, "Turma: %c\n", tab[i]->turma);
            fprintf(f, "Notas: P1=%.2f | P2=%.2f | P3=%.2f\n", tab[i]->p1, tab[i]->p2, tab[i]->p3);
            fprintf(f, "Media Final: %.2f\n", media);
            fprintf(f, "------------------------------------------\n");
        }
    }

    fclose(f);
    printf("Dados salvos em '%s' com sucesso!\n", notas);
}


void remover_aluno_do_arquivo(const char* notas, const char* matricula) {
    FILE* f = fopen(notas, "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo %s\n", notas);
        return;
    }

    FILE* temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(f);
        return;
    }

    char linha[200];
    int pular = 0; // flag para ignorar bloco do aluno

    while (fgets(linha, sizeof(linha), f)) {
        // Se encontrar a matrícula pedida, começa a pular até o próximo separador
        if (strstr(linha, "Matricula:") && strstr(linha, matricula)) {
            pular = 1;
            printf("Aluno com matrícula %s removido do arquivo.\n", matricula);
        }

        if (!pular) {
            fputs(linha, temp);
        }

        // Detecta fim do bloco do aluno
        if (pular && strstr(linha, "------------------------------------------")) {
            pular = 0; // volta a escrever as próximas linhas
        }
    }

    fclose(f);
    fclose(temp);


    remove(notas);
    rename("temp.txt", notas);
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
        printf("5. Salvar Alunos em Arquivo\n");
        printf("6. Remover Aluno do Arquivo\n");
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
                case 5:
                    salvar_alunos_em_arquivo(MAX_ALUNOS, tab, "notas.txt");
                    break;
                case 6:
                    printf("Digite a matrícula do aluno a remover do arquivo: ");
                    char mat[8];
                    scanf("%7s", mat);
                    limpar_buffer();
                    remover_aluno_do_arquivo("notas.txt", mat);
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