#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAMANHO 3
#define TAMANHO_FRASE 100


void escolha(char valor[], char arquivo[]);
void lerArquivo(char arquivo[]);
void exibirAjuda();
bool todosIguais(int matriz[][TAMANHO], int inicioLinha, int inicioColuna, int finalLinha, int finalColuna);
void dividir(int matriz[][TAMANHO], int inicioLinha, int inicioColuna, int finalLinha, int finalColuna, char frase[]);
void colocaLetra(int matriz[][TAMANHO], int inicioLinha, int inicioColuna, char frase[]);

int main(int argc, char **argv){

   // Teste
    int matriz[3][TAMANHO];

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < TAMANHO; j++){
            scanf("%d", &matriz[i][j]);
        }
        printf("\n");
    }

    int linha = 3;
    int coluna = TAMANHO;
    char frase[TAMANHO_FRASE] = "";

    dividir(matriz, 0, 0, linha, coluna, frase);
    printf("%s", frase);
    
    return 0;
}

void dividir(int matriz[][TAMANHO], int inicioLinha, int inicioColuna, int finalLinha, int finalColuna, char frase[]){

    if (todosIguais(matriz, inicioLinha, inicioColuna, finalLinha, finalColuna)){
        colocaLetra(matriz,inicioLinha, inicioColuna, frase);
        return;
    }

    char letra[2] = "X\0";
    strcat(frase, letra);

    int divisaoInicioLinha;
    int divisaoInicioColuna;

    int divisaoFinalLinha;
    int divisaoFinalColuna;

    //Quadrante 1
    divisaoInicioLinha = inicioLinha;
    divisaoFinalLinha = (finalLinha % 2 == 0) ? finalLinha/2: finalLinha/2 + 1;
    divisaoInicioColuna = inicioColuna;
    divisaoFinalColuna = (finalColuna % 2 == 0) ? finalColuna/2: finalColuna/2 + 1;
    dividir(matriz, divisaoInicioLinha, divisaoInicioColuna, divisaoFinalLinha, divisaoFinalColuna, frase);
    
    //Quadrante 2
    divisaoInicioLinha = inicioLinha;
    divisaoFinalLinha = (finalLinha % 2 == 0) ? finalLinha/2: finalLinha/2+1;
    divisaoInicioColuna = (finalColuna % 2 == 0) ? finalColuna/2: finalColuna/2 + 1;
    divisaoFinalColuna = finalColuna;
    dividir(matriz, divisaoInicioLinha, divisaoInicioColuna, divisaoFinalLinha, divisaoFinalColuna, frase);

    //Quadrante 3
    divisaoInicioLinha = (finalLinha % 2 == 0) ? finalLinha/2 : finalLinha/2 + 1;
    divisaoFinalLinha = finalLinha;
    divisaoInicioColuna = inicioColuna;
    divisaoFinalColuna = (finalColuna % 2 == 0) ? finalColuna/2: finalColuna/ 2 + 1;
    dividir(matriz, divisaoInicioLinha, divisaoInicioColuna, divisaoFinalLinha, divisaoFinalColuna, frase);

    //Quadrante 4
    divisaoInicioLinha = (finalLinha % 2 == 0) ? finalLinha/2: finalLinha/2 + 1;
    divisaoFinalLinha = finalLinha;
    divisaoInicioColuna = (finalColuna % 2 == 0) ? finalColuna / 2: finalColuna/2 + 1;
    divisaoFinalColuna = finalColuna;
    dividir(matriz, divisaoInicioLinha, divisaoInicioColuna, divisaoFinalLinha, divisaoFinalColuna, frase);
}


bool todosIguais(int matriz[][TAMANHO], int inicioLinha, int inicioColuna, int finalLinha, int finalColuna){
    if (inicioColuna == finalColuna && inicioLinha == finalLinha) return true;
    
    int cor;
    cor = matriz[inicioLinha][inicioColuna];

    if (inicioLinha == finalLinha && inicioLinha + 1 == finalLinha){
        for (int i = inicioColuna; i < finalColuna; i++){
            if (cor != matriz[inicioColuna][i]) return false;
        }
        return true;
    }
    if (inicioColuna == finalColuna && inicioColuna + 1 == finalColuna){
        for (int i = inicioLinha; i < finalLinha; i++){
            if (cor != matriz[i][inicioColuna]) return false;
        }
        return true;
    }
    

    for (int i = inicioLinha; i < finalLinha; i++){
        for (int j = inicioColuna; j < finalColuna; j++){
            if (cor != matriz[i][j]) 
                return false; 
        }
        
    }
    return true;
}

void colocaLetra(int matriz[][TAMANHO], int inicioLinha, int inicioColuna, char frase[]){
    char letra[2];
    if (matriz[inicioLinha][inicioColuna] == 0){
        letra[0] = 'B';
    }
    else if (matriz[inicioLinha][inicioColuna] == 1){
        letra[0] = 'P';
    }
    
    letra[1] = '\0';

    strcat(frase, letra);
}

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