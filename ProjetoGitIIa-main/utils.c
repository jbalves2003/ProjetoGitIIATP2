#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include "utils.h"

float* ler_moedas(char *nome_ficheiro, int *n_moedas, float *valor_objetivo) {
    FILE *f = fopen(nome_ficheiro, "r");
    if (!f) {
        printf("Erro ao abrir o ficheiro\n");
        exit(1);
    }

    fscanf(f, "%d %f", n_moedas, valor_objetivo);
    float *valores_moedas = malloc(sizeof(float) * (*n_moedas));

    for (int i = 0; i < *n_moedas; i++) {
        fscanf(f, "%f", &valores_moedas[i]);
    }

    fclose(f);
    return valores_moedas;
}

void gera_sol_inicial(int *sol, int n_moedas, float *valores_moedas) {
    int total_moedas = 0;
    do {
        total_moedas = 0;
        for (int i = 0; i < n_moedas; i++) {
            sol[i] = random_l_h(0, 10); // Gera entre 0 e 10 moedas de cada tipo
            total_moedas += sol[i];
        }
    } while (total_moedas == 0); // Garante que pelo menos uma moeda seja usada
}

void escreve_sol(int *sol, int n_moedas, float *valores_moedas, const char* titulo) {
    int primeiro = 1; // Para controlar o "+" entre os termos
    printf("%s", titulo);  // Exibe o título passado como parâmetro
    for (int i = 0; i < n_moedas; i++) {
        if (sol[i] > 0) { // Exibe apenas moedas usadas
            if (!primeiro) {
                printf(" + ");
            }
            printf("%d*%.2f", sol[i], valores_moedas[i]);
            primeiro = 0;
        }
    }
    if (primeiro) {
        printf("Nenhuma moeda usada"); // Caso a solução seja completamente vazia
    }
    printf("\n");
}

void substitui(int a[], int b[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}

void init_rand() {
    srand((unsigned)time(NULL) ^ (unsigned)_getpid());
}

int random_l_h(int min, int max) {
    return min + rand() % (max - min + 1);
}
