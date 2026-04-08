#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 1, b = 2, c = 3;

    int *p1 = (int *)malloc(sizeof(int));
    int *p2 = (int *)malloc(sizeof(int));
    int *p3 = (int *)malloc(sizeof(int));

    printf("--- ENDEREÇOS NA STACK (Variáveis Locais) ---\n");
    printf("Endereço de a: %p\n", (void*)&a);
    printf("Endereço de b: %p\n", (void*)&b);
    printf("Endereço de c: %p\n", (void*)&c);

    printf("\n--- ENDEREÇOS NA HEAP (malloc) ---\n");
    if (p1 && p2 && p3) {
        printf("Endereço de p1: %p\n", (void*)p1);
        printf("Endereço de p2: %p\n", (void*)p2);
        printf("Endereço de p3: %p\n", (void*)p3);
    }

    free(p1); free(p2); free(p3);

    return 0;
}