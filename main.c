#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAMANHO 2
#define TAMANHO_FRASE 100


void escolha(char valor[], char arquivo[]);
void lerArquivo(char arquivo[]);
void exibirAjuda();
bool todosIguais(int matriz[][TAMANHO], int linha, int coluna);
void dividir(int matriz[][TAMANHO], int linha, int coluna, char frase[]);
void colocaLetra(int matriz[][TAMANHO], char frase[]);


int main(int argc, char **argv){

    /*
    char argumento[TAMANHO];
    char nomeArquivo[TAMANHO];
    strcpy(argumento, argv[1]);
    strcpy(nomeArquivo, argv[2]);
    
    escolha(argumento, nomeArquivo);
    */

   // Teste
    int matriz[2][2];

    for (int i = 0; i < 2; i++){
        printf("Linha %d\n", i+1);

        for (int j = 0; j < 2; j++){
            scanf("%d", &matriz[i][j]);
        }
        printf("\n");
    }

    int linha = 2;
    int coluna = 2;

    char frase[TAMANHO_FRASE] = "";

    dividir(matriz, linha, coluna, frase);
    printf("%s", frase);
    
    return 0;
}

void dividir(int matriz[][TAMANHO], int linha, int coluna, char frase[]){
    char letra[2] = "X\0";
    strcat(frase, letra);

    if (todosIguais(matriz, linha, coluna)){
        colocaLetra(matriz, frase);
        return;
    }

    /*
    char = dividir(matriz[/2], tamanho/2);
    char = dividir()
    char =
    char
    */
}


bool todosIguais(int matriz[][TAMANHO], int linha, int coluna){
    int cor = matriz[0][0];
    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            if (cor != matriz[i][j]) return false;
        }
        
    }
    return true;
}

void colocaLetra(int matriz[][TAMANHO], char frase[]){
    char letra[2];
    if (matriz[0][0] == 0){
        letra[0] = 'B';
    }
    else{
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
