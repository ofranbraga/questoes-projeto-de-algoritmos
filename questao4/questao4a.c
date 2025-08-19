/*
A funcao topo(), verifica qual o topo da pilha com a funcao pop(), guarda em uma variavel,
recoloca no topo, e retorna na chamada da funcao.
*/

float topo(Pilha* p) {
    if (pilha_vazia(p)) {
        printf("Pilha Vazia!\n");
        return 0.0;
    }

    float v = pilha_pop(p);  
    pilha_push(p, v);        
    return v;                
}
