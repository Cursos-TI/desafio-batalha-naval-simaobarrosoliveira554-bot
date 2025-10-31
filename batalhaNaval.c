#include <stdio.h>

#define TAM 10      // Tamanho fixo do tabuleiro
#define NAVIO 3     // Valor que representa as partes dos navios
#define AGUA 0      // Valor que representa a água
#define TAMANHO_NAVIO 3  // Tamanho fixo de cada navio

// Função para inicializar o tabuleiro com zeros
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para posicionar um navio horizontalmente
void posicionarHorizontal(int tabuleiro[TAM][TAM], int linha, int colunaInicial) {
    for (int j = 0; j < TAMANHO_NAVIO; j++) {
        tabuleiro[linha][colunaInicial + j] = NAVIO;
    }
}

// Função para posicionar um navio verticalmente
void posicionarVertical(int tabuleiro[TAM][TAM], int linhaInicial, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaInicial + i][coluna] = NAVIO;
    }
}

// Função para posicionar um navio na diagonal principal (↘)
void posicionarDiagonalPrincipal(int tabuleiro[TAM][TAM], int linhaInicial, int colunaInicial) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaInicial + i][colunaInicial + i] = NAVIO;
    }
}

// Função para posicionar um navio na diagonal secundária (↙)
void posicionarDiagonalSecundaria(int tabuleiro[TAM][TAM], int linhaInicial, int colunaInicial) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linhaInicial + i][colunaInicial - i] = NAVIO;
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    
    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // === POSICIONAMENTO DOS 4 NAVIOS ===
    // Dois navios retos (horizontal e vertical)
    posicionarHorizontal(tabuleiro, 1, 1);   // Linha 1, colunas 1–3
    posicionarVertical(tabuleiro, 4, 6);     // Coluna 6, linhas 4–6

    // Dois navios diagonais
    posicionarDiagonalPrincipal(tabuleiro, 6, 1);  // Diagonal ↘ (começa em 6,1)
    posicionarDiagonalSecundaria(tabuleiro, 0, 9); // Diagonal ↙ (começa em 0,9)

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
