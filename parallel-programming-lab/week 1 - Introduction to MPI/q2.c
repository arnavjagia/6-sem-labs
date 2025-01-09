/*
MPI program display hello for even rank and world for odd rank
*/

#include "mpi.h"
#include <math.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank & 1) {
        printf("World (Rank %d)\n", rank);
    } else {
        printf("Hello (Rank %d)\n", rank);
    }

    MPI_Finalize();

    return 0;
}