#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "algoritmo_evolutivo.h"
#include "utils.h"

#define ITERACOES 1000
#define DEFAULT_RUNS 10

int main(int argc, char *argv[]) {
    char nome_fich[100];
    int n_moedas, num_iter, k, runs, custo, best_custo, opcao;
    float *valores_moedas, valor_objetivo;
    int *sol, *best;
    float mbf = 0.0;

    if (argc == 3) {
        runs = atoi(argv[2]);
        strcpy(nome_fich, argv[1]);
    } else if (argc == 2) {
        runs = DEFAULT_RUNS;
        strcpy(nome_fich, argv[1]);
    } else {
        runs = DEFAULT_RUNS;
        printf("Nome do Ficheiro: ");
        fgets(nome_fich, sizeof(nome_fich), stdin);
        nome_fich[strcspn(nome_fich, "\n")] = '\0';
    }
    if (runs <= 0)
        return 0;

    init_rand();
    // Lê dados do problema
    valores_moedas = ler_moedas(nome_fich, &n_moedas, &valor_objetivo);
    printf("Numero de moedas: %d\nValor objetivo: %.2f\n", n_moedas, valor_objetivo);

    num_iter = ITERACOES; // Número de iterações ajustado para exploração completa
    sol = malloc(sizeof(int) * n_moedas);
    best = malloc(sizeof(int) * n_moedas);
    if (sol == NULL || best == NULL) {
        printf("Erro na alocação de memória\n");
        exit(1);
    }

    do {
        // Apresentar o menu
        printf("\nMENU:\n");
        printf("1 - Trepa Colinas\n");
        printf("2 - Algoritmo Evolutivo\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mbf = 0.0;
                for (k = 0; k < runs; k++) {
                    gera_sol_inicial(sol, n_moedas, valores_moedas);
                    printf("\nRepeticao %d:\n", k + 1);
                    escreve_sol(sol, n_moedas, valores_moedas, "Solucao Inicial: ");

                    custo = trepa_colinas(sol, valores_moedas, n_moedas, valor_objetivo, num_iter);
                    escreve_sol(sol, n_moedas, valores_moedas, "Solucao Final: ");
                    printf("Custo final: %d\n", custo);

                    mbf += custo;
                    if (k == 0 || best_custo > custo) {
                        best_custo = custo;
                        substitui(best, sol, n_moedas);
                    }
                }

                printf("\n\nMBF: %f\n", mbf / runs);
                escreve_sol(best, n_moedas, valores_moedas, "Melhor solucao encontrada: ");
                printf("Custo final: %2d\n", best_custo);
                break;

            case 2: {
                // Configurações do algoritmo evolutivo
                int tamanho_pop = 20; // Definir tamanho da população
                int geracoes = 1000;  // Definir número de gerações

                custo = algoritmo_evolutivo(best, valores_moedas, n_moedas, valor_objetivo, tamanho_pop, geracoes);
                escreve_sol(best, n_moedas, valores_moedas, "Melhor solucao Evolutiva:");
                printf("Custo final Evolutivo: %d\n", custo);
                break;
            }

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    free(valores_moedas);
    free(sol);
    free(best);
    return 0;
}
