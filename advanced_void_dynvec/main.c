#include <stdio.h>
#include "dynvec.h"

// Funções Auxiliares para os Testes
int comparar_ints(const void *a, const void *b) { return (*(int*)a - *(int*)b); }
bool e_par(void *elem) { return (*(int*)elem % 2 == 0); }
void somar(void *acc, void *elem) { *(int*)acc += *(int*)elem; }

int main() {
    dynvec *v = dynvec_create(sizeof(int));
    int dados[] = {1, 2, 3, 4, 5, 6};
    for(int i=0; i<6; i++) dynvec_push(v, &dados[i]);

    printf("Comprimento: %zu\n", dynvec_length(v));

    // Teste Contains
    int busca = 4;
    printf("Contem 4? %s\n", dynvec_contains(v, &busca, comparar_ints) ? "Sim" : "Nao");

    // Teste Filter (Criar novo vetor apenas com pares)
    printf("Filtrando pares...\n");
    dynvec *pares = dynvec_filter(v, e_par);
    for(size_t i=0; i < dynvec_length(pares); i++) {
        printf("%d ", *(int*)dynvec_get(pares, i));
    }
    printf("\n");

    // Teste Fold (Somar tudo)
    int total = 0;
    dynvec_fold_left(v, &total, somar);
    printf("Soma total: %d\n", total);

    // Teste For all (Todos sao pares?)
    printf("Todos sao pares? %s\n", dynvec_forall(v, e_par) ? "Sim" : "Nao");

    dynvec_free(v);
    dynvec_free(pares);
    return 0;
}
