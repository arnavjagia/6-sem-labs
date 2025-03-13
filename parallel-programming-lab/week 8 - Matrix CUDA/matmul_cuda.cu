#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void matMulRow(int *a, int *b, int *c, int wa, int wb) {
    int ridA = threadIdx.x;
    int sum;
    for(int cidB = 0; cidB < wb; cidB++) {
        sum = 0;
        for(int k = 0; k < wa; k++) {
            sum += (a[ridA * wa + k] * b[k * wb + cidB]);
        }
        c[ridA * wb + cidB] = sum;
    }
}

__global__ void matMulCol(int *a, int *b, int *c, int ha, int wa) {
    int cidB = threadIdx.x;
    int wb = blockDim.x;
    int sum, k;
    for(int ridA = 0; ridA < ha; ridA++) {
        sum = 0;
        for(k = 0; k < wa; k++) {
            sum += (a[ridA * wa + k] * b[k * wb + cidB]);
        }
        c[ridA * wb + cidB] = sum;
    }
}

__global__ void matMulElement(int *a, int *b, int *c, int wa) {
    int ridA = threadIdx.y;
    int cidB = threadIdx.x; 
    int wb = blockDim.x;
    int sum = 0, k;
    for(k = 0; k < wa; k++) {
        sum += (a[ridA * wa + k] * b[k * wb + cidB]);
    }
    c[ridA * wb + cidB] = sum;
}

void initializeMatrix(int *matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            matrix[i * cols + j] = rand() % 10;
        }
    }
}

void printMatrix(int *matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

int main() {
    // Matrix dimensions
    int m, n, p;  // m x n * n x p = m x p
    
    printf("Enter dimensions for matrix multiplication:\n");
    printf("Matrix A rows (m): ");
    scanf("%d", &m);
    printf("Matrix A columns / Matrix B rows (n): ");
    scanf("%d", &n);
    printf("Matrix B columns (p): ");
    scanf("%d", &p);

    // Allocate memory for matrices on host
    int size_a = m * n * sizeof(int);
    int size_b = n * p * sizeof(int);
    int size_c = m * p * sizeof(int);

    int *h_a = (int *)malloc(size_a);
    int *h_b = (int *)malloc(size_b);
    int *h_c = (int *)malloc(size_c);

    // Initialize matrices A and B with random values
    srand(time(NULL));
    initializeMatrix(h_a, m, n);
    initializeMatrix(h_b, n, p);

    // Allocate memory for matrices on device
    int *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, size_a);
    cudaMalloc((void **)&d_b, size_b);
    cudaMalloc((void **)&d_c, size_c);

    // Copy matrices A and B from host to device
    cudaMemcpy(d_a, h_a, size_a, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size_b, cudaMemcpyHostToDevice);

    // Menu for kernel selection
    int choice;
    printf("\nSelect kernel to use:\n");
    printf("1. One thread per row\n");
    printf("2. One thread per column\n");
    printf("3. One thread per element\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("\nUsing one thread per row kernel\n");
            matMulRow<<<1, m>>>(d_a, d_b, d_c, n, p);
            break;
            
        case 2:
            printf("\nUsing one thread per column kernel\n");
            matMulCol<<<1, p>>>(d_a, d_b, d_c, m, n);
            break;
            
        case 3:
            printf("\nUsing one thread per element kernel\n");
            dim3 threadsPerBlock(p, m);  // x=columns, y=rows
            matMulElement<<<1, threadsPerBlock>>>(d_a, d_b, d_c, n);
            break;
    }
    

    cudaMemcpy(h_c, d_c, size_c, cudaMemcpyDeviceToHost);

    printf("\nMatrix A (%d x %d):\n", m, n);
    printMatrix(h_a, m, n);
    
    printf("\nMatrix B (%d x %d):\n", n, p);
    printMatrix(h_b, n, p);
    
    printf("\nResult Matrix C (%d x %d):\n", m, p);
    printMatrix(h_c, m, p);

    // Free memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(h_a);
    free(h_b);
    free(h_c);

    return 0;
}