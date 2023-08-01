#include <stdio.h>
#include <stdlib.h>

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
        "Vazio",
        "Goiania", 
        "Aparecida de Goiania", 
        "Anapolis",
        "Rio Verde",
        "Trindade",
        "Caldas Novas",
        "Goianira",
        "Jatai"
    };

    for(i = 0; i < 9; i++){
        for(j = 0; city[i][j] != '\0'; j++){
            n1->cidades[i][j] = city[i][j];
        }
        n1->cidades[i][j] = '\0'; 
    }
}



void comparar_string(){}

void calc_distancia(){}

void calc_tempo(){}

void calc_combustivel(){}

void calc_preco_combustivel(){}



int main(){
    Transito n1;
    int qtd, i;

    n1.distancia = NULL;
    n1.cidades = NULL;

    introducao();

    init_distancia(&n1); //inicializando a distancia entre as cidades com alocacao de memoria

    init_cidades(&n1); //inicializando o nome das cidades com alocacao de memoria

    return 0;
}