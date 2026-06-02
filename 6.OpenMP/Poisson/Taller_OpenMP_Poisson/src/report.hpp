#ifndef REPORT_UTILS_HPP
#define REPORT_UTILS_HPP

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <iostream>

template <typename SimulationFunc>
void run_report(SimulationFunc simulate_once,
                const std::string &nombre_base,
                int num_ejecuciones,
                const std::string &version_folder)
{
    namespace fs = std::filesystem;

    // Base y subdirectorios
    std::string base_dir = "report/" + version_folder;
    std::string data_dir = base_dir + "/data";
    std::string imag_dir = base_dir + "/imag";
    std::string resumen_file = base_dir + "/summary.txt";
    std::string data_file = data_dir + "/" + nombre_base + ".dat";

    // Borrar solo una vez por ejecución si ya existe la carpeta
    static bool initialized = false;
    if (!initialized)
    {
        if (fs::exists(base_dir))
        {
            std::cout << "[Inicialización] Limpiando: " << base_dir << "\n";
            fs::remove_all(base_dir);
        }
        fs::create_directories(data_dir);
        fs::create_directories(imag_dir);
        initialized = true;
    }

    std::vector<std::vector<double>> resultados(num_ejecuciones);
    std::vector<double> suma;

    // Ejecutar simulaciones
    for (int i = 0; i < num_ejecuciones; ++i)
    {
        resultados[i] = simulate_once();

        if (suma.empty())
            suma.resize(resultados[i].size(), 0.0);

        for (size_t j = 0; j < resultados[i].size(); ++j)
            suma[j] += resultados[i][j];
    }

    // Calcular promedios
    std::vector<double> promedio(suma.size());
    for (size_t j = 0; j < suma.size(); ++j)
        promedio[j] = suma[j] / num_ejecuciones;

    // Guardar resultados individuales (.dat)
    std::ofstream data_out(data_file);
    for (int i = 0; i < num_ejecuciones; ++i)
    {
        data_out << i + 1;
        for (const auto &val : resultados[i])
        {
            data_out << "\t" << std::setprecision(15) << val;
        }
        data_out << "\n";
    }
    data_out.close();

    // Guardar resumen (summary.txt)
    std::ofstream resumen_out(resumen_file, std::ios::app);
    resumen_out << std::scientific << std::setprecision(6);
    resumen_out << "Promedios de resultados para: " << nombre_base << "\n";
    for (size_t j = 0; j < promedio.size(); ++j)
    {
        resumen_out << "Valor " << j + 1 << ": " << promedio[j] << "\n";
    }
    resumen_out << "\n";
    resumen_out.close();

    std::cout << "[Reporte] Fuente '" << nombre_base << "' completada.\n";
}

#endif