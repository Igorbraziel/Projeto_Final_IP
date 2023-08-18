#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 100

void introducao(){
    sleep(1);
    printf("\nDigite a quantidade de viagens que voce deseja fazer: \n");

}

struct transito{
    int **distancia;
    char **cidades;
    char tipoComb[32], indiceComb;
    float dinheiro, combustivel, combustivelTotal;
    int horas, minutos, horasf, minutosf;
    int km, kmf;
};

typedef struct transito Transito; //definindo o nome da estrutura

void init_distancia(Transito *n1){
    int i, j;

    n1->distancia = (int **) malloc(30 * sizeof(int *)); //alocando a matriz de inteiros

    for(i = 0; i < 30; i++){
        n1->distancia[i] = (int *) malloc(30 * sizeof(int )); //alocando cada linha da matriz de inteiros
    }

    int kilometragem[30][30] = { 
        0, 266, 781, 506, 525, 558, 133, 394, 209, 115, 83, 695, 226, 410, 604, 465, 686, 278, 105, 255, 329, 475, 107, 507, 655, 448, 248, 238, 430, 498,  
        266, 0, 907, 601, 620, 907, 133, 633, 475, 381, 349, 821, 304, 676, 707, 673, 799, 486, 371, 338, 595, 741, 373, 773, 1086, 656, 917, 504, 274, 581, 
        781, 907, 0, 341, 284, 1029, 915, 663, 641, 750, 865, 94, 1008, 705, 195, 498, 388, 516, 690, 569, 800, 856, 675, 697, 1116, 604, 719, 571, 744, 412, 
        506, 601, 341, 0, 54, 723, 624, 413, 335, 459, 574, 255, 717, 397, 141, 173, 233, 210, 404, 263, 494, 531, 384, 378, 810, 285, 413, 265, 438, 385,   
        525, 620, 284, 54, 0, 742, 643, 445, 354, 473, 593, 201, 736, 418, 87, 205, 179, 229, 423, 282, 513, 563, 403, 410, 829, 317, 432, 284, 457, 333,   
        558, 907, 1029, 723, 742, 0, 691, 547, 452, 606, 561, 943, 784, 377, 829, 739, 921, 513, 534, 565, 235, 442, 541, 618, 609, 613, 310, 462, 744, 813,
        133, 133, 915, 624, 643, 691, 0, 527, 342, 248, 216, 829, 171, 679, 737, 598, 819, 411, 238, 389, 462, 608, 240, 640, 777, 581, 370, 371, 407, 631,
        394, 633, 663, 413, 445, 547, 527, 0, 222, 394, 399, 577, 651, 178, 463, 240, 543, 147, 293, 296, 318, 130, 75, 109, 646, 107, 239, 156, 492, 554,   
        209, 475, 641, 335, 354, 452, 342, 222, 0, 177, 207, 555, 438, 236, 441, 312, 533, 125, 107, 140, 223, 301, 191, 329, 549, 286, 142, 64, 315, 384,  
        83, 349, 865, 574, 593, 561, 216, 399, 207, 0, 198, 664, 341, 379, 572, 433, 654, 246, 126, 224, 377, 444, 75, 472, 703, 416, 296, 207, 399, 466, 
        83, 349, 865, 574, 593, 561, 216, 399, 207, 198, 0, 734, 309, 308, 687, 491, 712, 304, 172, 339, 332, 373, 190, 508, 654, 474, 251, 243, 513, 581,  
        695, 821, 94, 255, 201, 943, 829, 577, 555, 664, 734, 0, 922, 619, 109, 406, 302, 430, 613, 483, 714, 764, 589, 611, 1023, 518, 633, 485, 658, 326, 
        226, 304, 1008, 717, 736, 784, 171, 651, 438, 341, 309, 922, 0, 636, 830, 691, 912, 504, 331, 482, 555, 701, 333, 733, 784, 674, 474, 464, 578, 724,
        410, 676, 705, 397, 418, 377, 679, 178, 236, 379, 308, 619, 636, 0, 505, 369, 597, 189, 305, 320, 135, 79, 307, 261, 499, 242, 61, 172, 495, 564,     
        604, 707, 195, 141, 87, 829, 737, 463, 441, 572, 687, 109, 830, 505, 0, 292, 203, 316, 510, 369, 600, 650, 490, 497, 833, 425, 523, 371, 544, 269,    
        465, 673, 498, 173, 205, 739, 598, 240, 312, 433, 491, 406, 691, 369, 292, 0, 303, 187, 744, 383, 504, 358, 368, 205, 704, 133, 423, 242, 558, 538,   
        686, 799, 388, 233, 179, 921, 819, 543, 533, 654, 712, 302, 912, 597, 203, 303, 0, 408, 557, 461, 692, 661, 589, 508, 1008, 436, 611, 463, 636, 472,
        278, 486, 516, 210, 229, 513, 411, 147, 125, 246, 304, 430, 504, 189, 316, 187, 408, 0, 172, 149, 284, 277, 181, 255, 600, 170, 203, 55, 324, 407,   
        105, 371, 690, 404, 423, 534, 238, 293, 107, 126, 172, 613, 331, 305, 510, 744, 557, 172, 0, 169, 307, 370, 61, 402, 629, 365, 226, 137, 344, 413,   
        255, 338, 569, 263, 282, 565, 389, 296, 140, 224, 339, 483, 482, 320, 369, 383, 461, 149, 169, 0, 340, 385, 149, 455, 656, 319, 259, 161, 175, 244,  
        329, 595, 800, 494, 513, 235, 462, 318, 223, 377, 332, 714, 555, 135, 600, 504, 692, 284, 307, 340, 0, 207, 312, 389, 357, 384, 81, 233, 515, 584,   
        475, 741, 856, 531, 563, 442, 608, 130, 301, 444, 373, 764, 701, 79, 650, 358, 661, 277, 370, 385, 207, 0, 379, 182, 564, 225, 126, 237, 560, 629,   
        107, 373, 675, 384, 403, 541, 240, 75, 191, 75, 190, 589, 333, 307, 490, 368, 589, 181, 61, 149, 312, 379, 0, 407, 634, 351, 231, 142, 324, 391,     
        507, 773, 697, 378, 410, 618, 640, 109, 329, 472, 508, 611, 733, 261, 497, 205, 508, 255, 402, 455, 389, 182, 407, 0, 723, 118, 308, 265, 630, 692,   
        655, 1086, 1116, 810, 829, 609, 777, 646, 549, 703, 654, 1023, 784, 499, 833, 704, 1008, 600, 629, 656, 357, 564, 634, 723, 0, 720, 407, 559, 831, 900,
        448, 656, 604, 285, 317, 613, 581, 107, 286, 416, 474, 518, 674, 242, 425, 133, 436, 170, 365, 319, 384, 225, 351, 118, 720, 0, 303, 222, 494, 574,
        248, 917, 719, 413, 432, 310, 370, 239, 142, 296, 251, 633, 474, 61, 523, 423, 611, 203, 226, 259, 81, 126, 231, 308, 407, 303, 0, 152, 434, 503,
        238, 504, 571, 265, 284, 462, 371, 156, 64, 207, 243, 485, 464, 172, 371, 242, 463, 55, 137, 161, 233, 237, 142, 265, 559, 222, 152, 0, 336, 405,
        430, 274, 744, 438, 457, 744, 407, 492, 315, 399, 513, 658, 578, 495, 544, 558, 636, 324, 344, 175, 515, 560, 324, 630, 831, 494, 434, 336, 0, 419,  
        498, 581, 412, 385, 333, 813, 631, 554, 384, 466, 581, 326, 724, 564, 269, 538, 472, 407, 413, 244, 584, 629, 391, 692, 900, 574, 503, 405, 419, 0,
        };

    for(i = 0; i < 30; i++){
        for(j = 0; j < 30; j++){
            n1->distancia[i][j] = kilometragem[i][j];
        }
    }
    
}

void init_cidades(Transito *n1){
    int i, j;

    n1->cidades = (char **) malloc(30 * sizeof(char *)); //alocando a matriz de char

    for(i = 0; i < 30; i++){
        n1->cidades[i] = (char *) malloc(100 * sizeof(char)); //alocando cada linha da matriz de char
    }

    char city[30][100] = {
                        "uruacu",
                        "sao miguel do araguaia",
                        "santa rita do araguaia",
                        "santa helena de goias",
                        "rio verde", 
                        "posse", 
                        "porangatu", 
                        "pires do rio",  
                        "pirenopolis",   
                        "pilar de goias",
                        "niquelandia",   
                        "mineiros",      
                        "minacu",        
                        "luziania",      
                        "jatai",         
                        "itumbiara",     
                        "itaja",         
                        "goiania",       
                        "goianesia",     
                        "goias",         
                        "formosa",       
                        "cristalina",    
                        "ceres",         
                        "catalao",       
                        "campos belos" , 
                        "caldas novas",  
                        "brasilia",      
                        "anapolis",      
                        "aruana",        
                        "aragarças"     
    };

    for(i = 0; i < 30; i++){
        for(j = 0; city[i][j] != '\0'; j++){
            n1->cidades[i][j] = city[i][j];
        }
        n1->cidades[i][j] = '\0'; 
    }
}

void free_matrizes(Transito *n1){
    int i;

    for(i = 0; i < 30; i++){
        free(n1->cidades[i]);
        free(n1->distancia[i]);
    }

    free(n1->cidades);
    free(n1->distancia);
}

void print_cidades(Transito n1){
    int i;
    printf("\nAS CIDADES DISPONÍVEIS NO MOMENTO SÃO:\n\n");
    for(i = 0; i < 30; i++){
            printf("-%s\n", n1.cidades[i]);
    }
    printf("\n");
}



int comparar_string(Transito n1, char *str){
    int i;

    while(1){
        for(i = 0; i < 30; i++){
            if(strcmp(n1.cidades[i], str) == 0){
                return i;
            }
        }
        printf("Cidade não encontrada, digite novamente por favor: ");
        scanf("%[^\n]%*c", str); // leio a string ate o enter
    }
}


int calc_distancia(Transito n1, int indice_partida, int indice_destino){

    int km;

    km = n1.distancia[indice_partida][indice_destino];

    return km;
}

void calc_tempo(int km, Transito *n1){ 

    n1->minutos = (km * 60)/80;

    while(n1->minutos >= 60){
        n1->horas++;
        n1->minutos -= 60;
    }
 
}

void calc_combustivel(Transito *n1, float *valor, float *litros, int indice){
    float x;

    while(1){
        if(n1->indiceComb == 1){
            if((n1->combustivel * 12) < n1->km){
                printf("\nVocê deverá abastecer em %s!!!\n", n1->cidades[indice]);
                x = n1->km - (n1->combustivel * 12);
                *litros = x/12;
                *valor = (*litros) * 5.5;
                sleep(2);
                printf("Você precisará de %.2f litros de gasolina\n", *litros);
                sleep(2);
                printf("O valor será R$%.2f\n", *valor);
                sleep(1);
                break;
            } else {
                printf("\nVocê possui combustível suficiente\n");
                break;
            }
        } else if(n1->indiceComb == 2){
            if((n1->combustivel * 8) < n1->km){
                printf("\nVocê deverá abastecer em %s!!!\n", n1->cidades[indice]);
                x = n1->km - (n1->combustivel * 8);
                *litros = x/8;
                *valor = (*litros) * 3.5;
                sleep(2);
                printf("Você precisará de %.2f litros de etanol\n", *litros);
                sleep(2);
                printf("O valor será R$%.2f\n", *valor);
                sleep(1);
                break;
            } else {
                printf("\nVocê possui combustível suficiente\n");
                break;
            }
        } else if(n1->indiceComb == 3){
            if((n1->combustivel * 15) < n1->km){
                printf("\nVocê deverá abastecer em %s!!!\n", n1->cidades[indice]);
                x = n1->km - (n1->combustivel * 15);
                *litros = x/15;
                *valor = (*litros) * 4.98;
                sleep(2);
                printf("Você precisará de %.2f litros de diesel\n", *litros);
                sleep(2);
                printf("O valor será R$%.2f\n", *valor);
                sleep(1);
                break;
            } else {
                printf("\nVocê possui combustível suficiente\n");
                break;
            }
        }
    }
    n1->combustivel = 0;
}

void autonomia(Transito n1){
    if(n1.indiceComb == 1){
        printf("\n\nO alcance do seu carro no momento é de: %d KM\n", (int) n1.combustivel * 12);
    } else if(n1.indiceComb == 2){
        printf("\n\nO alcance do seu carro no momento é de: %d KM\n", (int) n1.combustivel * 8);
    } else if(n1.indiceComb == 3){
        printf("\n\nO alcance do seu carro no momento é de: %d KM\n", (int) n1.combustivel * 15);
    }
}

int escolhe_combustivel(Transito *n1){

    printf("Combustíveis disponíveis:\n-gasolina\n-etanol\n-diesel\n");

    printf("\nDigite o tipo de combustível que você deseja utilizar, em letras minusculas:\n");

    scanf("%s%*c", n1->tipoComb); // leio a string 

    while(1){
        if(strcmp(n1->tipoComb, "gasolina") == 0) return 1;
        if(strcmp(n1->tipoComb, "etanol") == 0) return 2;
        if(strcmp(n1->tipoComb, "diesel") == 0) return 3;
        printf("Combustível indisponivel, digite novamente: ");
        scanf("%s%*c", n1->tipoComb); // leio a string ate o enter
    }

}

void diminui_combustivel(Transito *n1){
    int km = n1->km;

    if(n1->indiceComb == 1){
        while(km > 12){
            n1->combustivel--;
            km -= 12;
        }
    } else if(n1->indiceComb == 2){
        while(km > 8){
            n1->combustivel--;
            km -= 8;
        }
    } else if(n1->indiceComb == 3){
        while(km > 15){
            n1->combustivel--;
            km -= 15;
        }
    }
}

void printUpper(char *str){
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] != ' '){
            printf("%c", str[i] - 32);
        } else{
            printf("%c", str[i]);
        }
        i++;
    }
    printf("\n\n");
}

void introducao1(){
    sleep(2);
    printf("\nDigite a quantidade de viagens que voce deseja fazer: \n");
}

struct transito1{
    int **distancia1;
    char **cidades1;
    float dinheiro1, combustivel1;
    int horas1, minutos1;
    char tipoComb1[32];
    int indice_cidade_final1[100];
};

typedef struct transito1 Transito1; //definindo o nome da estrutura

void init_distancia1(Transito1 *n1){
    int i, j;

    n1->distancia1 = (int **) malloc(30 * sizeof(int *)); //alocando a matriz de inteiros

    for(i = 0; i < 30; i++){
        n1->distancia1[i] = (int *) malloc(30 * sizeof(int )); //alocando cada linha da matriz de inteiros
    }

    int kilometragem[30][30] = { 
        0, 266, 781, 506, 525, 558, 133, 394, 209, 115, 83, 695, 226, 410, 604, 465, 686, 278, 105, 255, 329, 475, 107, 507, 655, 448, 248, 238, 430, 498,  
        266, 0, 907, 601, 620, 907, 133, 633, 475, 381, 349, 821, 304, 676, 707, 673, 799, 486, 371, 338, 595, 741, 373, 773, 1086, 656, 917, 504, 274, 581, 
        781, 907, 0, 341, 284, 1029, 915, 663, 641, 750, 865, 94, 1008, 705, 195, 498, 388, 516, 690, 569, 800, 856, 675, 697, 1116, 604, 719, 571, 744, 412, 
        506, 601, 341, 0, 54, 723, 624, 413, 335, 459, 574, 255, 717, 397, 141, 173, 233, 210, 404, 263, 494, 531, 384, 378, 810, 285, 413, 265, 438, 385,   
        525, 620, 284, 54, 0, 742, 643, 445, 354, 473, 593, 201, 736, 418, 87, 205, 179, 229, 423, 282, 513, 563, 403, 410, 829, 317, 432, 284, 457, 333,   
        558, 907, 1029, 723, 742, 0, 691, 547, 452, 606, 561, 943, 784, 377, 829, 739, 921, 513, 534, 565, 235, 442, 541, 618, 609, 613, 310, 462, 744, 813,
        133, 133, 915, 624, 643, 691, 0, 527, 342, 248, 216, 829, 171, 679, 737, 598, 819, 411, 238, 389, 462, 608, 240, 640, 777, 581, 370, 371, 407, 631,
        394, 633, 663, 413, 445, 547, 527, 0, 222, 394, 399, 577, 651, 178, 463, 240, 543, 147, 293, 296, 318, 130, 75, 109, 646, 107, 239, 156, 492, 554,   
        209, 475, 641, 335, 354, 452, 342, 222, 0, 177, 207, 555, 438, 236, 441, 312, 533, 125, 107, 140, 223, 301, 191, 329, 549, 286, 142, 64, 315, 384,  
        83, 349, 865, 574, 593, 561, 216, 399, 207, 0, 198, 664, 341, 379, 572, 433, 654, 246, 126, 224, 377, 444, 75, 472, 703, 416, 296, 207, 399, 466, 
        83, 349, 865, 574, 593, 561, 216, 399, 207, 198, 0, 734, 309, 308, 687, 491, 712, 304, 172, 339, 332, 373, 190, 508, 654, 474, 251, 243, 513, 581,  
        695, 821, 94, 255, 201, 943, 829, 577, 555, 664, 734, 0, 922, 619, 109, 406, 302, 430, 613, 483, 714, 764, 589, 611, 1023, 518, 633, 485, 658, 326, 
        226, 304, 1008, 717, 736, 784, 171, 651, 438, 341, 309, 922, 0, 636, 830, 691, 912, 504, 331, 482, 555, 701, 333, 733, 784, 674, 474, 464, 578, 724,
        410, 676, 705, 397, 418, 377, 679, 178, 236, 379, 308, 619, 636, 0, 505, 369, 597, 189, 305, 320, 135, 79, 307, 261, 499, 242, 61, 172, 495, 564,     
        604, 707, 195, 141, 87, 829, 737, 463, 441, 572, 687, 109, 830, 505, 0, 292, 203, 316, 510, 369, 600, 650, 490, 497, 833, 425, 523, 371, 544, 269,    
        465, 673, 498, 173, 205, 739, 598, 240, 312, 433, 491, 406, 691, 369, 292, 0, 303, 187, 744, 383, 504, 358, 368, 205, 704, 133, 423, 242, 558, 538,   
        686, 799, 388, 233, 179, 921, 819, 543, 533, 654, 712, 302, 912, 597, 203, 303, 0, 408, 557, 461, 692, 661, 589, 508, 1008, 436, 611, 463, 636, 472,
        278, 486, 516, 210, 229, 513, 411, 147, 125, 246, 304, 430, 504, 189, 316, 187, 408, 0, 172, 149, 284, 277, 181, 255, 600, 170, 203, 55, 324, 407,   
        105, 371, 690, 404, 423, 534, 238, 293, 107, 126, 172, 613, 331, 305, 510, 744, 557, 172, 0, 169, 307, 370, 61, 402, 629, 365, 226, 137, 344, 413,   
        255, 338, 569, 263, 282, 565, 389, 296, 140, 224, 339, 483, 482, 320, 369, 383, 461, 149, 169, 0, 340, 385, 149, 455, 656, 319, 259, 161, 175, 244,  
        329, 595, 800, 494, 513, 235, 462, 318, 223, 377, 332, 714, 555, 135, 600, 504, 692, 284, 307, 340, 0, 207, 312, 389, 357, 384, 81, 233, 515, 584,   
        475, 741, 856, 531, 563, 442, 608, 130, 301, 444, 373, 764, 701, 79, 650, 358, 661, 277, 370, 385, 207, 0, 379, 182, 564, 225, 126, 237, 560, 629,   
        107, 373, 675, 384, 403, 541, 240, 75, 191, 75, 190, 589, 333, 307, 490, 368, 589, 181, 61, 149, 312, 379, 0, 407, 634, 351, 231, 142, 324, 391,     
        507, 773, 697, 378, 410, 618, 640, 109, 329, 472, 508, 611, 733, 261, 497, 205, 508, 255, 402, 455, 389, 182, 407, 0, 723, 118, 308, 265, 630, 692,   
        655, 1086, 1116, 810, 829, 609, 777, 646, 549, 703, 654, 1023, 784, 499, 833, 704, 1008, 600, 629, 656, 357, 564, 634, 723, 0, 720, 407, 559, 831, 900,
        448, 656, 604, 285, 317, 613, 581, 107, 286, 416, 474, 518, 674, 242, 425, 133, 436, 170, 365, 319, 384, 225, 351, 118, 720, 0, 303, 222, 494, 574,
        248, 917, 719, 413, 432, 310, 370, 239, 142, 296, 251, 633, 474, 61, 523, 423, 611, 203, 226, 259, 81, 126, 231, 308, 407, 303, 0, 152, 434, 503,
        238, 504, 571, 265, 284, 462, 371, 156, 64, 207, 243, 485, 464, 172, 371, 242, 463, 55, 137, 161, 233, 237, 142, 265, 559, 222, 152, 0, 336, 405,
        430, 274, 744, 438, 457, 744, 407, 492, 315, 399, 513, 658, 578, 495, 544, 558, 636, 324, 344, 175, 515, 560, 324, 630, 831, 494, 434, 336, 0, 419,  
        498, 581, 412, 385, 333, 813, 631, 554, 384, 466, 581, 326, 724, 564, 269, 538, 472, 407, 413, 244, 584, 629, 391, 692, 900, 574, 503, 405, 419, 0,
        };

    for(i = 0; i < 30; i++){
        for(j = 0; j < 30; j++){
            n1->distancia1[i][j] = kilometragem[i][j];
        }
    }
    
}

void init_cidades1(Transito1 *n1){
    int i, j;

    n1->cidades1 = (char **) malloc(30 * sizeof(char *)); //alocando a matriz de char

    for(i = 0; i < 30; i++){
        n1->cidades1[i] = (char *) malloc(100 * sizeof(char)); //alocando cada linha da matriz de char
    }

    char city[30][100] = {
                        "uruacu",
                        "sao miguel do araguaia",
                        "santa rita do araguaia",
                        "santa helena de goias",
                        "rio verde", 
                        "posse", 
                        "porangatu", 
                        "pires do rio",  
                        "pirenopolis",   
                        "pilar de goias",
                        "niquelandia",   
                        "mineiros",      
                        "minacu",        
                        "luziania",      
                        "jatai",         
                        "itumbiara",     
                        "itaja",         
                        "goiania",       
                        "goianesia",     
                        "goias",         
                        "formosa",       
                        "cristalina",    
                        "ceres",         
                        "catalao",       
                        "campos belos" , 
                        "caldas novas",  
                        "brasilia",      
                        "anapolis",      
                        "aruana",        
                        "aragarças"     
    };

    for(i = 0; i < 30; i++){
        for(j = 0; city[i][j] != '\0'; j++){
            n1->cidades1[i][j] = city[i][j];
        }
        n1->cidades1[i][j] = '\0'; 
    }
}

void free_matrizes1(Transito1 *n1){
    int i;

    for(i = 0; i < 30; i++){
        free(n1->cidades1[i]);
        free(n1->distancia1[i]);
    }

    free(n1->cidades1);
    free(n1->distancia1);

}

void print_cidades1(Transito1 n1){
    int i;
    printf("\nAS CIDADES DISPONÍVEIS NO MOMENTO SÃO:\n\n");
    sleep(2);
    for(i = 0; i < 30; i++){
            printf("-%s\n", n1.cidades1[i]);
    }
    printf("\n");
}



int comparar_string1(Transito1 n1, char *str){
    int i;

    while(1){
        for(i = 0; i < 30; i++){
            if(strcmp(n1.cidades1[i], str) == 0){
                return i;
            }
        }
        printf("Cidade nao encontrada, digite novamente por favor: ");
        scanf("%[^\n]%*c", str); // leio a string ate o enter
    }
}


int calc_distancia1(Transito1 n1, int indice_partida, int indice_destino){

    int km;

    km = n1.distancia1[indice_partida][indice_destino];

    return km;
}

void calc_tempo1(int km, int *horas1, int *minutos){
    
    int tempo;   

    tempo = (km * 60)/80;

    *horas1 = tempo / 60;
    *minutos = tempo % 60;
 
}

int calc_combustivel1(int combustivel1, float km, float kml, float *valor, float *litros, float valorcomb){
    float x, litrosr;

    x = combustivel1-km;

    if(x<0){
        printf("\n\nCombustível insuficiente, abasteça no posto mais próximo!!!\n");
        x*=-1;
        *litros = (x/kml);
        *valor = *litros * valorcomb;
        printf("Você precisara de %.2f litros\n", *litros);
        printf("O valor seŕa R$%.2f\n", *valor);
        return 0;
    }
    else{
        printf("\n\nVocê possui combustível suficiente para esse destino\n");
        litrosr = (x/kml);
        printf("Sobrará %.2f litros\n", litrosr);
        return x;
    }

}

int escolhe_combustivel1(Transito1 *n1){
    sleep(2);
    printf("\nCombustíveis disponíveis:\n-gasolina\n-etanol\n-diesel\n");
    
    sleep(1);
    printf("\nDigite o tipo de combustível que você deseja utilizar, em letras minusculas:\n");

    scanf("%[^\n]%*c", n1->tipoComb1); // leio a string ate o enter

    while(1){
        if(strcmp(n1->tipoComb1, "gasolina") == 0) return 1;
        if(strcmp(n1->tipoComb1, "etanol") == 0) return 2;
        if(strcmp(n1->tipoComb1, "diesel") == 0) return 3;
        printf("Combustível indisponivel, digite novamente: ");
        scanf("%[^\n]%*c", n1->tipoComb1); // leio a string ate o enter
    }

}

int main(){
    Transito1 n11;
    int qtd1, i1 = 0, km1 = 0;
    int vetorIndices1[30];
    char str11[100], str21[100];
    float valor1=0, litros1=0;
    int horas1, minutos1, horasf1, minutosf1;
    float kml1, kmf1=0;
    int combustivel1, tipocomb1;
    float valorcomb1, qtdcomb1=0;
    int indice1;
    int x1;
    int numinicial;
    
    Transito n1;
    int qtd = 0, i = 0;
    int *vetorIndices;
    char str[100];
    float valor = 0, litros = 0;

    n1.distancia =  NULL;
    n1.cidades = NULL;
    n1.combustivel = 0;
    n1.dinheiro = 0;  // INICIALIZANDO A STRUCT
    n1.horas = 0;
    n1.minutos = 0;
    n1.horasf = 0;
    n1.minutosf = 0;  // INICIALIZANDO A STRUCT
    n1.km = 0;
    n1.kmf = 0;
    n1.indiceComb = 0;
    n1.combustivelTotal = 0;

    n11.distancia1 =  NULL;
    n11.cidades1 = NULL;
    n11.combustivel1 = 0;
    n11.dinheiro1 = 0;  // INICIALIZANDO A STRUCT
    n11.horas1 = 0;
    n11.minutos1 = 0;

    init_distancia1(&n11); //inicializando a distancia entre as cidades com alocacao de memoria

    init_cidades1(&n11); //inicializando o nome das cidades com alocacao de memoria

    horasf1=0;
    minutos1=0;
    minutosf1=0;
    horas1=0;
    printf("==========================================================ANÁLISE DE VIAGENS==========================================================\n\n");
    printf("Digite 1 se quiser colocar informações precisas do seu carro\nDigite 2 para usar nossas informações aproximadas\n\n");
    scanf("%d", &numinicial);

    if(numinicial == 1){

        introducao1();

        scanf("%d%*c", &qtd1);

        tipocomb1 = escolhe_combustivel1(&n11);

        sleep(1);
        if(tipocomb1 == 1){
        printf("Digite o valor do litro da %s na sua região: ", n11.tipoComb1);
        }
        else{
            printf("Digite o valor do litro do %s na sua região: ", n11.tipoComb1);
        }
        scanf("%f", &valorcomb1);

        printf("\n\nDigite quantos km seu carro faz ainda com o combustivel que possui:");
        scanf("%d%*c", &combustivel1);
        sleep(1);
        printf("Informe quantos km seu carro faz por litro de combustivel:");
        scanf("%f%*c", &kml1);



            sleep(1);
            print_cidades1(n11); //mostro na tela as cidades disponiveis para navegação

            sleep(1);
            printf("\nDigite o nome da cidade que voce deseja inicializar seu trajeto, em letras minusculas:\n");

            scanf("%[^\n]%*c", str11); // leio a string ate o enter

            vetorIndices1[0] = comparar_string1(n11, str11); // coloco o indice da cidade no meu vetor de indices
            n11.indice_cidade_final1[0] = vetorIndices1[0];

            indice1 = vetorIndices1[0];

        while(i1<qtd1){
        
            vetorIndices1[0] = indice1;

            if(i1==0){
                sleep(1);
                printf("\nDigite o nome da cidade que voce deseja ir, em letras minusculas:\n");
            }
            else{
                sleep(1);
                printf("\nDigite o seu próximo destino, em letras minusculas:\n");
            }
            scanf("%[^\n]%*c", str21); // leio a string ate o enter

            vetorIndices1[1] = comparar_string1(n11, str21);
            n11.indice_cidade_final1[i1+1] = vetorIndices1[1];


            km1 = calc_distancia1(n11, vetorIndices1[0], vetorIndices1[1]); //acumula a distancia em km entre as cidades

            kmf1+=km1;

            sleep(3);
            qtdcomb1 = calc_combustivel1(combustivel1, km1, kml1, &valor1, &litros1, valorcomb1);
            combustivel1 = qtdcomb1;
            n11.dinheiro1+=valor1;
            n11.combustivel1+=litros1;

            calc_tempo1(km1, &horas1, &minutos1);
           
            horasf1+=horas1;
            minutosf1+=minutos1;

            if(minutosf1/60 != 0){
                horasf1+=minutosf1/60;
                minutosf1 %= 60;
            }
            else{
                minutosf1 %= 60;
            }

            printf("Você gastará %d horas e %d minutos", horas1, minutos1);

            printf("\nA viagem terá %dkm\n\n", km1);

            sleep(3);
            if(i1<qtd1-1){
                printf("\nVocê está em %s\n\n", str21);
                sleep(1);
                printf("SUA VIAGEM NÃO ACABOU, PROSSIGA!\n\n");
            }

            indice1 = vetorIndices1[1];

            sleep(3);

            i1++;

            if(i1==qtd1){
                printf("\nVIAGEM FINALIZADA\n\n");
            }

        }

        sleep(3);
        printf("==========================================================RESUMO FINAL==========================================================\n\n");
            x1 = n11.indice_cidade_final1[0];
            printf("Sua cidade inicial foi: %s\n", n11.cidades1[x1]);
            printf("Seus destinos foram:");
        for(i1=1;i1<=qtd1;i1++){
            x1 = n11.indice_cidade_final1[i1];
            printf(" %s", n11.cidades1[x1]);
            if(i1<qtd1){
                printf(",");
            }

        }
        sleep(2);
        printf("\nO total de combustível gasto é %.2f litros.\n", n11.combustivel1);
        printf("O total gasto é R$%.2f.\n", n11.dinheiro1);
        printf("O tempo total da viagem é %d horas e %d minutos.\n", horasf1, minutosf1);
        printf("A distância total da viagem será %.0fkm.\n\n", kmf1);
        sleep(1);
        printf("==========================================================RESUMO FINAL==========================================================\n\n\n\n");



            free_matrizes1(&n11); // liberando memoria alocada  

    }  
    else{

        init_distancia(&n1); //inicializando a distancia entre as cidades com alocacao de memoria

        init_cidades(&n1); //inicializando o nome das cidades com alocacao de memoria

        introducao();

        scanf("%d%*c", &qtd);

        if(qtd == 0) return 0;

        vetorIndices = (int *) malloc((qtd + 1) * sizeof(int)); // alocando a memoria necessaria para armazenar os indices das cidades

        sleep(2);

        n1.indiceComb = escolhe_combustivel(&n1);

        sleep(3);

        print_cidades(n1); //mostro na tela as cidades disponiveis para navegação

        sleep(2);

        printf("Digite o nome da cidade que voce deseja inicializar seu trajeto, em letras minusculas:\n");

        scanf("%[^\n]%*c", str); // leio a string ate o enter

        vetorIndices[i] = comparar_string(n1, str);

        sleep(2);

        while(qtd > 0){

            sleep(1);
            printf("\nDigite o nome da cidade que voce deseja ir, em letras minusculas:\n");

            scanf("%[^\n]%*c", str); // leio a string ate o enter

            vetorIndices[i + 1] = comparar_string(n1, str);

            n1.km = calc_distancia(n1, vetorIndices[i], vetorIndices[i + 1]); //retorna a distancia em km entre as cidades

            n1.kmf += n1.km;

            sleep(3);

            calc_combustivel(&n1, &valor, &litros, vetorIndices[i]);

            n1.dinheiro += valor;
            n1.combustivelTotal += litros;

            calc_tempo(n1.km, &n1);

            n1.horasf += n1.horas;
            n1.minutosf += n1.minutos;

            while(1){
                if(n1.minutosf >= 60){
                    n1.horasf++;
                    n1.minutosf -= 60;
                } else{
                    break;
                }
            }

            sleep(2);
            printf("Você gastará %d horas e %d minutos", n1.horas, n1.minutos);

            sleep(2);
            printf("\nA viagem terá %dkm\n\n", n1.km);

            sleep(3);
            printf("VOCÊ ESTÁ EM ");
            printUpper(n1.cidades[vetorIndices[i + 1]]);

            sleep(3);
            if(qtd > 1){
                printf("PROSSIGA SUA VIAGEM\n");
            }

            n1.horas = 0;
            n1.minutos = 0;

            i++;
            qtd--;
        }

        sleep(3);
        printf("==========================================================RESUMO FINAL==========================================================\n\n");
        printf("O total de combustível gasto é %.2f litros.\n", n1.combustivelTotal);
        printf("O gasto total é de R$%.2f.\n", n1.dinheiro);
        printf("O tempo total da viagem é %d horas e %d minutos.\n", n1.horasf, n1.minutosf);
        printf("A distância total da viagem será %dkm.\n\n", n1.kmf);
    
        free_matrizes(&n1); // liberando memoria alocada  

        free(vetorIndices); // liberando memoria alocada 
    }    

    return 0;
}
