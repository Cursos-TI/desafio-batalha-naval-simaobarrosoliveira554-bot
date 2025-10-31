#include <stdio.h>

#define TAM 10       // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3  // Tamanho dos navios (3 posições)
#define AGUA 0       // Representa o mar
#define NAVIO 3      // Representa as partes do navio

int main() {
    // -----------------------------------------------
    // 1. DECLARAÇÃO DO TABULEIRO E INICIALIZAÇÃO
    // -----------------------------------------------
    int tabuleiro[TAM][TAM];
    
    // Preenche o tabuleiro com água (valor 0)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // -----------------------------------------------
    // 2. DECLARAÇÃO DOS NAVIOS (VETORES)
    // -----------------------------------------------
    int navioHorizontal[TAM_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAM_NAVIO]   = {NAVIO, NAVIO, NAVIO};

    // Coordenadas iniciais dos navios
    // (definidas diretamente no código, conforme instrução)
    int linhaHorizontal = 4;  // Linha onde o navio horizontal começa
    int colunaHorizontal = 2; // Coluna inicial do navio horizontal

    int linhaVertical = 1;    // Linha inicial do navio vertical
    int colunaVertical = 7;   // Coluna fixa do navio vertical

    // -----------------------------------------------
    // 3. VALIDAÇÃO DE LIMITES DO TABULEIRO
    // (Simplificada — apenas garante que o navio cabe no tabuleiro)
    // -----------------------------------------------
    if (colunaHorizontal + TAM_NAVIO <= TAM && linhaVertical + TAM_NAVIO <= TAM) {

        // -----------------------------------------------
        // 4. POSICIONAMENTO DOS NAVIOS NO TABULEIRO
        // -----------------------------------------------

        // Navio horizontal
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaHorizontal][colunaHorizontal + i] = navioHorizontal[i];
        }

        // Navio vertical
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaVertical + i][colunaVertical] = navioVertical[i];
        }

    } else {
        printf("Erro: coordenadas inválidas. O navio ultrapassa os limites do tabuleiro.\n");
        return 1; // Encerra o programa com erro
    }

    // -----------------------------------------------
    // 5. EXIBIÇÃO DO TABULEIRO
    // -----------------------------------------------
    printf("===== TABULEIRO DE BATALHA NAVAL =====\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    // -----------------------------------------------
    // 6. FIM DO PROGRAMA
    // -----------------------------------------------
    printf("\nNavios posicionados com sucesso!\n");
    printf("-> Navio Horizontal: linha %d, colunas %d a %d\n", linhaHorizontal, colunaHorizontal, colunaHorizontal + TAM_NAVIO - 1);
    printf("-> Navio Vertical: coluna %d, linhas %d a %d\n", colunaVertical, linhaVertical, linhaVertical + TAM_NAVIO - 1);

    return 0;
}
