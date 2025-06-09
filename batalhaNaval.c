#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Desafio Batalha Naval - MateCheck

#define TAMANHO_TABULEIRO 10
#define TAMANHO_PADRAO 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE_CONE 5
#define HABILIDADE_CRUZ 7
#define HABILIDADE_OCTAEDRO 9

//Função para limpar o tabuleiro
void limparTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

//Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int visivel[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (visivel[i][j] == 0) {
                printf(" 0 ");  // Água não atingida
            } else {
                if (tabuleiro[i][j] == NAVIO)
                    printf(" 3 ");  // Navio revelado
                else if (tabuleiro[i][j] == HABILIDADE_CONE)
                    printf(" 5 ");
                else if (tabuleiro[i][j] == HABILIDADE_CRUZ)
                    printf(" 7 ");
                else if (tabuleiro[i][j] == HABILIDADE_OCTAEDRO)
                    printf(" 9 ");
                else
                    printf(" 0 ");
            }
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

// Função para aplicar habilidade
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int visivel[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                        int centroX, int centroY, int padrao[TAMANHO_PADRAO][TAMANHO_PADRAO], int valorHabilidade) {
    int offset = TAMANHO_PADRAO / 2;

    for (int i = 0; i < TAMANHO_PADRAO; i++) {
        for (int j = 0; j < TAMANHO_PADRAO; j++) {
            int x = centroX + (j - offset);
            int y = centroY + (i - offset);

            if (x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO) {
                if (padrao[i][j] == 1) {
                    visivel[y][x] = 1;

                    if (tabuleiro[y][x] == AGUA) {
                        tabuleiro[y][x] = valorHabilidade; // Marca água com o tipo da habilidade
                    } 
                    // Se for navio, só revela, não altera o valor (mantém 3 como NAVIO)
                }
            }
        }
    }
}

//Função para posicionar navios
void posicionarNavios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int quantidade;
    printf("\nQuantos navios deseja posicionar? ");
    scanf("%d", &quantidade);

    for (int i = 0; i < quantidade; i++) {
        int x, y;
        do {
            printf("Posicione o navio %d (linha coluna): ", i + 1);
            scanf("%d %d", &y, &x);
            if (x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO) {
                if (tabuleiro[y][x] == AGUA) {
                    tabuleiro[y][x] = NAVIO;
                    break;
                } else {
                    printf("Ja existe algo nessa posicao.\n");
                }
            } else {
                printf("Posicao invalida.\n");
            }
        } while (1);
    }
}

//Menu para escolha de habilidades
void menuHabilidades(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int visivel[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int opcao;
    do {
        printf("\n--- Menu de Habilidades ---\n");
        printf("1. Cone\n");
        printf("2. Cruz\n");
        printf("3. Octaedro\n");
        printf("4. Sair\n");
        printf("Escolha uma habilidade: ");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 3) {
            int x, y;
            printf("Informe as coordenadas (linha coluna): ");
            scanf("%d %d", &y, &x);

            int padrao[TAMANHO_PADRAO][TAMANHO_PADRAO];
            const char *nome = (opcao == 1) ? "cone" : (opcao == 2) ? "cruz" : "octaedro";
            int valor = (opcao == 1) ? HABILIDADE_CONE : (opcao == 2) ? HABILIDADE_CRUZ : HABILIDADE_OCTAEDRO;

            criarPadrao(padrao, nome);
            aplicarHabilidade(tabuleiro, visivel, x, y, padrao, valor);

            imprimirTabuleiro(tabuleiro, visivel);
        }
    } while (opcao != 4);
}


// Programa principal
int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int visivel[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    limparTabuleiro(tabuleiro);

    printf("### Batalha Naval ###\n");

    imprimirTabuleiro(tabuleiro, visivel);

    posicionarNavios(tabuleiro);

    imprimirTabuleiro(tabuleiro, visivel);

    menuHabilidades(tabuleiro, visivel);

    printf("\nTabuleiro final:\n");
    imprimirTabuleiro(tabuleiro, visivel);

    return 0;
}