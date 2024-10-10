#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)
{

    //omp_set_num_threads(2);
    #pragma omp parallel
    {
    	printf("Hello from thread %d !\n", omp_get_thread_num());
    	printf("Bye bye from %d!\n", omp_get_thread_num());
    }

    return 0;
}
