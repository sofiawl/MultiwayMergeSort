#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

size_t RUN_SIZE = 1000;

void trocar(size_t *v, size_t i, size_t j){
    size_t h;
    h = v[i];
    v[i] = v[j];
    v[j] = h;

    return;
} 

void min_heapfy(size_t *h, size_t i, size_t n){
    size_t left = i * 2 + 1;
    size_t right = i * 2 + 2;
    size_t min_idx;

    if ((left <= n) && (h[left] < h[i]))
        min_idx = left;
    else 
        min_idx = i;
    if ((right <= n) && (h[right] < h[min_idx]))
        min_idx = right;

    if (min_idx != i){
        trocar(h, i, min_idx);
        min_heapfy(h, min_idx, n);
    }
    return;
}

void contruir(size_t *h, size_t n){
    for(size_t i = n/2; i > 0; i--){
        min_heapfy(h, i, n);
    }

    return;
}

void heap_sort(size_t *h, size_t n){
    construir(h, n);

    size_t i = n;
    while(i > 1){
        trocar(h, 1, n);
        n--;
        min_heapfy(h, 1, n);
        i--;
    }

    return;
}

void copiar(size_t *final, size_t *init, size_t a, size_t b){
    
    for (size_t i = a; i <= b; i++)
        final[i] = init[i]; 

    return;
}

size_t *merge(size_t *v, size_t *w, size_t size_v, size_t size_w){
    size_t n = size_v + size_w;
    size_t *u = malloc (sizeof(size_t) * (n));
    if (!u) return 1;

    size_t set = 0;
    size_t i = size_v - 1, j = size_w - 1, k = 0;
    size_t aux;
    while(k < n){
        if (j < 0 || (i >= size_v && v[i] <= w[j])){
            aux = i;
            i--;
            set = 1;
        } else {
            aux = j;
            j--;
            set = 0;
        }

        if (set)
            u[k] = v[aux];
        else 
            u[k] = w[aux];

        k++;
    }

    return u;
}

void print_vet(size_t *vet, size_t vet_size){

    for (size_t i = 0; i < vet_size; i++){
        printf("%zu ", vet[i]);
    }
    printf("/n");
    return;
}

int main(){
    const char *file_name = "entrada.txt";
    char run_name[20];

    FILE *fp = fopen(file_name, 'r+');
    if (!fp) return 1;

    // LEITURA
    size_t *data = malloc(RUN_SIZE * sizeof(size_t));
    if (!data) return 1;

    fseek(fp, 0, SEEK_END);
    long int file_size = ftell(fp);
    rewind(fp);

    size_t total_runs = file_size / sizeof(size_t);
    size_t count_run = 1;

    // corrigir o loop
    while (!feof(fp) && count_run * RUN_SIZE < file_size) {
        size_t read_size = fread (data, sizeof(size_t), RUN_SIZE, fp);

        print_vet(data, RUN_SIZE);
        // ORDENAÇÃO
        heap_sort(data, RUN_SIZE);    

        printf(data, RUN_SIZE);

        // GRAVAÇÃO
        sprintf(run_name, "run%zu.txt", count_run);
        FILE *run = fopen(run_name, 'w+');
        if (!run) return 1;
        fwrite(data, sizeof(size_t), read_size, run);

        fclose(run);
        count_run++;
    }

    // INTERCALAÇÃO
    // abre arquivo run que terá todos dados no final
    FILE *out = fopen("saida.txt", 'r+');
    if (!out) return 1;
    rewind(out);

    size_t *buffer = NULL;
    if (!buffer) return 1;
    size_t buffer_size = 0;

    for (size_t i = 1; i <= count_run; i++) {
        sprintf(run_name, "run%zu.txt", i);
        FILE *run_fp = fopen(run_name, "rb");
        if (!run_fp) return 1;

        size_t *chunk = malloc(RUN_SIZE * sizeof(size_t));
        size_t read_size = fread(chunk, sizeof(size_t), RUN_SIZE, run_fp);
        fclose(run_fp);

        if (!buffer) {
            buffer = chunk;
            buffer_size = read_size;
        } else {
            size_t *merged = merge(buffer, chunk, buffer_size, read_size);
            free(buffer);
            free(chunk);
            buffer = merged;
            buffer_size += read_size;
        }
    }

    fclose(out);
    free(data);
    fclose(fp);
    return 0;
}