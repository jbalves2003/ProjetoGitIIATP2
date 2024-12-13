//
// Created by 2003j on 13/12/2024.
//

#include "algoritmo_evolutivo.h"
#include "utils.h"
#include "funcao.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Inicializa a população com soluções aleatórias
void inicializa_populacao(int **pop, int tamanho_pop, int n_moedas, float *valores_moedas) {
    for (int i = 0; i < tamanho_pop; i++) {
        gera_sol_inicial(pop[i], n_moedas, valores_moedas);
    }
}

// Avalia todas as soluções na população
void avalia_populacao(int **pop, int *fitness, int tamanho_pop, float *valores_moedas, int n_moedas, float valor_objetivo) {
    for (int i = 0; i < tamanho_pop; i++) {
        fitness[i] = calcula_fit(pop[i], valores_moedas, n_moedas, valor_objetivo);
    }
}

// Torneio para selecionar um indivíduo
int torneio(int **pop, int *fitness, int tamanho_pop, int n_moedas) {
    int i1 = random_l_h(0, tamanho_pop - 1);
    int i2 = random_l_h(0, tamanho_pop - 1);
    return (fitness[i1] < fitness[i2]) ? i1 : i2;
}

// Operador de crossover de um ponto
void crossover(int *pai1, int *pai2, int *filho1, int *filho2, int n_moedas) {
    int ponto_corte = random_l_h(0, n_moedas - 1);
    for (int i = 0; i < n_moedas; i++) {
        if (i <= ponto_corte) {
            filho1[i] = pai1[i];
            filho2[i] = pai2[i];
        } else {
            filho1[i] = pai2[i];
            filho2[i] = pai1[i];
        }
    }
}

// Operador de mutação
void mutacao(int *individuo, int n_moedas) {
    int pos = random_l_h(0, n_moedas - 1);
    int alteracao = random_l_h(-3, 3); // Adiciona ou remove entre -3 e 3 moedas
    individuo[pos] = (individuo[pos] + alteracao > 0) ? individuo[pos] + alteracao : 0;
}

// Substituição elitista
void substitui_populacao(int **pop, int **nova_pop, int *fitness, int *nova_fitness, int tamanho_pop, int n_moedas) {
    int melhor_idx = 0;
    for (int i = 1; i < tamanho_pop; i++) {
        if (nova_fitness[i] < nova_fitness[melhor_idx]) {
            melhor_idx = i;
        }
    }

    for (int i = 0; i < tamanho_pop; i++) {
        if (i == 0) { // Garante a preservação do melhor
            substitui(pop[i], nova_pop[melhor_idx], n_moedas);
            fitness[i] = nova_fitness[melhor_idx];
        } else {
            substitui(pop[i], nova_pop[i], n_moedas);
            fitness[i] = nova_fitness[i];
        }
    }
}

// Algoritmo evolutivo principal
int algoritmo_evolutivo(int *melhor_sol, float *valores_moedas, int n_moedas, float valor_objetivo, int tamanho_pop, int geracoes) {
    int **pop = malloc(sizeof(int *) * tamanho_pop);
    int **nova_pop = malloc(sizeof(int *) * tamanho_pop);
    int *fitness = malloc(sizeof(int) * tamanho_pop);
    int *nova_fitness = malloc(sizeof(int) * tamanho_pop);

    for (int i = 0; i < tamanho_pop; i++) {
        pop[i] = malloc(sizeof(int) * n_moedas);
        nova_pop[i] = malloc(sizeof(int) * n_moedas);
    }

    inicializa_populacao(pop, tamanho_pop, n_moedas, valores_moedas);
    avalia_populacao(pop, fitness, tamanho_pop, valores_moedas, n_moedas, valor_objetivo);

    for (int g = 0; g < geracoes; g++) {
        for (int i = 0; i < tamanho_pop; i += 2) {
            int p1 = torneio(pop, fitness, tamanho_pop, n_moedas);
            int p2 = torneio(pop, fitness, tamanho_pop, n_moedas);

            crossover(pop[p1], pop[p2], nova_pop[i], nova_pop[i + 1], n_moedas);
            mutacao(nova_pop[i], n_moedas);
            mutacao(nova_pop[i + 1], n_moedas);
        }

        avalia_populacao(nova_pop, nova_fitness, tamanho_pop, valores_moedas, n_moedas, valor_objetivo);
        substitui_populacao(pop, nova_pop, fitness, nova_fitness, tamanho_pop, n_moedas);
    }

    int melhor_idx = 0;
    for (int i = 1; i < tamanho_pop; i++) {
        if (fitness[i] < fitness[melhor_idx]) {
            melhor_idx = i;
        }
    }
    substitui(melhor_sol, pop[melhor_idx], n_moedas);

    for (int i = 0; i < tamanho_pop; i++) {
        free(pop[i]);
        free(nova_pop[i]);
    }
    free(pop);
    free(nova_pop);
    free(fitness);
    free(nova_fitness);

    return fitness[melhor_idx];
}
