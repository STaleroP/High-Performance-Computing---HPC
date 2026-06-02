#include "poisson.h"
#include "report.hpp"

// Resuelve la ecuación de Poisson iterativamente hasta convergencia
void solve_poisson(std::vector<std::vector<double>> &T,
                   const std::vector<std::vector<double>> &source,
                   int M, int N, double h, double k, SourceType source_type,
                   std::vector<double> &resultado)
{
    double start_time = omp_get_wtime();

    double constante = (source_type == GAUSSIAN) ? (1.0 / e) : 1.0;
    double delta = 1.0;
    int iterations = 0;

    while (delta > TOL)
    {
        delta = 0.0;
        for (int i = 1; i < M; ++i)
        {
            for (int j = 1; j < N; ++j)
            {
                double T_new = (((T[i + 1][j] + T[i - 1][j]) * k * k) +
                                ((T[i][j + 1] + T[i][j - 1]) * h * h) -
                                (constante * source[i][j] * h * h * k * k)) /
                               (2.0 * (h * h + k * k));

                delta = std::max(delta, std::abs(T_new - T[i][j]));
                T[i][j] = T_new;
            }
        }
        ++iterations;
    }

    double end_time = omp_get_wtime();

    resultado.clear();
    resultado.push_back(static_cast<double>(iterations));            // 1. Iteraciones
    resultado.push_back(delta);                                      // 2. Tolerancia
    resultado.push_back(end_time - start_time);                      // 3. Tiempo
    resultado.push_back(static_cast<double>(omp_get_max_threads())); // 4. Número de hilos
}

int main(int argc, char *argv[])
{
    int M = 50, N = 50;
    std::string version_folder = "serial";

    bool report = false;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "--report" || arg == "-r")
        {
            report = true;
        }
    }

    for (int source = euler; source <= GAUSSIAN; ++source)
    {
        SourceType current_source = static_cast<SourceType>(source);
        std::string nombre_base;

        switch (current_source)
        {
        case euler:
            nombre_base = "euler";
            break;
        case laplace:
            nombre_base = "laplace";
            break;
        case constanza:
            nombre_base = "constanza";
            break;
        case fraccion:
            nombre_base = "fraccion";
            break;
        case GAUSSIAN:
            nombre_base = "gaussiana";
            break;
        }

        if (report)
        {
            auto simulate_once = [=]() -> std::vector<double>
            {
                Domain domain = get_domain(current_source);
                double h, k;
                std::vector<std::vector<double>> T, source_grid;

                initialize_grid(M, N, T, source_grid, h, k, current_source, domain);
                calculate_source(M, N, source_grid, h, k, current_source, domain);

                std::vector<double> resultado;
                solve_poisson(T, source_grid, M, N, h, k, current_source, resultado);
                return resultado;
            };

            run_report(simulate_once, nombre_base, 100, version_folder);
        }
        else
        {
            Domain domain = get_domain(current_source);
            double h, k;
            std::vector<std::vector<double>> T, source_grid;

            std::cout << "\nFuente " << current_source + 1 << " de 5:" << std::endl;

            initialize_grid(M, N, T, source_grid, h, k, current_source, domain);
            calculate_source(M, N, source_grid, h, k, current_source, domain);

            std::vector<double> resultado;
            solve_poisson(T, source_grid, M, N, h, k, current_source, resultado);

            std::cout << "● Iteraciones: " << static_cast<int>(resultado[0]) << "\n";
            std::cout << std::scientific << std::setprecision(6);
            std::cout << "● Tolerancia: " << resultado[1] << "\n";
            std::cout << "● Tiempo de ejecución: " << resultado[2] << " segundos\n";

            std::string filename = nombre_base + ".dat";
            export_to_file(T, h, k, M, N, domain, version_folder, filename);
        }
    }

    if (!report)
    {
        std::cout << "\nTodas las simulaciones completadas.\n";
    }

    return 0;
}