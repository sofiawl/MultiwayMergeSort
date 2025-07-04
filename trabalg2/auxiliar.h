#ifndef AUXILIAR_H
#define AUXILIAR_H

    #include <stdio.h>
    #include <stdlib.h>

    void trocar(int v[], int i, int j);
    int particionar(int v[], int a, int b);
    void quickSort(int v[], int a, int b);
    int generateInitialRuns(int ram[], int TAM_RAM, FILE *arqEntrada);
    void intercalar(int runA, int runB, int runC, int TAM_RAM);
    void salvarUltimaRunEmSaida(int runsIntermediarias1);
#endif  /*AUXILIAR_H*/