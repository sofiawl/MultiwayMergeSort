#include <stdio.h>

size_t RUN_SIZE = 1000;

void trocar(size_t x, size_t y){
    size_t h;
    h = x;
    x = y;
    y = h;

    return;
} 

size_t particionar(size_t *v, size_t a, size_t b){
    size_t x = v[b];
    size_t m = a;

    for(size_t i = a; i < b; i++){
        if (v[i] <= x)
            m++;
    }

    trocar(v[m], v[b]);
    return m;
}

void quicksort(size_t *v, size_t a, size_t b){
    if (a >= b) return;
    size_t m = particionar(v, a, b);
    quicksort(v, a, m-1);
    quicksort(v, m+1, b);
}

size_t main(){
    const char file_name = 'entrada.txt';
    char run_name[20];

    FILE *fp = fopen(file_name, 'r+');
    if (!fp) return 1;

    // LEITURA
    size_t *data = malloc(RUN_SIZE * sizeof(size_t));
    if (!data) return 1;

    fseek(fp, 0, SEEK_END);
    long int file_size = ftell(fp);
    rewind(fp);
    size_t offset = RUN_SIZE;
    size_t count_run = 1;
    while (offset < file_size) {
        fread (data, sizeof(int), 1000, fp);
        fseek(fp, offset, SEEK_CUR);
        offset += RUN_SIZE;

        // ORDENAÇÃO
        quicksort(data, 0, RUN_SIZE-1);


        // GRAVAÇÃO
        sprintf(run_name, "run%d.txt", count_run);
        FILE *run = fopen(run_name, 'w+');
        if (!run) return 1;

        rewind(run);
        fwrite(data, sizeof(int), 1000, run);

        count_run++;
    }

 
    // INTERCALAÇÃO

    free(data);
    fclose(fp);
    return 0;
}