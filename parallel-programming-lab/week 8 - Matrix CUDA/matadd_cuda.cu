#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void matAddRow(int *a, int *b, int *c, int m, int n) {
    int row = threadIdx.x;
    if (row < m) {
        for (int j = 0; j < n; j++) {
            c[row * n + j] = a[row * n + j] + b[row * n + j];
        }
    }
}

__global__ void matAddCol(int *a, int *b, int *c, int m, int n) {
    int col = threadIdx.x;
    if (col < n) {
        for (int i = 0; i < m; i++) {
            c[i * n + col] = a[i * n + col] + b[i * n + col];
        }
    }
}

__global__ void matAddElement(int *a, int *b, int *c, int m, int n) {
    int col = threadIdx.x;
    int row = threadIdx.y;
    
    if (row < m && col < n) {
        c[row * n + col] = a[row * n + col] + b[row * n + col];
    }
}

int main() {
    int m, n;
    printf("Enter m and n: ");
    scanf("%d %d", &m, &n);

    // Host memory allocation
    int *h_a = (int *)malloc(m * n * sizeof(int));
    int *h_b = (int *)malloc(m * n * sizeof(int));
    int *h_c = (int *)malloc(m * n * sizeof(int));

    printf("Enter mat a: ");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &h_a[i * n + j]);
        }
    }

    printf("Enter mat b: ");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &h_b[i * n + j]);
        }
    }

    // Device memory allocation
    int *d_a, *d_b, *d_c;
    cudaMalloc(&d_a, m * n * sizeof(int));
    cudaMalloc(&d_b, m * n * sizeof(int));
    cudaMalloc(&d_c, m * n * sizeof(int));

    // input from host to device
    cudaMemcpy(d_a, h_a, m * n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, m * n * sizeof(int), cudaMemcpyHostToDevice);

    int choice;
    printf("\nSelect kernel to use:\n");
    printf("1. One thread per row\n");
    printf("2. One thread per column\n");
    printf("3. One thread per element\n");
    printf("Choice: ");
    scanf("%d", &choice);

    // Launch the selected kernel
    switch(choice) {
        case 1:
            // a. Launch kernel - one thread per row
            matAddRow<<<1, m>>>(d_a, d_b, d_c, m, n);
            break;
            
        case 2:
            // b. Launch kernel - one thread per column
            matAddCol<<<1, n>>>(d_a, d_b, d_c, m, n);
            break;
            
        case 3:
            // c. Launch kernel - one thread per element
            dim3 threadsPerBlock(n, m);  // x=columns, y=rows
            matAddElement<<<1, threadsPerBlock>>>(d_a, d_b, d_c, m, n);
            break;
    }

    // result from device to host
    cudaMemcpy(h_c, d_c, m * n * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    printf("\nResultant Matrix:\n");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", h_c[i * n + j]);
        }
        printf("\n");
    }

    free(h_a);
    free(h_b);
    free(h_c);

    return 0;
}