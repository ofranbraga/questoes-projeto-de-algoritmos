#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    float valor;
    struct lista *prox;
} Lista;

// Função para criar um novo nó
Lista* cria_no(float valor) {
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    if (!novo) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

// Insere no final da lista
Lista* insere_final(Lista* l, float valor) {
    Lista* novo = cria_no(valor);
    if (l == NULL) {
        return novo;
    } else {
        Lista* aux = l;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
        return l;
    }
}

// Função para concatenar duas listas
Lista* concatena(Lista* l1, Lista* l2) {
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    Lista* aux = l1;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = l2;
    return l1;
}

// Função para imprimir a lista
void imprime_lista(Lista* l) {
    Lista* aux = l;
    while (aux != NULL) {
        printf("%.1f -> ", aux->valor);
        aux = aux->prox;
    }
    printf("NULL\n");
}

int main() {
    Lista* l1 = NULL;
    Lista* l2 = NULL;

    // Criando lista 1: 2.1 -> 4.5 -> 1.0
    l1 = insere_final(l1, 2.1);
    l1 = insere_final(l1, 4.5);
    l1 = insere_final(l1, 1.0);

    // Criando lista 2: 7.2 -> 9.8
    l2 = insere_final(l2, 7.2);
    l2 = insere_final(l2, 9.8);

    printf("Lista 1:\n");
    imprime_lista(l1);

    printf("Lista 2:\n");
    imprime_lista(l2);

    // Concatenando
    Lista* resultado = concatena(l1, l2);

    printf("Lista concatenada:\n");
    imprime_lista(resultado);

    return 0;
}
