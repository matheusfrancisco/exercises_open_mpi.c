#include <stdio.h>
#include <stdlib.h>

long factorial(int n)
{
    long res;
    int i;
    res = 1;
#pragma omp parallel for reduction(*:res)
    for(i = 2; i <= n; i++){
       res *= i; 
    }
    return res;
}

int main(int argc, char **argv)
{
  int n;
  long result;
  
  if(argc < 2){
    printf("Use: %s <integer number higher than zero>\n", argv[0]);
    exit(1);
  }
  
  n = atoi(argv[1]);
  
  if(n < 0){
    printf("ERROR! You must specify an integer value > 0!\n");
    exit(1);
  }

  printf("Computing factorial(%d)...\n",n);

  result = factorial(n);

  printf("factorial(%d) = %ld\n", n, result);

  return 0;
}
