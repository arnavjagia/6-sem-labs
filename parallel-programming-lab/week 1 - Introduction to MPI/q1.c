/*
MPI program find pow(x, rank) for all processes
where,
    x       -> integer constant
    rank    -> rank of processes
*/

#include "mpi.h"
#include <math.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int x;
    x = 2;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Process rank : %d \t Answer : %.0f \n", rank, pow(x, rank));
    MPI_Finalize();

    return 0;
}