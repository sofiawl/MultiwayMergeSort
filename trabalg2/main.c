#include <stdio.h>
#include <stdlib.h>
#include "auxiliar.h"
#define TAM_RAM 100000


int main(){
    int ram[TAM_RAM];
    int runsIniciais = 0;

    FILE *arqInp;
    FILE *arqOut;
    
    arqInp = fopen("entrada.txt", "rt");
    arqOut = fopen("saida.txt", "w");

    if (arqInp == NULL) {
        fprintf(stderr, "erro");
        return 1;
    }
    
    if (arqOut == NULL) {
        fprintf(stderr, "erro");
        return 1;
    }

    runsIniciais = generateInitialRuns(ram, TAM_RAM, arqInp);
    
    int runsIntermediarias = runsIniciais;
    if(runsIniciais%2 == 1){
        runsIniciais--;
    }
    
    int i = 0;
    while(i<runsIniciais){
        int j = i+1;
        intercalar(i, j, runsIntermediarias, TAM_RAM);
        i = i+2;
        runsIntermediarias++;
    }

    if(runsIniciais%2 == 1){
        i=runsIniciais;
    }
    
    if(runsIntermediarias%2 == 1){
        runsIntermediarias--;
    }

    int runsFinais = runsIntermediarias;
    printf("runsFinais: %d\n", runsFinais);
    while(i<runsFinais-1){
        int j = i+1;
        intercalar(i, j, runsFinais, TAM_RAM);
        i = i+2;
        runsFinais++;
    }

    salvarUltimaRunEmSaida(i);

    fclose(arqInp);
    fclose(arqOut);

    return 0;
}

