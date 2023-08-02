#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void introducao(){

    printf("==========================================================ANÁLISE DE VIAGENS==========================================================\n\n");
    
}

struct transito{
    int **distancia;
    char **cidades;
    float dinheiro, combustivel;
    int horas, minutos;
};

typedef struct transito Transito; //definindo o nome da estrutura

void init_distancia(Transito *n1){
    int i, j;

    n1->distancia = (int **) malloc(9 * sizeof(int *)); //alocando a matriz de inteiros

    for(i = 0; i < 9; i++){
        n1->distancia[i] = (int *) malloc(9 * sizeof(int )); //alocando cada linha da matriz de inteiros
    }

    int kilometragem[9][9] = { 
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 20, 60, 230, 27, 170, 30, 321,
        0, 20, 0, 73, 234, 44, 147, 48, 323,
        0, 60, 73, 0, 295, 86, 220, 70, 384,
        0, 230, 234, 295, 0, 225, 313, 249, 91,
        0, 27, 44, 86, 225, 0, 195, 25, 314,
        0, 170, 147, 220, 313, 195, 0, 203, 401,
        0, 30, 48, 70, 249, 25, 203, 0, 321,
        0, 321, 323, 384, 91, 314, 401, 321, 0
    };

    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            n1->distancia[i][j] = kilometragem[i][j];
        }
    }
    
}

void init_cidades(Transito *n1){
    int i, j;

    n1->cidades = (char **) malloc(9 * sizeof(char *)); //alocando a matriz de char

    for(i = 0; i < 9; i++){
        n1->cidades[i] = (char *) malloc(50 * sizeof(char)); //alocando cada linha da matriz de char
    }

    char city[9][50] = {
        "vazio",
        "goiania", 
        "aparecida de goiania", 
        "anapolis",
        "rio verde",
        "trindade",
        "caldas novas",
        "goianira",
        "jatai"
    };

    for(i = 0; i < 9; i++){
        for(j = 0; city[i][j] != '\0'; j++){
            n1->cidades[i][j] = city[i][j];
        }
        n1->cidades[i][j] = '\0'; 
    }
}

void free_matrizes(Transito *n1){
    int i;

    for(i = 0; i < 9; i++){
        free(n1->cidades[i]);
        free(n1->distancia[i]);
    }

    free(n1->cidades);
    free(n1->distancia);
}

void print_cidades(Transito n1){
    int i;
    for(i = 0; i < 9; i++){
        if(i > 0){
            printf("%d.%s\n", i, n1.cidades[i]);
        }
    }
    printf("\n");
}



int comparar_string(Transito n1, char *str){
    int i;
    while(1){
        for(i = 0; i < 9; i++){
            if(strcmp(n1.cidades[i], str) == 0){
                return i;
            }
        }
        printf("Cidade nao encontrada, digite novamente por favor: ");
        scanf("%[^\n]%*c", str); // leio a string ate o enter
    }
}

void calc_distancia(){}

void calc_tempo(){}

void calc_combustivel(){}

void calc_preco_combustivel(){}

void qual_cidade_abastecer(){}



int main(){
    Transito n1;
    int qtd, i, indice;
    int *pi;
    char str[50];

    n1.distancia = NULL;
    n1.cidades = NULL;

    init_distancia(&n1); //inicializando a distancia entre as cidades com alocacao de memoria

    init_cidades(&n1); //inicializando o nome das cidades com alocacao de memoria

    introducao();

    printf("Digite a quantidade de cidades que voce deseja percorrer: ");

    scanf("%d%*c", &qtd);

    pi = (int *) malloc(qtd * sizeof(int)); // alocando a memoria necessaria para armazenar os indices das cidades

    printf("Digite o nome da cidade que voce deseja inicializar seu trajeto, em letras minusculas:\n");

    print_cidades(n1); //mostro na tela as cidades disponiveis para navegação

    scanf("%[^\n]%*c", str); // leio a string ate o enter

    indice = comparar_string(n1, str);

    free_matrizes(&n1); // liberando memoria alocada  

    free(pi); // liberando memoria alocada 

    return 0;
}