#include <iostream>
#include <cuda_runtime.h>
#include <cmath>
#include <chrono>

__global__ void sumaCUDA(float *A, float *B, float *C, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) C[i] = A[i] + B[i];
}

void inicializar(float *v, float valor, int N) {
    for (int i = 0; i < N; ++i) {
        v[i] = valor;
    }
}

int main() {
    std::cout << "DIM,T_CUDA_MS\n";
    for (int exp = 1; exp <= 8; ++exp) {
        int N = pow(10, exp);
        size_t size = N * sizeof(float);

        float *h_A = (float *)malloc(size);
        float *h_B = (float *)malloc(size);
        float *h_C = (float *)malloc(size);

        if (!h_A || !h_B || !h_C) {
            std::cerr << "Error al asignar memoria en CPU para N = " << N << std::endl;
            continue;
        }

        inicializar(h_A, 1.0f, N);
        inicializar(h_B, 2.0f, N);

        float *d_A, *d_B, *d_C;
        cudaMalloc(&d_A, size);
        cudaMalloc(&d_B, size);
        cudaMalloc(&d_C, size);

        cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
        cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

        int threadsPerBlock = 256;
        int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

        cudaDeviceSynchronize();
        auto start = std::chrono::high_resolution_clock::now();

        sumaCUDA<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

        cudaDeviceSynchronize();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << N << "," << duration.count() << "\n";

        cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

        cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
        free(h_A); free(h_B); free(h_C);
    }
    return 0;
}
