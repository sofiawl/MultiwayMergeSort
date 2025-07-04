#include <stdio.h>
#include <stdlib.h>
#include "auxiliar.h"

void imprime_initvetor(int v[], int n){
    printf("vetor: ");
    for (int i = 0; i < n/2; i++)
        printf("%d ", v[i]);

    printf("\n");
}

void trocar(int v[], int i, int j){
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int particionar(int v[], int a, int b){
    int x = v[b];
    int m = a;
    for(int i=a; i<b; i++){
        if(v[i] <= x){
            trocar(v, m, i);
            m++;
        }
    }
    trocar(v, m, b);
    return m;
}

void quickSort(int v[], int a, int b){
    if(a >= b){
        return;
    }
    int m = particionar(v, a, b);
    quickSort(v, a, m-1);
    quickSort(v, m+1, b);
}

int generateInitialRuns(int ram[], int TAM_RAM, FILE *arqEntrada){
    FILE *arq_temp;
    int quantLida = 0;
    int numTemp;
    char nomeArquivo[50];
    int run=0;


    printf("TAM_RAM dentro da função: %d\n", TAM_RAM); 

    while(1){
        quantLida = 0;
        while (quantLida < TAM_RAM && fscanf(arqEntrada, "%d", &numTemp) == 1) {
            ram[quantLida] = numTemp;
            quantLida++;
        }


        if(quantLida == 0 || feof(arqEntrada)){
            break;
        }

        //printf("quantidade de números lidos: %d\n", quantLida);

        printf("Run %d: lendo %d números\n", run, quantLida);
        quickSort(ram, 0, quantLida-1);
        sprintf(nomeArquivo, "run%d.txt", run);
        arq_temp = fopen(nomeArquivo, "w");
        if (!arq_temp) return 1;

        for (int i = 0; i < quantLida; i++) {
            fprintf(arq_temp, "%d\n", ram[i]);
        }

        run++;
        fclose(arq_temp);
    }

    return run;
}

int countLinesInFile(FILE *arq){
    int numTemp;
    int quantLinhas=0;
    while (fscanf(arq, "%d", &numTemp) == 1){
        quantLinhas++;
    }
    rewind(arq);
    return quantLinhas;

}

void intercalar(int runA, int runB, int runC, int TAM_RAM){
    FILE *arqA;
    FILE *arqB;
    FILE *arqC;
    int a, b;
    char nomeArquivoA[50];
    char nomeArquivoB[50];
    char nomeArquivoC[50];
    sprintf(nomeArquivoA, "run%d.txt", runA);
    sprintf(nomeArquivoB, "run%d.txt", runB);
    sprintf(nomeArquivoC, "run%d.txt", runC);
    printf("Intercalando %s com %s e gerando %s\n", nomeArquivoA, nomeArquivoB, nomeArquivoC);
    arqA = fopen(nomeArquivoA, "rt");
    if (!arqA) return;
    arqB = fopen(nomeArquivoB, "rt");
    if (!arqB) return;
    arqC = fopen(nomeArquivoC, "w");
    if (!arqC) return;

    int quantLinhasA = countLinesInFile(arqA);
    int quantLinhasB = countLinesInFile(arqB);
    int quantLinhasC = quantLinhasA + quantLinhasB;
    int k=0;

    int i=0;
    int j=0;

    if (fscanf(arqA, "%d", &a) != 1)
        a = 0;
    if (fscanf(arqB, "%d", &b) != 1)
        b = 0;

    while(k<quantLinhasC){
        if(j>quantLinhasB || (i<quantLinhasA && a<=b)){
            i++;
            fprintf(arqC, "%d\n", a);
            if(fscanf(arqA, "%d", &a) != 1);
        } else{
            j++;
            fprintf(arqC, "%d\n", b);
            if(fscanf(arqB, "%d", &b) != 1);
        }
        k++;
    }

    fclose(arqA);
    fclose(arqB);
    fclose(arqC);
}

int left(int i){
    return i/2;
}

int right(int i){
    return i/2+1;
}

int pai(int i){
    return 2*i;
}

void max_heapify(int v[], int i, int n){
    int r = right(i);
    int l = left(i);
    int maior;
    if(l <= n && (v[l]>v[i])){
        maior = l;
    } else{
        maior = i;
    }
    if(r <= n && (v[r]>v[maior])){
        maior = r;
    }
    if(maior!=i){
        trocar(v, maior, i);
        max_heapify(v, maior, n);
    }
}

void build_max_heapify(int v[], int n){
    for(int i = n; i > n/2; i++)
        max_heapify(v, i, n);

}

void salvarUltimaRunEmSaida(int runsIntermediarias1) {
    char nomeArquivoOrigem[50];
    FILE *arqOrigem, *arqDestino;
    int num;

    sprintf(nomeArquivoOrigem, "run%d.txt", runsIntermediarias1);

    arqOrigem = fopen(nomeArquivoOrigem, "r");
    if (arqOrigem == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nomeArquivoOrigem);
        exit(1);
    }

    arqDestino = fopen("saida.txt", "w");
    if (arqDestino == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo saida.txt\n");
        fclose(arqOrigem);
        exit(1);
    }

    while (fscanf(arqOrigem, "%d", &num) == 1) {
        fprintf(arqDestino, "%d\n", num);
    }

    fclose(arqOrigem);
    fclose(arqDestino);
}