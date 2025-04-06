#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0) {
            printf("This program requires exactly 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    int start, end;
    if (rank == 0) {
        // Process 0 handles the range 1 to 50
        start = 1;
        end = 50;
    } else {
        // Process 1 handles the range 51 to 100
        start = 51;
        end = 100;
    }

    // Find primes in the assigned range
    int primes[50], count = 0;
    for (int i = start; i <= end; i++) {
        if (isPrime(i)) {
            primes[count++] = i;
        }
    }

    // Gather results at process 0
    int totalPrimes[100], totalCount = 0;
    MPI_Gather(primes, count, MPI_INT, totalPrimes, count, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Prime numbers between 1 and 100: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", primes[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
