#include <stdio.h>

int soma(int a, int b) {
    printf("INICIO -> Valor de a: %d | Valor de b: %d\n", a, b);

    *(&b - 1) = 999; 

    printf("FIM    -> Valor de a: %d | Valor de b: %d\n", a, b);

    return a + b;
}

int main() {
    int var1 = 10;
    int var2 = 20;
    
    printf("--- Testar a funcao soma ---\n");
    int resultado = soma(var1, var2);
    
    printf("Resultado final da soma: %d\n", resultado);
    
    return 0;
}