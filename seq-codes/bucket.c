#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE  200
#define N_BUCKETS   2

typedef struct {
    int head;
    int elements[ARRAY_SIZE];
} bucket;

void bubble_sort(int *v, int size){
    int i, j, temp, changed;

    for(j = 0; j < size - 1; j++){
        changed = 0;
        for(i = 0; i < size - 1; i++){
            if(v[i + 1] < v[i]){
                temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                changed = 1;
            }
        }
        if(!changed) break;
    }
}

void bucket_sort(int *v, int size, int n_buckets){
    int i, j, k;
    bucket buckets[n_buckets];
    int max_numbers_bucket = size / n_buckets;
    
    for(i = 0; i < n_buckets; i++)
        buckets[i].head = 0;

    for(i = 0; i < size; i++) {
        for (j = 0; j < n_buckets; j++) {
            if(v[i] < (j+1) * max_numbers_bucket) {
                buckets[j].elements[buckets[j].head] = v[i];
                (buckets[j].head)++;
                break;
            }
        }
    }

    for(i = 0; i < n_buckets; i++)
        if(buckets[i].head > 1) 
            bubble_sort(buckets[i].elements, buckets[i].head);

    k = 0;
    for(i = 0; i < n_buckets; i++) {
        for(j = 0; j < buckets[i].head; j++) {
            v[k] = buckets[i].elements[j];
            k++;
        }
    }
}

void print_array(int *v, int size) {
    int i;
    for(i = 0; i < size; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int main(int argc, char **argv) {
    int vet[ARRAY_SIZE];
    int i;

    srand(time(NULL));
    
    for(i=0; i < ARRAY_SIZE; i++)
        vet[i] = rand() % ARRAY_SIZE;

    print_array(vet, ARRAY_SIZE);

    bucket_sort(vet, ARRAY_SIZE, N_BUCKETS);

    print_array(vet, ARRAY_SIZE);

    return 0;
}