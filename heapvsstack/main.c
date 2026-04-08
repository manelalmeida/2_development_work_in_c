#include <stdio.h>
#include <stdlib.h>

int* aloca_memoria(){

    int *p_func = (int *)malloc(sizeof(int));

    if(p_func != NULL){
        *p_func = 42;
    }

    return p_func;
}

int main(){

    int a = 10;
    
    int *p_main = (int *)malloc(sizeof(int));
    if(p_main != NULL){
        *p_main = 20;
    }

    int *p_da_func = aloca_memoria();

    printf("--- Memoria Stack (Pilha) ---\n");
    printf("Endereço da variavel local:      %p\n\n", (void*)&a);
    
    printf("--- Memoria Heap (Monte) ---\n");
    printf("Endereço do inteiro alocado no main: %p\n", (void*)p_main);
    printf("Endereço do inteiro alocado na func: %p\n", (void*)p_da_func);

    free(p_main);
    free(p_da_func);

    return 0;
}