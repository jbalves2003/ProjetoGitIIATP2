#include "algoritmo.h"
#include <stdlib.h>
#include "funcao.h"
#include "utils.h"
#include <stdio.h>
#include <tgmath.h>
#include "algoritmo_evolutivo.h"
int num_iter = 1000;


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


// Função híbrida: Trepa-Colinas + Algoritmo Evolutivo
int metodo_hibrido(int *melhor_sol, float *valores_moedas, int n_moedas, float valor_objetivo, int tamanho_pop, int geracoes, int num_iter) {
    // Passo 1: Inicializar a solução com Trepa-Colinas
    printf("Iniciando Trepa-Colinas...\n");
    int custo_final = trepa_colinas(melhor_sol, valores_moedas, n_moedas, valor_objetivo, num_iter);

    // Passo 2: Melhorar com Algoritmo Evolutivo
    printf("Iniciando Algoritmo Evolutivo...\n");
    custo_final = algoritmo_evolutivo(melhor_sol, valores_moedas, n_moedas, valor_objetivo, tamanho_pop, geracoes);

    return custo_final;
}

// Função híbrida: Algoritmo Evolutivo + Trepa-Colinas
int metodo_hibrido_2(int *melhor_sol, float *valores_moedas, int n_moedas, float valor_objetivo, int tamanho_pop, int geracoes, int num_iter) {
    // Passo 1: Inicializar com Algoritmo Evolutivo
    printf("Iniciando Algoritmo Evolutivo...\n");
    int custo_inicial = algoritmo_evolutivo(melhor_sol, valores_moedas, n_moedas, valor_objetivo, tamanho_pop, geracoes);

    // Passo 2: Melhorar com Trepa-Colinas
    printf("Iniciando Trepa-Colinas...\n");
    int custo_final = trepa_colinas(melhor_sol, valores_moedas, n_moedas, valor_objetivo, num_iter);

    return custo_final;
}


//Comparar Hibridos
void compara_abordagens_hibridas(int *melhor_sol_1, int *melhor_sol_2, float *valores_moedas, int n_moedas, float valor_objetivo, int tamanho_pop, int geracoes) {
    // Abordagem híbrida 1: Trepa-Colinas + Algoritmo Evolutivo
    int custo_hibrido_1 = metodo_hibrido(melhor_sol_1, valores_moedas, n_moedas, valor_objetivo, tamanho_pop, geracoes, num_iter);

    // Abordagem híbrida 2: Algoritmo Evolutivo + Trepa-Colinas
    int custo_hibrido_2 = metodo_hibrido_2(melhor_sol_2, valores_moedas, n_moedas, valor_objetivo, tamanho_pop, geracoes, num_iter);

    printf("Custo final - Hibrido 1 (Trepa-Colinas + Algoritmo Evolutivo): %d\n", custo_hibrido_1);
    printf("Custo final - Hibrido 2 (Algoritmo Evolutivo + Trepa-Colinas): %d\n", custo_hibrido_2);

    if (custo_hibrido_1 < custo_hibrido_2) {
        printf("Hibrido 1 (Trepa-Colinas + Algoritmo Evolutivo) e o melhor metodo!\n");
    } else {
        printf("Hibrido 2 (Algoritmo Evolutivo + Trepa-Colinas) e o melhor metodo!\n");
    }
}
