#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Matrix Addition Kernels
__global__ void matAddRow(int *a, int *b, int *c, int ha, int wa) {
    int row = threadIdx.x;
    if (row < ha) {
        for (int j = 0; j < wa; j++) {
            c[row * wa + j] = a[row * wa + j] + b[row * wa + j];
        }
    }
}

__global__ void matAddCol(int *a, int *b, int *c, int ha, int wa) {
    int col = threadIdx.x;
    if (col < wa) {
        for (int i = 0; i < ha; i++) {
            c[i * wa + col] = a[i * wa + col] + b[i * wa + col];
        }
    }
}

__global__ void matAddElement(int *a, int *b, int *c, int ha, int wa) {
    int col = threadIdx.x;
    int row = threadIdx.y;
    
    if (row < ha && col < wa) {
        c[row * wa + col] = a[row * wa + col] + b[row * wa + col];
    }
}

// Matrix Multiplication Kernels
__global__ void matMulRow(int *a, int *b, int *c, int ha, int wa, int wb) {
    int ridA = threadIdx.x;
    int sum;
    if (ridA < ha) {
        for(int cidB = 0; cidB < wb; cidB++) {
            sum = 0;
            for(int k = 0; k < wa; k++) {
                sum += (a[ridA * wa + k] * b[k * wb + cidB]);
            }
            c[ridA * wb + cidB] = sum;
        }
    }
}

__global__ void matMulCol(int *a, int *b, int *c, int ha, int wa, int wb) {
    int cidB = threadIdx.x;
    if (cidB < wb) {
        int sum;
        for(int ridA = 0; ridA < ha; ridA++) {
            sum = 0;
            for(int k = 0; k < wa; k++) {
                sum += (a[ridA * wa + k] * b[k * wb + cidB]);
            }
            c[ridA * wb + cidB] = sum;
        }
    }
}

__global__ void matMulElement(int *a, int *b, int *c, int ha, int wa, int wb) {
    int ridA = threadIdx.y;
    int cidB = threadIdx.x;
    
    if (ridA < ha && cidB < wb) {
        int sum = 0;
        for(int k = 0; k < wa; k++) {
            sum += (a[ridA * wa + k] * b[k * wb + cidB]);
        }
        c[ridA * wb + cidB] = sum;
    }
}

// Utility Functions
void initializeMatrixManually(int *matrix, int rows, int cols, const char *name) {
    printf("Enter matrix %s (%d x %d):\n", name, rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i * cols + j]);
        }
    }
}

void initializeMatrixRandomly(int *matrix, int rows, int cols) {
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
    int ha, wa, hb, wb, hc, wc;
    int operationChoice, initChoice, kernelChoice;
    
    // Choose operation: Addition or Multiplication
    printf("Select operation:\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("Choice: ");
    scanf("%d", &operationChoice);
    
    // Choose initialization method
    printf("\nSelect initialization method:\n");
    printf("1. Manual input\n");
    printf("2. Random values\n");
    printf("Choice: ");
    scanf("%d", &initChoice);
    
    // Get matrix dimensions based on operation
    if (operationChoice == 1) { // Addition
        printf("\nEnter matrix dimensions (both matrices must be same size):\n");
        printf("Height (rows): ");
        scanf("%d", &ha);
        printf("Width (columns): ");
        scanf("%d", &wa);
        
        hb = ha;
        wb = wa;
        hc = ha;
        wc = wa;
    } else { // Multiplication
        printf("\nEnter dimensions for matrix multiplication:\n");
        printf("Matrix A height (rows): ");
        scanf("%d", &ha);
        printf("Matrix A width / Matrix B height (columns/rows): ");
        scanf("%d", &wa);
        
        hb = wa; // For multiplication, B's height must equal A's width
        printf("Matrix B width (columns): ");
        scanf("%d", &wb);
        
        hc = ha;
        wc = wb;
    }
    
    // Allocate memory for matrices on host
    int size_a = ha * wa * sizeof(int);
    int size_b = hb * wb * sizeof(int);
    int size_c = hc * wc * sizeof(int);

    int *h_a = (int *)malloc(size_a);
    int *h_b = (int *)malloc(size_b);
    int *h_c = (int *)malloc(size_c);
    
    // Initialize matrices
    if (initChoice == 1) { // Manual
        initializeMatrixManually(h_a, ha, wa, "A");
        initializeMatrixManually(h_b, hb, wb, "B");
    } else { // Random
        srand(time(NULL));
        initializeMatrixRandomly(h_a, ha, wa);
        initializeMatrixRandomly(h_b, hb, wb);
    }
    
    // Allocate memory for matrices on device
    int *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, size_a);
    cudaMalloc((void **)&d_b, size_b);
    cudaMalloc((void **)&d_c, size_c);
    
    // Copy matrices A and B from host to device
    cudaMemcpy(d_a, h_a, size_a, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size_b, cudaMemcpyHostToDevice);
    
    // Choose kernel implementation
    printf("\nSelect kernel implementation:\n");
    printf("1. One thread per row\n");
    printf("2. One thread per column\n");
    printf("3. One thread per element\n");
    printf("Choice: ");
    scanf("%d", &kernelChoice);
    
    // Launch the selected kernel based on operation
    if (operationChoice == 1) { // Addition
        switch(kernelChoice) {
            case 1:
                printf("\nUsing one thread per row kernel for addition\n");
                matAddRow<<<1, ha>>>(d_a, d_b, d_c, ha, wa);
                break;
                
            case 2:
                printf("\nUsing one thread per column kernel for addition\n");
                matAddCol<<<1, wa>>>(d_a, d_b, d_c, ha, wa);
                break;
                
            case 3:
                printf("\nUsing one thread per element kernel for addition\n");
                dim3 threadsPerBlock(wa, ha);  // x=columns, y=rows
                matAddElement<<<1, threadsPerBlock>>>(d_a, d_b, d_c, ha, wa);
                break;
        }
    } else { // Multiplication
        switch(kernelChoice) {
            case 1:
                printf("\nUsing one thread per row kernel for multiplication\n");
                matMulRow<<<1, ha>>>(d_a, d_b, d_c, ha, wa, wb);
                break;
                
            case 2:
                printf("\nUsing one thread per column kernel for multiplication\n");
                matMulCol<<<1, wb>>>(d_a, d_b, d_c, ha, wa, wb);
                break;
                
            case 3:
                printf("\nUsing one thread per element kernel for multiplication\n");
                dim3 threadsPerBlock(wb, ha);  // x=columns, y=rows
                matMulElement<<<1, threadsPerBlock>>>(d_a, d_b, d_c, ha, wa, wb);
                break;
        }
    }
    
    // Copy result from device to host
    cudaMemcpy(h_c, d_c, size_c, cudaMemcpyDeviceToHost);
    
    // Print matrices
    printf("\nMatrix A (%d x %d):\n", ha, wa);
    printMatrix(h_a, ha, wa);
    
    printf("\nMatrix B (%d x %d):\n", hb, wb);
    printMatrix(h_b, hb, wb);
    
    printf("\nResult Matrix C (%d x %d):\n", hc, wc);
    printMatrix(h_c, hc, wc);
    
    // Free memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(h_a);
    free(h_b);
    free(h_c);
    
    return 0;
}