#ifndef POISSON_H
#define POISSON_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <omp.h>

namespace fs = std::filesystem;

const double e = 8.85e-12; // Permitividad eléctrica
const double TOL = 1e-6;

enum SourceType
{
    euler,
    laplace,
    constanza,
    fraccion,
    GAUSSIAN
};

struct Domain
{
    double x0, xf;
    double y0, yf;
};

// Obtiene el dominio espacial para cada tipo de fuente
Domain get_domain(SourceType source_type)
{
    switch (source_type)
    {
    case euler:
        return {0.0, 2.0, 0.0, 1.0}; // x ∈ [0,2], y ∈ [0,1]
    case laplace:
        return {1.0, 2.0, 0.0, 1.0}; // x ∈ [1,2], y ∈ [0,1]
    case constanza:
        return {1.0, 2.0, 0.0, 2.0}; // x ∈ [1,2], y ∈ [0,2]
    case fraccion:
        return {1.0, 2.0, 1.0, 2.0}; // x ∈ [1,2], y ∈ [1,2]
    case GAUSSIAN:
        return {0.0, 1.0, 0.0, 1.0}; // x ∈ [0,1], y ∈ [0,1]
    default:
        return {0.0, 1.0, 0.0, 1.0};
    }
}

// Inicializa las matrices de la grilla y las condiciones de frontera
void initialize_grid(int M, int N, std::vector<std::vector<double>> &T,
                     std::vector<std::vector<double>> &source, double &h, double &k,
                     SourceType source_type, const Domain &domain)
{
    h = (domain.xf - domain.x0) / M;
    k = (domain.yf - domain.y0) / N;

    T.resize(M + 1, std::vector<double>(N + 1, 0.0));
    source.resize(M + 1, std::vector<double>(N + 1, 0.0));

    // Configuración de condiciones de frontera según el tipo de fuente
    switch (source_type)
    {
    case euler:
        for (int j = 0; j <= N; ++j)
        {
            double y = domain.y0 + j * k;
            T[0][j] = 1.0;          // V(0, y) = 1
            T[M][j] = exp(2.0 * y); // V(2, y) = e^(2y)
        }
        for (int i = 0; i <= M; ++i)
        {
            double x = domain.x0 + i * h;
            T[i][0] = 1.0;    // V(x, 0) = 1
            T[i][N] = exp(x); // V(x, 1) = e^x
        }
        break;

    case laplace:
        for (int j = 0; j <= N; ++j)
        {
            double y = domain.y0 + j * k;
            T[0][j] = log(y * y + 1); // V(1, y) = ln(y² + 1)
            T[M][j] = log(y * y + 4); // V(2, y) = ln(y² + 4)
        }
        for (int i = 0; i <= M; ++i)
        {
            double x = domain.x0 + i * h;
            T[i][0] = 2.0 * log(x);   // V(x, 0) = 2ln(x)
            T[i][N] = log(x * x + 1); // V(x, 1) = ln(x² + 1)
        }
        break;

    case constanza:
        for (int j = 0; j <= N; ++j)
        {
            double y = domain.y0 + j * k;
            T[0][j] = (1.0 - y) * (1.0 - y); // V(1, y) = (1-y)²
            T[M][j] = (2.0 - y) * (2.0 - y); // V(2, y) = (2-y)²
        }
        for (int i = 0; i <= M; ++i)
        {
            double x = domain.x0 + i * h;
            T[i][0] = x * x;                 // V(x, 0) = x²
            T[i][N] = (x - 2.0) * (x - 2.0); // V(x, 2) = (x-2)²
        }
        break;

    case fraccion:
        for (int j = 0; j <= N; ++j)
        {
            double y = domain.y0 + j * k;
            if (y > 0)
            {
                T[0][j] = y * log(y);             // V(1, y) = y ln(y)
                T[M][j] = 2.0 * y * log(2.0 * y); // V(2, y) = 2y ln(2y)
            }
            else
            {
                T[0][j] = 0.0;
                T[M][j] = 0.0;
            }
        }
        for (int i = 0; i <= M; ++i)
        {
            double x = domain.x0 + i * h;
            if (x > 0)
            {
                T[i][0] = x * log(x);           // V(x, 1) = x ln(x)
                T[i][N] = x * log(4.0 * x * x); // V(x, 2) = 2x ln(2x)
            }
            else
            {
                T[i][0] = 0.0;
                T[i][N] = 0.0;
            }
        }
        break;

    case GAUSSIAN:
    default:
        // Condiciones de frontera originales para la fuente gaussiana
        for (int j = 0; j <= N; ++j)
        {
            T[0][j] = 0.0;
            T[M][j] = 0.0;
        }
        for (int i = 0; i <= M; ++i)
        {
            T[i][0] = 0.0;
            T[i][N] = pow(domain.x0 + i * h, 1.0);
        }
        break;
    }
}

// Calcula el término fuente según el tipo seleccionado
void calculate_source(int M, int N, std::vector<std::vector<double>> &source,
                      double h, double k, SourceType source_type, const Domain &domain)
{
    for (int i = 0; i <= M; ++i)
    {
        for (int j = 0; j <= N; ++j)
        {
            double x = domain.x0 + i * h;
            double y = domain.y0 + j * k;

            switch (source_type)
            {
            case euler:
                source[i][j] = (x * x + y * y) * exp(x * y);
                break;

            case laplace:
                source[i][j] = 0.0; // ∇²V = 0
                break;

            case constanza:
                source[i][j] = 4.0; // ∇²V = 4
                break;

            case fraccion:
                if (x != 0.0 && y != 0.0)
                {
                    source[i][j] = x / y + y / x;
                }
                else
                {
                    source[i][j] = 0.0; // Evitar división por cero
                }
                break;

            case GAUSSIAN:
            default:
                // Fuente gaussiana original
                double mu_x = (domain.x0 + domain.xf) / 2.0;
                double mu_y = (domain.y0 + domain.yf) / 2.0;
                double sigma = 0.1;
                source[i][j] = exp(-((x - mu_x) * (x - mu_x) + (y - mu_y) * (y - mu_y)) /
                                   (2 * sigma * sigma)) /
                               (sqrt(2 * M_PI * sigma));
                break;
            }

            // Condiciones de contorno para la fuente (cero en los bordes)
            if (i == 0 || i == M || j == 0 || j == N)
            {
                source[i][j] = 0.0;
            }
        }
    }
}

// Exporta los resultados de la matriz T a un archivo .dat
void export_to_file(const std::vector<std::vector<double>> &T, double h, double k,
                    int M, int N, const Domain &domain, const std::string &subfolder,
                    const std::string &filename)
{
    // Crear directorio data si no existe
    fs::create_directory("data");

    // Crear subdirectorio para esta versión
    std::string folder_path = "data/" + subfolder;
    fs::create_directory(folder_path);

    std::ofstream file(folder_path + "/" + filename);
    if (!file.is_open())
    {
        std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
        return;
    }
    for (int i = 0; i <= M; ++i)
    {
        for (int j = 0; j <= N; ++j)
        {
            double x = domain.x0 + i * h;
            double y = domain.y0 + j * k;
            file << x << "\t" << y << "\t" << T[i][j] << "\n";
        }
    }
    file.close();
    std::cout << "Resultados exportados a " << folder_path << "/" << filename << std::endl;
}

#endif