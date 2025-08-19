/*
Para concatenar duas pilhas p1 e p2, colocando todos os elementos de p2 no topo de p1 mantendo a ordem, usamos uma pilha auxiliar.
*/
void concatena_pilhas(Pilha* p1, Pilha* p2) {
    Pilha* aux = pilha_cria();
    while (!pilha_vazia(p2)) {
        pilha_push(aux, pilha_pop(p2));
    }
    while (!pilha_vazia(aux)) {
        pilha_push(p1, pilha_pop(aux));
    }
    pilha_libera(aux);
}
