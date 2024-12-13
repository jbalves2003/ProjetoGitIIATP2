
//
// Created by 2003j on 09/12/2024.
//

#ifndef ALGORITMO_H
#define ALGORITMO_H

int trepa_colinas(int sol[], float *valores_moedas, int n_moedas, float valor_objetivo, int num_iter);
void gera_vizinho(int a[], int b[], int n, float valor_objetivo, float *valores_moedas);
int metodo_hibrido(int *melhor_sol, float *valores_moedas, int n_moedas, float valor_objetivo, int tamanho_pop, int geracoes, int num_iter);
int metodo_hibrido_2(int *melhor_sol, float *valores_moedas, int n_moedas, float valor_objetivo, int tamanho_pop, int geracoes, int num_iter);



#endif

