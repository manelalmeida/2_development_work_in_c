#include <stdio.h>

int* retorna_ponteiro() {
    
    int variavel_local = 42;

    return &variavel_local; 
}

void outra_funcao_qualquer() {
    int lixo = 9999;
    printf("A fazer outras coisas na memoria...\n");
}

int main() {
    
    int *ponteiro_fantasma = retorna_ponteiro();
    
    printf("Endereço retornado: %p\n", (void*)ponteiro_fantasma);
    
    printf("Valor logo apos a funcao: %d\n", *ponteiro_fantasma);
    
    outra_funcao_qualquer();
    
    printf("Valor depois de outra funcao: %d\n", *ponteiro_fantasma);
    
    return 0;
}