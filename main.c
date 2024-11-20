#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAMANHO 3
#define TAMANHO_FRASE 100

void escolha(char valor[], char arquivo[]);
int** lerArquivo(char arquivo[], int* linhas, int* colunas);
int inserirDados();
void exibirAjuda();
bool todosIguais(int** matriz, int inicioLinha, int inicioColuna, int finalLinha, int finalColuna);
void dividir(int** matriz, int inicioLinha, int inicioColuna, int finalLinha, int finalColuna, char frase[]);
void colocaLetra(int** matriz, int inicioLinha, int inicioColuna, char frase[]);

int main(int argc, char **argv) {
    if (argc < 2) {
        exibirAjuda();
        return 1;
    }

    char argumento[25];
    char nomeArquivo[25];

    strcpy(argumento, argv[1]);
    if (argc > 2) {
        strcpy(nomeArquivo, argv[2]);
    }

    escolha(argumento, nomeArquivo);
    return 0;
}

void dividir(int** matriz, int inicioLinha, int inicioColuna, int finalLinha, int finalColuna, char frase[]) {
    if (todosIguais(matriz, inicioLinha, inicioColuna, finalLinha, finalColuna)) {
        colocaLetra(matriz, inicioLinha, inicioColuna, frase);
        return;
    }

    char letra[2] = "X\0";
    strcat(frase, letra);

    int divisaoInicioLinha;
    int divisaoInicioColuna;
    int divisaoFinalLinha;
    int divisaoFinalColuna;

    // Quadrante 1
    divisaoInicioLinha = inicioLinha;
    divisaoFinalLinha = (finalLinha % 2 == 0) ? finalLinha / 2 : finalLinha / 2 + 1;
    divisaoInicioColuna = inicioColuna;
    divisaoFinalColuna = (finalColuna % 2 == 0) ? finalColuna / 2 : finalColuna / 2 + 1;
    dividir(matriz, divisaoInicioLinha, divisaoInicioColuna, divisaoFinalLinha, divisaoFinalColuna, frase);

    // Quadrante 2
    divisaoInicioLinha = inicioLinha;
    divisaoFinalLinha = (finalLinha % 2 == 0) ? finalLinha / 2 : finalLinha / 2 + 1;
    divisaoInicioColuna = (finalColuna % 2 == 0) ? finalColuna / 2 : finalColuna / 2 + 1;
    divisaoFinalColuna = finalColuna;
    dividir(matriz, divisaoInicioLinha, divisaoInicioColuna, divisaoFinalLinha, divisaoFinalColuna, frase);

    // Quadrante 3
    divisaoInicioLinha = (finalLinha % 2 == 0) ? finalLinha / 2 : finalLinha / 2 + 1;
    divisaoFinalLinha = finalLinha;
    divisaoInicioColuna = inicioColuna;
    divisaoFinalColuna = (finalColuna % 2 == 0) ? finalColuna / 2 : finalColuna / 2 + 1;
    dividir(matriz, divisaoInicioLinha, divisaoInicioColuna, divisaoFinalLinha, divisaoFinalColuna, frase);

    // Quadrante 4
    divisaoInicioLinha = (finalLinha % 2 == 0) ? finalLinha / 2 : finalLinha / 2 + 1;
    divisaoFinalLinha = finalLinha;
    divisaoInicioColuna = (finalColuna % 2 == 0) ? finalColuna / 2 : finalColuna / 2 + 1;
    divisaoFinalColuna = finalColuna;
    dividir(matriz, divisaoInicioLinha, divisaoInicioColuna, divisaoFinalLinha, divisaoFinalColuna, frase);
}

bool todosIguais(int** matriz, int inicioLinha, int inicioColuna, int finalLinha, int finalColuna) {
    int cor = matriz[inicioLinha][inicioColuna];

    for (int i = inicioLinha; i < finalLinha; i++) {
        for (int j = inicioColuna; j < finalColuna; j++) {
            if (cor != matriz[i][j]) return false;
        }
    }
    return true;
}

void colocaLetra(int** matriz, int inicioLinha, int inicioColuna, char frase[]) {
    char letra[2];
    if (matriz[inicioLinha][inicioColuna] == 0) {
        letra[0] = 'B';
    } else if (matriz[inicioLinha][inicioColuna] == 1) {
        letra[0] = 'P';
    }

    letra[1] = '\0';
    strcat(frase, letra);
}

int** lerArquivo(char arquivo[], int* linhas, int* colunas) {
    FILE* arquivosaida = fopen(arquivo, "r");
    if (arquivosaida == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char linha[100];
    fgets(linha, sizeof(linha), arquivosaida);
    do {
        if (fgets(linha, sizeof(linha), arquivosaida) == NULL) {
            fclose(arquivosaida);
            return NULL;
        }
    } while (linha[0] == '#');

    sscanf(linha, "%d %d", colunas, linhas);

    int** matriz [*linhas] [*colunas];

    for (int i = 0; i < *linhas; i++) {
        for (int j = 0; j < *colunas; j++) {
            fscanf(arquivosaida, "%d", &matriz[i][j]);
        }
    }
    fclose(arquivosaida);

    printf("Matriz lida do arquivo (%dx%d):\n", *linhas, *colunas);
    for (int i = 0; i < *linhas; i++) {
        for (int j = 0; j < *colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    return matriz;
}

int inserirDados() {
    int linhas, colunas;

    printf("Digite a altura: ");
    scanf("%d", &linhas);
    printf("Digite a largura: ");
    scanf("%d", &colunas);

    int** matriz [linhas] [colunas];

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("linha %d, coluna %d: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    printf("Matriz inserida (%dx%d):\n", linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    char frase[TAMANHO_FRASE] = "";
    dividir(matriz, 0, 0, linhas, colunas, frase);
    return 0;
}

void exibirAjuda() {
    printf("Uso: ImageEncoder [-? | -m | -f ARQ]\n");
    printf("Codifica imagens binarias dadas em arquivos PBM ou dados informados manualmente.\n");
    printf("Argumentos:\n");
    printf("  -?, --help    : Apresenta esta orientacao na tela.\n");
    printf("  -m, --manual  : Ativa o modo de entrada manual, em que o usuario fornece os dados da imagem via teclado.\n");
    printf("  -f, --file ARQ: Le a imagem representada no arquivo PBM (Portable Bitmap).\n");
}

void escolha(char valor[], char arquivo[]) {
    if (strcmp(valor, "-?") == 0 || strcmp(valor, "--help") == 0) {
        exibirAjuda();
    } else if (strcmp(valor, "-m") == 0 || strcmp(valor, "--manual") == 0) {
        inserirDados();
    } else if (strcmp(valor, "-f") == 0 || strcmp(valor, "--file") == 0) {
        int linhas, colunas;
        int** matriz = lerArquivo(arquivo, &linhas, &colunas);
        char frase[TAMANHO_FRASE] = "";
        dividir(matriz, 0, 0, linhas, colunas, frase);
    } else {
        exibirAjuda();
    }
}
