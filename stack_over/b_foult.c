#include <stdio.h>


void causar_overflow_infinito(int n) {
    int x; 
    
    printf("Chamada %d - Endereço de x: %p\n", n, (void *)&x);
    
    causar_overflow_infinito(n + 1); 
}

int main() {
    printf("--- A iniciar o estouro por recursao infinita ---\n");
    causar_overflow_infinito(1);
}