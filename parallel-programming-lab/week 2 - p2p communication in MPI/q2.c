#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            int data = 69420;
            MPI_Send(
                &data,         // data
                1,             // count
                MPI_INT,       // datatype
                i,             // destination
                0,             // tag
                MPI_COMM_WORLD // communicator
            );
        }
    } else {
        int number;

        MPI_Recv(
            &number,          // data
            1,                // count
            MPI_INT,          // datatype
            0,                // source, MPI_ANY_SOURCE also available
            MPI_ANY_TAG,      // tag, can also give an integer
            MPI_COMM_WORLD,   // communicator
            MPI_STATUS_IGNORE // status, alternatively declare `MPI_Status status` and pass `&status`
        );

        printf("Process %d: %d\n", rank, number);
    }

    MPI_Finalize();
    return 0;
}