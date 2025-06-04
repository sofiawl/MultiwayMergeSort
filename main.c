#include <stdio.h>
#include <stdlib.h>

size_t RUN_SIZE = 1000;

void trocar(size_t *v, size_t i, size_t j){
    size_t h;
    h = v[i];
    v[i] = v[j];
    v[j] = h;

    return;
} 

void min_heapfy(size_t *h, size_t i, size_t n){
    size_t left = i * 2 ;
    size_t right = i * 2 + 1;
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
void merge(size_t *v, size_t a, size_t m, size_t b){
    if (a >= b)
        return;

    size_t n = b - a + 1;
    size_t u[n];
    size_t i = b, j = m, k = 0;
    size_t aux;
    while(k < n){
        if (j < a || (i >= m && v[i] <= v[j])){
            aux = i;
            i--;
        } else {
            aux = j;
            j--;
        }

        u[k++] = v[aux];
    }

    copiar(u, v, a, b);
    return;
}

int main(){
    const char file_name = "entrada.txt";
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
    // corrigir o loop
    while (offset < file_size) {
        fread (data, sizeof(size_t), 1000, fp);
        fseek(fp, offset, SEEK_CUR);
        offset += RUN_SIZE;

        // ORDENAÇÃO
        heap_sort(data, RUN_SIZE);    

        // GRAVAÇÃO
        sprintf(run_name, "run%d.txt", count_run);
        FILE *run = fopen(run_name, 'w+');
        if (!run) return 1;

        rewind(run);
        fwrite(data, sizeof(size_t), 1000, run);

        count_run++;
    }

    // INTERCALAÇÃO
    for (size_t i = 1; i <= count_run; i++) {


    }

    free(data);
    fclose(fp);
    return 0;
}