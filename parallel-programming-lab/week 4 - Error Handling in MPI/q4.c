#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

char *read_string();

int main() {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char *string = NULL;
    if (rank == 0) {
        printf("Enter a string of length %d: ", size);
        string = read_string();

        if (strlen(string) != size) {
            printf("Invalid length!");
            MPI_Abort(MPI_COMM_WORLD, 0);
        }
    }

    char local_char;
    MPI_Scatter(string, 1, MPI_CHAR, &local_char, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    char *local_result = malloc((rank + 2) * sizeof(char));
    for (int i = 0; i <= rank; i++) {
        local_result[i] = local_char;
    }
    local_result[rank + 1] = '\0';
    printf("Process %d, local result: %s\n", rank, local_result);

    if (rank == 0) {
        char *global_result, len;

        len = (size) * (size + 1) / 2 + 1;
        global_result = malloc(len * sizeof(char));

        for (int i = 1; i < size; i++) {
            int offset = i * (i + 1) / 2;
            MPI_Recv(global_result + offset, i + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        global_result[0] = local_char;
        global_result[len - 1] = '\0';
        printf("Process 0, global result: %s\n", global_result);

    } else {
        MPI_Send(local_result, rank + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}


char *read_string() {
    char buffer[1024];
    
    fflush(stdin);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strlen(buffer) - 1] = '\0';

    return strdup(buffer);
}