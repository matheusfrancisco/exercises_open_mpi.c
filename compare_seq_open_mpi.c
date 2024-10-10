#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAGICNUMBER 26

int less(int *a, int *b, int init, int end) {
  int num, i;
  num = 0;
  for (i = init; i < end; i++) {
    if (a[i] < b[i]) {
      num++;
    }
  }
  return num;
}

int main(int argc, char **argv) {
  int n, i;
  int init, end;
  int result;
  int *A, *B;

  if (argc < 2) {
    printf("Use: %s <integer number higher than zero>\n", argv[0]);
    exit(1);
  }
  n = atoi(argv[1]);
  if (n <= 0) {
    printf("ERROR! You must specify an integer value > 0!\n");
    exit(1);
  }

  A = (int *)malloc(n * sizeof(int));
  B = (int *)malloc(n * sizeof(int));
  srand(MAGICNUMBER);
  for (i = 0; i < n; i++) {
    A[i] = rand() % 100;
    B[i] = rand() % 100;
  }

  printf("Comparing arrays A and B\n");

  int t_num = 0;
  init = 0;
  end = n;
  result = 0;
#pragma omp parallel reduction(+ : result)
  {
    int process_init = (n / omp_get_num_threads()) * omp_get_thread_num();
    int process_end = omp_get_thread_num() == omp_get_num_threads() - 1
                          ? n
                          : process_init + n / omp_get_num_threads();

    result = less(A, B, init, end);
  }

  printf("A[i] is less than B[i] %d times\n", result);

  return 0;
}
