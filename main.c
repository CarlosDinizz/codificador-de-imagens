#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void escolha(char valor[], char arquivo[]);
void lerArquivo(char arquivo[]);
void exibirAjuda();

#define TAMANHO 25

int main(int argc, char **argv){

    char argumento[TAMANHO];
    char nomeArquivo[TAMANHO];
    strcpy(argumento, argv[1]);
    strcpy(nomeArquivo, argv[2]);
    

    escolha(argumento, nomeArquivo);
    
    return 0;
}

/*
bool todosIguais(int matriz[][], int linha, int coluna){
    
}
*/

void lerArquivo(char arquivo[]) {
    FILE *arquivosaida = fopen(arquivo, "r");
    if (arquivosaida == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int linhas, colunas;
    fscanf(arquivosaida, "%d %d", &linhas, &colunas);
    int matriz[linhas][colunas];

    for (int i = 0; i < colunas; i++) {
        for (int j = 0; j < linhas; j++) {
            fscanf(arquivosaida, "%d", &matriz[i][j]);
        }
    }
    fclose(arquivosaida);

    printf("Matriz lida do arquivo (%dx%d):\n", linhas, colunas);
    for (int i = 0; i < colunas; i++) {
        for (int j = 0; j < linhas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
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
    }
    if (strcmp(valor, "-m") == 0 || strcmp(valor, "--manual") == 0) {
        //inserirDados();
        printf("Inserir dados\n");
    }
    if (strcmp(valor, "-f") == 0 || strcmp(valor, "--file") == 0) {
        lerArquivo(arquivo);
    }
    else {
        exibirAjuda();
    }
}
