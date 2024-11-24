#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINHAS 1024
#define MAX_COLUNAS 768
#define TAMANHO_FRASE 100

// Protótipos das funções
void escolha(char valor[], char arquivo[]);
void lerArquivo(char arquivo[]);
void inserirDados();
void exibirAjuda();
bool todosIguais(int matriz[MAX_LINHAS][MAX_COLUNAS], int inicioLinha, int inicioColuna, int finalLinha, int finalColuna);
void dividir(int matriz[MAX_LINHAS][MAX_COLUNAS], int inicioLinha, int inicioColuna, int finalLinha, int finalColuna, char frase[]);
void colocaLetra(int matriz[MAX_LINHAS][MAX_COLUNAS], int inicioLinha, int inicioColuna, char frase[]);
int retornaCentro(int inicio, int final);

// Função principal
int main(int argc, char **argv) {

    // Verifica se o número de argumentos é menor que 2 para exibir o menu de ajuda
    if (argc < 2) {
        exibirAjuda();
        return 1;
    }

    // String para armazenar o argumento e o nome do arquivo
    char argumento[25];
    char nomeArquivo[25];

    strcpy(argumento, argv[1]); 

    // Copia o nome do arquivo para a variável 'nomeArquivo'
    if (argc > 2) {
        strcpy(nomeArquivo, argv[2]);
    }

    // Chama a função que decidirá o que fazer com base no argumento fornecido
    escolha(argumento, nomeArquivo);

    return 0;
}

//Divide a matriz em 4 quadrantes
void dividir(int matriz[MAX_LINHAS][MAX_COLUNAS], int inicioLinha, int inicioColuna, int finalLinha, int finalColuna, char frase[]) {
    
    //Caso-base para sair da recursão
    if (todosIguais(matriz, inicioLinha, inicioColuna, finalLinha, finalColuna)) {
        colocaLetra(matriz, inicioLinha, inicioColuna, frase);
        return;
    }
    
    //Adiciona a letra X à frase, caso seja necessário realizar uma divisão
    char letra[2] = "X\0";
    strcat(frase, letra);

    //Valor do central da coluna
    int centroColuna = retornaCentro(inicioColuna, finalColuna);

    //Valor central da linha
    int centroLinha = retornaCentro(inicioLinha, finalLinha);

    // Quadrante 1
    dividir(matriz, inicioLinha, inicioColuna, centroLinha, centroColuna, frase);

    // Quadrante 2
    dividir(matriz, inicioLinha, centroColuna, centroLinha, finalColuna, frase);

    //Se tivermos que dividir um vetor, teremos uma repetição dos quadrantes 3 e 4.
    //A condição serve para ignorar isso 
    if (centroLinha != finalLinha) {
        // Quadrante 3
        dividir(matriz, centroLinha, inicioColuna, finalLinha, centroColuna, frase);

        // Quadrante 4
        dividir(matriz, centroLinha, centroColuna, finalLinha, finalColuna, frase);
    }
}

//Função que pega a letra presente no quadrante e coloca na frase principal
void colocaLetra(int matriz[MAX_LINHAS][MAX_COLUNAS], int inicioLinha, int inicioColuna, char frase[]) {
    char letra[2];
    if (matriz[inicioLinha][inicioColuna] == 0) {
        letra[0] = 'B';
    } else if (matriz[inicioLinha][inicioColuna] == 1) {
        letra[0] = 'P';
    }

    letra[1] = '\0';
    strcat(frase, letra);
}

// Função para ler o arquivo
void lerArquivo(char arquivo[]) {

    // Abre o arquivo
    FILE* arquivosaida = fopen(arquivo, "r");
    if (arquivosaida == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int linhas, colunas;
    char linha[100];

    // Pula a primeira linha (P1)
    fgets(linha, sizeof(linha), arquivosaida);

    // Ignora os comentários que começam com #
    do {
        if (fgets(linha, sizeof(linha), arquivosaida) == NULL) {
            fclose(arquivosaida);
            return;
        }
    } while (linha[0] == '#');

    // Lê o número de linhas e colunas 
    sscanf(linha, "%d %d", &colunas, &linhas);

    int matriz[MAX_LINHAS][MAX_COLUNAS];

    // Lê os valores do arquivo e os guarda em uma matriz
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fscanf(arquivosaida, "%d", &matriz[i][j]);
        }
    }
    fclose(arquivosaida);

    // Imprime a matriz lida
    printf("Matriz lida do arquivo (%dx%d):\n", linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // Chama a função de dividir e imprime o resultado
    char frase[TAMANHO_FRASE] = "";
    dividir(matriz, 0, 0, linhas, colunas, frase);
    printf("%s", frase);
}

// Função para inserir os dados manualmente
void inserirDados() {
    int linhas, colunas;

    // Pede a altura e largura da imagem para o usuário
    printf("Digite a altura: ");
    scanf("%d", &linhas);
    printf("Digite a largura: ");
    scanf("%d", &colunas);

    int matriz[MAX_LINHAS][MAX_COLUNAS];

    // Lê os valores inseridos
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("linha %d, coluna %d: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    // Imprime a matriz inserida
    printf("Matriz inserida (%dx%d):\n", linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // Chama a função de dividir e imprime o resultado
    char frase[TAMANHO_FRASE] = "";
    dividir(matriz, 0, 0, linhas, colunas, frase);
    printf("%s", frase);
}

// Função de impressão do menu de ajuda
void exibirAjuda() {
    printf("Uso: ImageEncoder [-? | -m | -f ARQ]\n");
    printf("Codifica imagens binarias dadas em arquivos PBM ou dados informados manualmente.\n");
    printf("Argumentos:\n");
    printf("  -?, --help    : Apresenta esta orientacao na tela.\n");
    printf("  -m, --manual  : Ativa o modo de entrada manual, em que o usuario fornece os dados da imagem via teclado.\n");
    printf("  -f, --file ARQ: Le a imagem representada no arquivo PBM (Portable Bitmap).\n");
}

// Função da escolha do menu para: ajuda, inserir a imagem manualmente ou ler arquivo
void escolha(char valor[], char arquivo[]) {
    if (strcmp(valor, "-?") == 0 || strcmp(valor, "--help") == 0) {
        exibirAjuda();
    } else if (strcmp(valor, "-m") == 0 || strcmp(valor, "--manual") == 0) {
        inserirDados();
    } else if (strcmp(valor, "-f") == 0 || strcmp(valor, "--file") == 0) {
        lerArquivo(arquivo);
    } else {
        exibirAjuda();
    }
}

//Função que verifica se todos os elementos da matriz são iguais. Retorna verdadeiro ou falso
bool todosIguais(int matriz[MAX_LINHAS][MAX_COLUNAS], int inicioLinha, int inicioColuna, int finalLinha, int finalColuna) {
    if (inicioColuna == finalColuna && inicioLinha == finalLinha) return true;

    int cor = matriz[inicioLinha][inicioColuna];

    if (inicioLinha == finalLinha) {
        for (int i = inicioColuna; i < finalColuna; i++) {
            if (cor != matriz[inicioLinha][i]) return false;
        }
        return true;
    }

    if (inicioColuna == finalColuna) {
        for (int i = inicioLinha; i < finalLinha; i++) {
            if (cor != matriz[i][inicioColuna]) return false;
        }
        return true;
    }

    for (int i = inicioLinha; i < finalLinha; i++) {
        for (int j = inicioColuna; j < finalColuna; j++) {
            if (cor != matriz[i][j]) {
                return false;
            }
        }
    }
    return true;
}

//Função que faz a divisão da linha ou coluna
int retornaCentro(int inicio, int final) {
    if ((inicio + final) % 2 == 0) {
        return (inicio + final) / 2;
    }
    return (inicio + final) / 2 + 1;
}
