#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int factorial(int *n) {
    int f = 1;
    for (int i = 1; i <= *n; i++)
        f *= i;
    return f;
}

int main(int argc, char **argv) {
    int rank, size;
    int *A = NULL, *B = NULL, N, c;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        N = size;
        printf("Enter %d values: ", N);
        fflush(stdout);

        A = malloc(sizeof(int) * N);
        for (int i = 0; i < N; ++i)
            scanf("%d", &A[i]);
    }

    MPI_Scatter(A, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);

    c = factorial(&c);
    B = malloc(sizeof(int) * N);
    MPI_Gather(&c, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Gather(&c, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        int res = 0;
        for (int i = 0; i < N; ++i)
            res += B[i];
        printf("sum of factorials is %d", res);
    }
    MPI_Finalize();

    return 0;
}
