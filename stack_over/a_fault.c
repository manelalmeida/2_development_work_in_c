#include <stdio.h>

void causar_overflow_pesado(int n) {

    int t[10000]; 
    
    printf("Chamada %d - Endereço de t: %p\n", n, (void *)&t);
    
    causar_overflow_pesado(n + 1); 
}

int main() {
    printf("--- A iniciar o estouro por variaveis gigantes ---\n");
    causar_overflow_pesado(1);
    return 0; 
}
