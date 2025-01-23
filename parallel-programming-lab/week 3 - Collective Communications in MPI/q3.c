#include "mpi.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_non_vowel(char c) {
    char lower = tolower(c);
    return (lower >= 'a' && lower <= 'z' && lower != 'a' && lower != 'e' && lower != 'i' && lower != 'o' && lower != 'u');
}

int main(int argc, char **argv) {
    int rank, size;
    int len, local_len, local_non_vowels = 0;
    char *str = NULL, *local_str = NULL;
    int *all_non_vowels = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the string: ");
        fflush(stdout);
        scanf("%ms", &str);

        len = strlen(str);

        if (len % size != 0) {
            printf("Error: The length of the string must be divisible by the number of processes.\n");
            MPI_Finalize();
            return 1;
        }
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    local_len = len / size;

    local_str = malloc((local_len + 1) * sizeof(char));

    MPI_Scatter(str, local_len, MPI_CHAR, local_str, local_len, MPI_CHAR, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_len; i++) {
        if (is_non_vowel(local_str[i])) {
            local_non_vowels++;
        }
    }

    all_non_vowels = malloc(size * sizeof(int));
    MPI_Gather(&local_non_vowels, 1, MPI_INT, all_non_vowels, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        int total_non_vowels = 0;

        for (int i = 0; i < size; i++) {
            printf("Non-vowels found by process %d: %d\n", i, all_non_vowels[i]);
            total_non_vowels += all_non_vowels[i];
        }

        printf("Total number of non-vowels: %d\n", total_non_vowels);

        free(str);
    }

    free(local_str);
    free(all_non_vowels);

    MPI_Finalize();
    return 0;
}
