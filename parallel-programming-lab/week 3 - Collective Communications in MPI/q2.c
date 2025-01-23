#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int rank, size;
    int M, N;
    int *ID = NULL, *local_data = NULL;
    double local_sum = 0.0, total_sum = 0.0, total_average = 0.0;
    double *local_averages = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the value of M: ");
        fflush(stdout);
        scanf("%d", &M);
        printf("Enter the ID array elements (total %d elements):\n", M * size);
        fflush(stdout);
        ID = malloc(M * size * sizeof(int));

        for (int i = 0; i < M * size; i++) {
            scanf("%d", &ID[i]);
        }
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    local_data = malloc(M * sizeof(int));
    MPI_Scatter(ID, M, MPI_INT, local_data, M, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < M; i++) {
        local_sum += local_data[i];
    }

    double local_average = local_sum / M;
    local_averages = malloc(size * sizeof(double));
    MPI_Gather(&local_average, 1, MPI_DOUBLE, local_averages, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            total_sum += local_averages[i];
        }
        total_average = total_sum / size;
        printf("Total average: %.2f\n", total_average);
    }

    MPI_Finalize();
    return 0;
}
