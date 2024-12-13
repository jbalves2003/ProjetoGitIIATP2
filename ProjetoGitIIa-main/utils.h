#ifndef UTILS_H
#define UTILS_H

// Atualize a declaração da função para incluir o parâmetro de título
void escreve_sol(int *sol, int n_moedas, float *valores_moedas, const char* titulo);

void gera_sol_inicial(int *sol, int n_moedas, float *valores_moedas);
float* ler_moedas(char *nome_ficheiro, int *n_moedas, float *valor_objetivo);
void substitui(int a[], int b[], int n);
void init_rand();
int random_l_h(int min, int max);

#endif
