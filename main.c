#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void escolha(char valor[], char arquivo[]);

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

void escolha(char valor[], char arquivo[]){

    if (strcmp(valor, "-?") == 0 || strcmp(valor, "--help") == 0){
        printf("Help\n");
        //menu();
    }
    if (strcmp(valor, "-m") == 0|| strcmp(valor, "--manual") == 0){
        //inserirDados();
        printf("Inserir dados");
    }
    if (strcmp(valor, "-f") == 0 || strcmp(valor, "--file") == 0){
        printf("Ler arquivo\n");
        //lerArquivo(arquivo);
    }
}