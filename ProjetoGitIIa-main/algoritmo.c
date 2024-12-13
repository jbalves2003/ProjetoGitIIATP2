#include "algoritmo.h"
#include <stdlib.h>
#include "funcao.h"
#include "utils.h"
#include <stdio.h>
#include <tgmath.h>

// Gera um vizinho
void gera_vizinho(int a[], int b[], int n, float valor_objetivo, float *valores_moedas) {
    // Copiar a solução atual para a nova solução
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }

    // Avaliar o quão distante a solução atual está do valor objetivo
    float soma_atual = 0.0;
    for (int i = 0; i < n; i++) {
        soma_atual += a[i] * valores_moedas[i];  // Supondo que você tenha o vetor 'valores_moedas'
    }
    float diff = fabs(soma_atual - valor_objetivo);

    // Definir o número de mudanças dependendo da diferença
    int num_mudancas = (diff > 1.0) ? random_l_h(1, 3) : 1; // Mais mudanças se a diferença for grande

    for (int i = 0; i < num_mudancas; i++) {
        int operacao = random_l_h(0, 2); // 0: remover moeda, 1: adicionar moeda, 2: trocar moedas entre tipos diferentes

        if (operacao == 0) {
            // Remover moeda
            int pos = random_l_h(0, n - 1);
            if (b[pos] > 0) b[pos]--;
        } else if (operacao == 1) {
            // Adicionar moeda
            int pos = random_l_h(0, n - 1);
            b[pos]++;
        } else if (operacao == 2) {
            // Trocar moedas entre tipos
            int pos1 = random_l_h(0, n - 1);
            int pos2 = random_l_h(0, n - 1);
            while (pos1 == pos2) pos2 = random_l_h(0, n - 1);
            int temp = b[pos1];
            b[pos1] = b[pos2];
            b[pos2] = temp;
        }
    }
}


// Trepa-colinas
int trepa_colinas(int sol[], float *valores_moedas, int n_moedas, float valor_objetivo, int num_iter) {
    int *nova_sol = malloc(sizeof(int) * n_moedas);
    if (nova_sol == NULL) {
        printf("Erro na alocação de memória\n");
        exit(1);
    }

    int custo = calcula_fit(sol, valores_moedas, n_moedas, valor_objetivo);
    for (int i = 0; i < num_iter; i++) {
        gera_vizinho(sol, nova_sol, n_moedas, valor_objetivo, valores_moedas);
        int custo_viz = calcula_fit(nova_sol, valores_moedas, n_moedas, valor_objetivo);

        if (custo_viz < custo) {
            substitui(sol, nova_sol, n_moedas);
            custo = custo_viz;
        }
    }
    free(nova_sol);
    return custo;
}
