#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  int array_size;
  int i;
  unsigned long int prod = 0.0;

  if(argc<2){
    printf("Use: %s <array size>\n", argv[0]);
    exit(1);
  }
  
  /* Size of arrays */
  array_size = atoi(argv[1]);
  
  /* Allocate array A */
  unsigned long int *a = (unsigned long int *) malloc(sizeof(unsigned long int) * array_size);

  /* Allocate array B */
  unsigned long int *b = (unsigned long int *) malloc(sizeof(unsigned long int) * array_size);

  printf("Initializing arrays A and B...\n");

  /* Initialization */
  for (i=0; i<array_size; i++)
    a[i] = i;

  for (i=0; i<array_size; i++)
    b[i] = i;
  
  printf("Computing...\n");

  /* Compute the scalar product */
  #pragma omp parallel for shared(a, b) reduction(+:prod)
  for (i=0; i<array_size; i++)
    prod += a[i] * b[i];

  printf("Finished!\n");

  /*** Print result ***/
  printf("******************************************************\n");
  printf("Scalar product: %lu\n", prod);
  printf("******************************************************\n");

  prod = 0.0;
  for (i=0; i<array_size; i++)
    prod += a[i] * b[i];

  printf("Finished!\n");

  /*** Print result ***/
  printf("******************************************************\n");
  printf("Scalar product: %lu\n", prod);
  printf("******************************************************\n");


  free(a);
  free(b);
}
