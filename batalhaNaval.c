#include <stdio.h>

#define TAM 10             // Tamanho do tabuleiro 10x10
#define TAM_HAB 5          // Tamanho das matrizes de habilidade (5x5)
#define AGUA 0             // Representa água
#define NAVIO 3            // Representa navio
#define AREA 5             // Representa área afetada pela habilidade
#define NAVIO_AREA 8       // Representa posição com navio + área simultânea
#define TAMANHO_NAVIO 3    // Tamanho fixo dos navios (3)

// --------- Funções utilitárias ---------

// Inicializa tabuleiro com 0 (água)
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = AGUA;
}

// Exibe tabuleiro (0 = água, 3 = navio, 5 = area, 8 = navio+area)
void exibirTabuleiro(int tab[TAM][TAM]) {
    printf("\n=== TABULEIRO (0=agua,3=navio,5=area,8=navio+area) ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Posiciona navio horizontal (assume validação externa)
void posicionarHorizontal(int tab[TAM][TAM], int linha, int colunaInicial) {
    for (int j = 0; j < TAMANHO_NAVIO; j++)
        tab[linha][colunaInicial + j] = NAVIO;
}

// Posiciona navio vertical (assume validação externa)
void posicionarVertical(int tab[TAM][TAM], int linhaInicial, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tab[linhaInicial + i][coluna] = NAVIO;
}

// Posiciona navio diagonal principal (↘)
void posicionarDiagonalPrincipal(int tab[TAM][TAM], int linhaInicial, int colunaInicial) {
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tab[linhaInicial + i][colunaInicial + i] = NAVIO;
}

// Posiciona navio diagonal secundária (↙)
void posicionarDiagonalSecundaria(int tab[TAM][TAM], int linhaInicial, int colunaInicial) {
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tab[linhaInicial + i][colunaInicial - i] = NAVIO;
}

// --------- Geração dinâmica das matrizes de habilidade (5x5) ---------

// Cone apontando para baixo: topo no centro da primeira linha, expande-se para baixo
// Ex.: para size=5 e center=2, linha r tem uns entre center - r e center + r (limitado)
void gerarCone(int cone[TAM_HAB][TAM_HAB]) {
    int center = TAM_HAB / 2; // 2 para TAM_HAB=5
    for (int r = 0; r < TAM_HAB; r++) {
        for (int c = 0; c < TAM_HAB; c++) {
            // Condicional que cria a forma de cone (expande conforme r aumenta)
            if (c >= center - r && c <= center + r)
                cone[r][c] = 1;
            else
                cone[r][c] = 0;
        }
    }
}

// Cruz com ponto de origem no centro: linha central e coluna central preenchidas
void gerarCruz(int cruz[TAM_HAB][TAM_HAB]) {
    int center = TAM_HAB / 2;
    for (int r = 0; r < TAM_HAB; r++) {
        for (int c = 0; c < TAM_HAB; c++) {
            if (r == center || c == center)
                cruz[r][c] = 1;
            else
                cruz[r][c] = 0;
        }
    }
}

// Octaedro (vista frontal) ~ Losango (diamante) com ponto de origem no centro
// Critério: |r-center| + |c-center| <= radius
void gerarOctaedro(int oct[TAM_HAB][TAM_HAB]) {
    int center = TAM_HAB / 2;
    int radius = center; // para 5x5, radius=2
    for (int r = 0; r < TAM_HAB; r++) {
        for (int c = 0; c < TAM_HAB; c++) {
            if ( (abs(r - center) + abs(c - center)) <= radius )
                oct[r][c] = 1;
            else
                oct[r][c] = 0;
        }
    }
}

// --------- Sobreposição da matriz de habilidade no tabuleiro ---------
// Centro (origem) definido por origemLinha, origemColuna (no tabuleiro).
// A matriz de habilidade skill[size][size] será centrada nesse ponto.
// Caso a posição esteja fora dos limites do tabuleiro, é ignorada.
// Se atingir um navio (3), marcamos com NAVIO_AREA (8) para indicar sobreposição.
void aplicarHabilidade(int tab[TAM][TAM], int skill[TAM_HAB][TAM_HAB],
                       int origemLinha, int origemColuna) {
    int center = TAM_HAB / 2; // índice central da matriz de habilidade
    for (int r = 0; r < TAM_HAB; r++) {
        for (int c = 0; c < TAM_HAB; c++) {
            if (skill[r][c] != 1) continue; // não afeta posições com 0

            int targetLinha = origemLinha - center + r;
            int targetCol   = origemColuna - center + c;

            // valida limites do tabuleiro
            if (targetLinha < 0 || targetLinha >= TAM || targetCol < 0 || targetCol >= TAM)
                continue;

            // se já havia navio, marca navio+area; senão marca área.
            if (tab[targetLinha][targetCol] == NAVIO)
                tab[targetLinha][targetCol] = NAVIO_AREA;
            else
                tab[targetLinha][targetCol] = AREA;
        }
    }
}

// --------- Programa principal ---------
int main() {
    int tabuleiro[TAM][TAM];

    // Inicializa tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Posiciona 4 navios (tamanho fixo 3) -- coordenadas definidas diretamente
    posicionarHorizontal(tabuleiro, 1, 1);    // horizontal: linha 1, col 1-3
    posicionarVertical(tabuleiro, 4, 6);      // vertical: coluna 6, linhas 4-6
    posicionarDiagonalPrincipal(tabuleiro, 6, 1); // diagonal ↘ começando em 6,1
    posicionarDiagonalSecundaria(tabuleiro, 0, 9); // diagonal ↙ começando em 0,9

    // Matrizes de habilidade (5x5)
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    // Gera dinamicamente as matrizes (uso obrigatório de loops aninhados e condicionais)
    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // Pontos de origem no tabuleiro (definidos diretamente)
    // (linha, coluna) -> cuidado com índices 0..9
    int origemConeLinha = 2, origemConeColuna = 3;     // exemplo: topo-centro do cone em (2,3)
    int origemCruzLinha = 5, origemCruzColuna = 4;     // cruz centrada em (5,4)
    int origemOctLinha  = 7, origemOctColuna  = 7;     // octaedro centrado em (7,7)

    // Aplica as habilidades sobre o tabuleiro (com validação de limites)
    aplicarHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicarHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicarHabilidade(tabuleiro, octaedro, origemOctLinha, origemOctColuna);

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    // (Opcional) Exibe as matrizes de habilidade geradas, para inspeção
    printf("Matriz CONE (1 = afetado):\n");
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) printf("%d ", cone[i][j]);
        printf("\n");
    }
    printf("\nMatriz CRUZ (1 = afetado):\n");
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) printf("%d ", cruz[i][j]);
        printf("\n");
    }
    printf("\nMatriz OCTAEDRO (1 = afetado):\n");
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) printf("%d ", octaedro[i][j]);
        printf("\n");
    }

    printf("\nHabilidades aplicadas nas origens:\n");
    printf("Cone  -> (%d,%d)\n", origemConeLinha, origemConeColuna);
    printf("Cruz  -> (%d,%d)\n", origemCruzLinha, origemCruzColuna);
    printf("Octaedro -> (%d,%d)\n", origemOctLinha, origemOctColuna);

    return 0;
}
