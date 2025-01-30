#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    if (n < 2)
        return 1;
    return n * factorial(n - 1);
}

void custom_error_handler(MPI_Comm *comm, int *errcode, ...) {
    char error_string[MPI_MAX_ERROR_STRING];
    int error_length;

    MPI_Error_string(*errcode, error_string, &error_length);

    printf("Custom Error Handler: Error occurred! Error code: %d, Error message: %s\n", *errcode, error_string);
}

int main(int argc, char *argv[]) {
    int rank, size, fact_sum = 0, local_fact;
    int error_code;
    char error_string[MPI_MAX_ERROR_STRING];
    int error_length;
    int error_class;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    local_fact = factorial(rank + 1);

    MPI_Comm invalid_comm = MPI_COMM_NULL;
    error_code = MPI_Scan(&local_fact, &fact_sum, 1, MPI_INT, MPI_SUM, invalid_comm);

    if (error_code != MPI_SUCCESS) {
        MPI_Error_class(error_code, &error_class);
        MPI_Error_string(error_class, error_string, &error_length);

        custom_error_handler(&invalid_comm, &error_code);

        printf("| Error class: %d | Error code: %d | Error message: %s |\n", error_class, error_code, error_string);
    } else {
        if (rank == size - 1) {
            printf("Summation of factorials: %d\n", fact_sum);
        }
    }

    MPI_Finalize();
    return 0;
}
