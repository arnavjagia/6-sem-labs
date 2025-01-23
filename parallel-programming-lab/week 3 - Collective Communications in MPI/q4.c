#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int rank, size;
    int len, local_len;
    char *S1 = NULL, *S2 = NULL, *local_S1 = NULL, *local_S2 = NULL, *resultant_str = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter first string (S1): ");
        scanf("%ms", &S1);
        printf("Enter second string (S2): ");
        scanf("%ms", &S2);

        len = strlen(S1);
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    local_len = len / size;

    local_S1 = malloc((local_len + 1) * sizeof(char));
    local_S2 = malloc((local_len + 1) * sizeof(char));

    MPI_Scatter(S1, local_len, MPI_CHAR, local_S1, local_len, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(S2, local_len, MPI_CHAR, local_S2, local_len, MPI_CHAR, 0, MPI_COMM_WORLD);

    char *local_result = malloc((local_len * 2 + 1) * sizeof(char));

    for (int i = 0; i < local_len; i++) {
        local_result[2 * i] = local_S1[i];
        local_result[2 * i + 1] = local_S2[i];
    }
    local_result[2 * local_len] = '\0';

    if (rank == 0) {
        resultant_str = malloc((len + 1) * sizeof(char));
    }

    MPI_Gather(local_result, local_len * 2, MPI_CHAR, resultant_str, local_len * 2, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resultant string: %s\n", resultant_str);
    }

    MPI_Finalize();
    return 0;
}
