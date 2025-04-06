#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1)
        return 0;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *array = NULL; // Array to hold numbers
    int localNumber;   // Number assigned to each process
    int isPrimeResult; // Result of prime check for each process

    if (rank == 0) {
        // Master process reads the array
        printf("Enter %d elements of the array:\n", size);
        array = (int *)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) {
            scanf("%d", &array[i]);
        }
    }

    // Scatter the array elements to all processes
    MPI_Scatter(
        array, 1, MPI_INT,
        &localNumber, 1, MPI_INT,
        0, MPI_COMM_WORLD
    );

    // Each process checks if its assigned number is prime
    isPrimeResult = isPrime(localNumber);

    // Gather results back at the master process
    int *results = NULL;
    if (rank == 0) {
        results = (int *)malloc(size * sizeof(int));
    }
    MPI_Gather(&isPrimeResult, 1, MPI_INT,
        results, 1, MPI_INT,
        0, MPI_COMM_WORLD
    );

    // Master process prints the results
    if (rank == 0) {
        printf("Prime check results:\n");
        for (int i = 0; i < size; i++) {
            printf("Number %d is %s\n", array[i], results[i] ? "Prime" : "Not Prime");
        }
        free(array);
        free(results);
    }

    MPI_Finalize();
    return 0;
}
