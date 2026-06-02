#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

int main() {
    std::cout << "DIM,T_SERIE_MS\n";
    for (int exp = 1; exp <= 8; ++exp) {
        size_t N = pow(10, exp);
        std::vector<float> A(N, 1.0f), B(N, 2.0f), C(N, 0.0f);

        auto start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < N; ++i) {
            C[i] = A[i] + B[i];
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << N << "," << duration.count() << "\n";
    }
    return 0;
}
