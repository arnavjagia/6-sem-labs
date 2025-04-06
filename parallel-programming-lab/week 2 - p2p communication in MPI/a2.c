#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

// Function to calculate factorial
int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    int fact = 1;
    for (int i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

// Function to calculate sum of integers from 1 to n
int sum_of_integers(int n) {
    return (n * (n + 1)) / 2; // Using the formula for sum of first n integers
}

int main(int argc, char *argv[]) {
    int rank, size, N;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Root process reads the value of N
        printf("Enter the value of N: ");
        scanf("%d", &N);

        // Ensure N matches the number of processes
        if (N != size) {
            printf("Error: Number of processes must be equal to N.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    // Broadcast the value of N to all processes
    MPI_Bcast(&N, 1, MPI_INT,
        0, MPI_COMM_WORLD
    );

    // Each process computes its contribution based on its rank
    int local_result = 0;
    if ((rank + 1) % 2 == 1) { // Odd index: factorial
        local_result = factorial(rank + 1);
    } else { // Even index: sum of integers
        local_result = sum_of_integers(rank + 1);
    }

    // Gather results at the root process
    int final_result = 0;
    MPI_Reduce(&local_result, &final_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Root process prints the final result
    if (rank == 0) {
        printf("The result is: %d\n", final_result);
    }

    MPI_Finalize();
    return 0;
}
