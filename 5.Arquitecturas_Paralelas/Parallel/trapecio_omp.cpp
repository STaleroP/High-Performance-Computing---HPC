#include <iostream>
#include <cmath>
#include <chrono>
#include <omp.h>

// Función a integrar
double f(double x) {
    return x - pow(x, 3)/6 + pow(x, 5)/120;
}

// Solución analítica
double integral_analitica(double x) {
    return pow(x, 2)/2 - pow(x, 4)/24 + pow(x, 6)/720;
}

// Método del trapecio paralelizado
double metodo_trapecio_omp(double a, double b, int n) {
    double h = (b - a)/n;
    double suma = (f(a) + f(b))/2.0;
    #pragma omp parallel for reduction(+:suma)
    for (int i = 1; i < n; ++i) {
        suma += f(a + i*h);
    }
    return h * suma;
}

int main() {
    const double a = 0.0, b = 4.0;
    const int n = 10000000;

    // Configuración de hilos
    omp_set_num_threads(omp_get_max_threads());

    // Medición de tiempo
    auto start = std::chrono::high_resolution_clock::now();
    double resultado_numerico = metodo_trapecio_omp(a, b, n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempo = end - start;

    // Solución analítica
    double resultado_analitico = integral_analitica(b) - integral_analitica(a);
    double error = fabs((resultado_analitico - resultado_numerico) / resultado_analitico) * 100.0;

    // Resultados
    std::cout << "=== MÉTODO DEL TRAPECIO (OPENMP) ===\n";
    std::cout << "Resultado numérico: " << resultado_numerico << "\n";
    std::cout << "Resultado analítico: " << resultado_analitico << "\n";
    std::cout << "Error relativo: " << error << " %\n";
    std::cout << "Tiempo de ejecución: " << tiempo.count() << " segundos\n";
    std::cout << "Hilos utilizados: " << omp_get_max_threads() << "\n";

    return 0;
}
