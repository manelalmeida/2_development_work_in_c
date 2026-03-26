#include <stdio.h>

int dobrar(int x) { return x * 2; }
int triplicar(int x) { return x * 3; }
int quadrado(int x) { return x * x; }

int main() {

    int vetor[100];
    int n, escolha;

    int (*calculos[3])(int) = {dobrar, triplicar, quadrado};

    // Ler tamanho do vetor
    printf("Quantos elementos queres no vetor?\n");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        printf("Erro: tamanho inválido.\n");
        return 0;
    }

    // Ler elementos do vetor
    printf("Introduz os %d elementos:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &vetor[i]) != 1) {
            printf("Erro: valor inválido.\n");
            return 0;
        }
    }

    // Menu
    printf("Escolhe o calculo:\n");
    printf("0 - Dobrar\n1 - Triplicar\n2 - Quadrado\n");

    if (scanf("%d", &escolha) != 1 || escolha < 0 || escolha > 2) {
        printf("Erro: escolha inválida.\n");
        return 0;
    }

    // Aplicar transformação
    for (int i = 0; i < n; i++) {
        vetor[i] = calculos[escolha](vetor[i]);
    }

    // Mostrar resultado
    printf("Vetor transformado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
