## Exercises using OPEN_MPI

This is just simple code to understand tha abstraction of
open mpi. OPEN_MPI is a library that allows you to create
parallel programs using the message passing interface (MPI).

## How to compile


gcc prod_seq_open_mpi.c -o out -fopenmp ; ./out <number_of_threads>

gcc -o out compare_seq_open_mpi.c -fopenmp ; ./out <number_of_threads>
