#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void introducao(){

    printf("==========================================================ANÁLISE DE VIAGENS==========================================================\n\n");
    printf("Digite a quantidade de cidades que voce deseja percorrer: ");
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

    char city[30][100] = {
                        "Uruaçu",
                        "Sao Miguel do Araguaia",
                        "Santa Rita do Araguaia",
                        "Santa Helena de Goiás",
                        "Rio Verde", 
                        "Posse", 
                        "PORANGATU", 
                        "Pires do Rio",  
                        "Pirenopolis",   
                        "Pilar de Goias",
                        "Niquelandia",   
                        "Mineiros",      
                        "Minaçu",        
                        "Luziania",      
                        "Jatai",         
                        "Itumbiara",     
                        "Itaja",         
                        "Goiania",       
                        "Goianesia",     
                        "Goias",         
                        "Formosa",       
                        "Cristalina",    
                        "Ceres",         
                        "Catalao",       
                        "Campos Belos" , 
                        "Caldas Novas",  
                        "Brasilia",      
                        "Anapolis",      
                        "Aruana",        
                        "Aragarças",     
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
    printf("\n\nAS CIDADES DISPONÍVEIS NO MOMENTO SÃO:\n\n");
    for(i = 0; i < 9; i++){
        if(i > 0){
            printf("-%s\n", n1.cidades[i]);
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


int calc_distancia(Transito n1, int indice_partida, int indice_destino){

    int km;

    km = n1.distancia[indice_partida][indice_destino];

    return km;
}

void calc_tempo(int km, int *horas, int *minutos){
    
    int tempo;   

    tempo = (km * 60)/80;

    *horas = tempo / 60;
    *minutos = tempo % 60;
 
}


void calc_combustivel(){}

void calc_preco_combustivel(){}

void qual_cidade_abastecer(){}



int main(){
    Transito n1;
    int qtd, i, indice_partida, indice_destino;
    int *pi;
    char partida[50], destino[50];
    int distancia;
    int horas, minutos;

    n1.distancia = NULL;
    n1.cidades = NULL;

    init_distancia(&n1); //inicializando a distancia entre as cidades com alocacao de memoria

    init_cidades(&n1); //inicializando o nome das cidades com alocacao de memoria

    introducao();

    scanf("%d%*c", &qtd);

    pi = (int *) malloc(qtd * sizeof(int)); // alocando a memoria necessaria para armazenar os indices das cidades

    printf("Digite o nome da cidade que voce deseja inicializar seu trajeto, em letras minusculas:\n");

    print_cidades(n1); //mostro na tela as cidades disponiveis para navegação

    scanf("%[^\n]%*c", partida); // leio a string ate o enter

    indice_partida = comparar_string(n1, partida);

    printf("\n\nDigite o nome da cidade destino, em letras minusculas:\n\n");

    scanf("%[^\n]%*c", destino);

    indice_destino = comparar_string(n1, destino);

    distancia = calc_distancia(n1, indice_partida, indice_destino);

    calc_tempo(distancia, &horas, &minutos);

    printf("Sua viagem demorará %d horas e %d minutos\n", horas, minutos);












    free_matrizes(&n1); // liberando memoria alocada  

    free(pi); // liberando memoria alocada 

    return 0;
}