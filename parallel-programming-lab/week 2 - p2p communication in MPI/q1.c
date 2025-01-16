#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank;
    char string[] = "Hello World";

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        // send to process 1
        MPI_Ssend(string, strlen(string) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

        // recieve from process 1
        MPI_Recv(string, strlen(string) + 1, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Barrier(MPI_COMM_WORLD);
        fprintf(stdout, "Rank %d: %s\n", rank, string);
    } else if (rank == 1) {
        // recieve from process 0
        char recieved[strlen(string)];
        MPI_Recv(recieved, strlen(string) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // toggle case
        for (int i = 0; i < strlen(recieved); ++i)
            if ((recieved[i] >= 'a' && recieved[i] <= 'z') || (recieved[i] >= 'A' && recieved[i] <= 'Z'))
                recieved[i] = recieved[i] ^ 32;

        // send back to process 0
        MPI_Ssend(recieved, strlen(recieved) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        fprintf(stdout, "Rank %d: %s\n", rank, recieved);
    }

    MPI_Finalize();
    return 0;
}