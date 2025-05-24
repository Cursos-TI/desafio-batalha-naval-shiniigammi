#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Desafio Batalha Naval - MateCheck

#define TAMANHO_TABULEIRO 10
#define TAMANHO_PADRAO 5

//Função para limpar o tabuleiro
void limparTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

//Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

//Função para criar padrão de habilidade
void criarPadrao(int matriz[TAMANHO_PADRAO][TAMANHO_PADRAO], const char *tipo) {
    int centro = TAMANHO_PADRAO / 2;

    //Zerar matriz
    for (int i = 0; i < TAMANHO_PADRAO; i++) {
        for (int j = 0; j < TAMANHO_PADRAO; j++) {
            matriz[i][j] = 0;
        }
    }

    if (strcmp(tipo, "cone") == 0) {
        for (int i = 0; i <= centro; i++) {
            for (int j = centro - i; j <= centro + i; j++) {
                matriz[i + centro][j] = 1;
            }
        }
    } else if (strcmp(tipo, "cruz") == 0) {
        for (int i = 0; i < TAMANHO_PADRAO; i++) {
            matriz[centro][i] = 1;
            matriz[i][centro] = 1;
        }
    } else if (strcmp(tipo, "octaedro") == 0) {
        for (int i = 0; i < TAMANHO_PADRAO; i++) {
            for (int j = 0; j < TAMANHO_PADRAO; j++) {
                if (abs(i - centro) + abs(j - centro) <= 2) {
                    matriz[i][j] = 1;
                }
            }
        }
    }
}

//Verifica se é possível aplicar habilidade sem sobreposição
int podeAplicar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int centroX, int centroY, int padrao[TAMANHO_PADRAO][TAMANHO_PADRAO]) {
    int offset = TAMANHO_PADRAO / 2;

    for (int i = 0; i < TAMANHO_PADRAO; i++) {
        for (int j = 0; j < TAMANHO_PADRAO; j++) {
            int x = centroX + (j - offset);
            int y = centroY + (i - offset);

            if (x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO) {
                if (padrao[i][j] == 1 && tabuleiro[y][x] == 1) {
                    return 0; // Não pode aplicar, há sobreposição
                }
            }
        }
    }
    return 1; //Pode aplicar, não há sobreposição
}

// Função para aplicar habilidade se não houver sobreposição
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int centroX, int centroY, int padrao[TAMANHO_PADRAO][TAMANHO_PADRAO]) {
    if (podeAplicar(tabuleiro, centroX, centroY, padrao)) {
        int offset = TAMANHO_PADRAO / 2;

        for (int i = 0; i < TAMANHO_PADRAO; i++) {
            for (int j = 0; j < TAMANHO_PADRAO; j++) {
                int x = centroX + (j - offset);
                int y = centroY + (i - offset);

                if (x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO) {
                    if (padrao[i][j] == 1) {
                        tabuleiro[y][x] = 1;
                    }
                }
            }
        }
        printf("Habilidade aplicada com sucesso em (%d, %d)\n", centroX, centroY);
    } else {
        printf("Nao foi possivel aplicar habilidade em (%d, %d) devido a sobreposicao.\n", centroX, centroY);
    }
}

// Programa principal
int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int padrao[TAMANHO_PADRAO][TAMANHO_PADRAO];

    limparTabuleiro(tabuleiro);

    //Aplicando múltiplas habilidades sem sobreposição

    // Exemplos de exibição das habilidades:
    
    // Exemplo para habilidade em cone:
    criarPadrao(padrao, "cone");
    aplicarHabilidade(tabuleiro, 3, 6, padrao);


    // Exemplo para habilidade em octaedro:
    criarPadrao(padrao, "octaedro");
    aplicarHabilidade(tabuleiro, 3, 2, padrao);

    // Exemplo para habilidade em cruz:
    criarPadrao(padrao, "cruz");
    aplicarHabilidade(tabuleiro, 7, 5, padrao);

    //Exibir o resultado final
    imprimirTabuleiro(tabuleiro);

    return 0;
}