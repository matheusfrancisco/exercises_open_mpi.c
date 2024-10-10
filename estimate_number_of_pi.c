
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int rank, size;
    long long int i, count = 0, total_count = 0;
    long long int total_darts = 1000000; // Default number of darts
    long long int darts_per_process;
    double x, y, pi_estimate;
    unsigned int seed;

    MPI_Init(&argc, &argv);                    // Initialize the MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);      // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);      // Get the number of processes

    if (argc > 1) {
        total_darts = atoll(argv[1]);          // Total number of darts from command line
    }

    darts_per_process = total_darts / size;    // Darts per process
    if (rank == size - 1) {
        darts_per_process += total_darts % size; // Handle any remainder
    }

    seed = (unsigned int)(time(NULL) + rank);  // Unique seed for each process

    // Simulate dart throwing
    for (i = 0; i < darts_per_process; i++) {
        x = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0; // Random x in [-1, 1]
        y = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0; // Random y in [-1, 1]
        if (x * x + y * y <= 1.0) {
            count++; // Dart is inside the circle
        }
    }

    // Reduce counts from all processes to total_count in the root process
    MPI_Reduce(&count, &total_count, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi_estimate = 4.0 * (double)total_count / (double)total_darts;
        printf("Estimated Pi = %.16f\n", pi_estimate);
    }

    MPI_Finalize(); // Finalize the MPI environment
    return 0;
}
