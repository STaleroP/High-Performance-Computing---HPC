#include <iostream>   // Para entrada/salida estándar (cout)
#include <fstream>    // Para manejo de archivos (ofstream)
#include <chrono>     // Para medición de tiempo (high_resolution_clock)
#include "Particle.h" // Clase Particle y definiciones de constantes (PROTON_MASS, etc.)
#include "utils.h"    // Funciones auxiliares (calcularCampo, operadores Vector2D)

int main()
{
    // Crea partículas: protón (p1) y electrón (p2) con posición/velocidad inicial
    Particle p1(PROTON_MASS, PROTON_CHARGE, {0.0, 0.0}, {0.0, 0.0});
    Particle p2(ELECTRON_MASS, ELECTRON_CHARGE, {5.29e-11, 0.0}, {0.0, 2.19e6});

    double dt = 1e-18; // Paso temporal de simulación (en segundos)
    int steps = 1000;  // Número de iteraciones

    // Archivos para guardar trayectorias de las partículas
    std::ofstream archivo1("particula1.txt");
    std::ofstream archivo2("particula2.txt");

    // Inicia medición de tiempo de ejecución
    auto inicio = std::chrono::high_resolution_clock::now();

    // Bucle de simulación
    for (int i = 0; i < steps; ++i)
    {
        // Calcula campo eléctrico en la posición de cada partícula
        Vector2D E1 = calcularCampo(p1, p2.position);
        Vector2D E2 = calcularCampo(p2, p1.position);

        // Actualiza posición/velocidad de las partículas (F = q*E)
        p1.update(E2, dt);
        p2.update(E1, dt);

        // Muestra posiciones en consola
        std::cout << "Paso " << i << ":\n";
        std::cout << "  Partícula 1: " << p1.position << "\n";
        std::cout << "  Partícula 2: " << p2.position << "\n";

        // Guarda posiciones en archivos
        archivo1 << p1.position << "\n";
        archivo2 << p2.position << "\n";
    }

    // Finaliza medición de tiempo y muestra resultados
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;
    archivo1.close();
    archivo2.close();

    std::cout << "Tiempo total de simulación: " << duracion.count() << " s" << std::endl;

    return 0;
}