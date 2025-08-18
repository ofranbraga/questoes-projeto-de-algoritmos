#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Nodo {
    char* dado;
    struct Nodo* prox;
} Nodo;

typedef struct {
    Nodo* inicio;
} Lista;

int igual(Lista* l1, Lista* l2) {
    Nodo* p1 = l1->inicio;
    Nodo* p2 = l2->inicio;

    while (p1 != NULL && p2 != NULL) {
        if (strcmp(p1->dado, p2->dado) != 0) {
            return 0;
        }
        p1 = p1->prox;
        p2 = p2->prox;
    }

    if (p1 != NULL || p2 != NULL) {
        return 0;
    }

    return 1;
}

void inicializaLista(Lista* l) {
    l->inicio = NULL;
}

void adiciona(Lista* l, const char* str) {
    Nodo* novo = (Nodo*) malloc(sizeof(Nodo));
    novo->dado = strdup(str);  // duplica a string
    novo->prox = NULL;

    if (l->inicio == NULL) {
        l->inicio = novo;
    } else {
        Nodo* temp = l->inicio;
        while (temp->prox != NULL)
            temp = temp->prox;
        temp->prox = novo;
    }
}

int main(void) {
    setlocale(LC_ALL, "");

    Lista l1, l2;

    inicializaLista(&l1);
    inicializaLista(&l2);

    adiciona(&l1, "banana");
    adiciona(&l1, "ma��");
    adiciona(&l1, "uva");

    adiciona(&l2, "banana");
    adiciona(&l2, "ma��");
    adiciona(&l2, "uva");

    int res = igual(&l1, &l2);
    if (res)
        printf("As listas sao iguais\n");
    else
        printf("As listas sao diferentes\n");

    return 0;
}

