#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// Function to reverse digits of a number
int reverseDigits(int num) {
    int reversed = 0;
    while (num != 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int inputArray[9] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    int outputArray[9];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Ensure exactly 9 processes are used
    if (size != 9) {
        if (rank == 0) {
            printf("This program requires exactly 9 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    // Each process reverses one element of the array
    int localResult = reverseDigits(inputArray[rank]);
    printf("Rank %d localResult: %d\n", rank, localResult);

    // Gather the results back to process 0
    MPI_Gather(&localResult, 1, MPI_INT, outputArray, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Process 0 prints the final reversed array
    if (rank == 0) {
        printf("Reversed Array: ");
        for (int i = 0; i < 9; i++) {
            printf("%d ", outputArray[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
