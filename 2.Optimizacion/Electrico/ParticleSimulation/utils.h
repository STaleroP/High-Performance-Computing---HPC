#ifndef UTILS_H
#define UTILS_H

#include <cmath>      // Para funciones matemáticas (sqrt, M_PI)
#include "Particle.h" // Definición de Particle y Vector2D

// Constantes físicas fundamentales (unidades SI)
const double EPSILON_0 = 8.854187817e-12;        // Permitividad del vacío [F/m]
const double ELECTRON_CHARGE = -1.602176634e-19; // Carga del electrón [C]
const double PROTON_CHARGE = 1.602176634e-19;    // Carga del protón [C]
const double ELECTRON_MASS = 9.10938356e-31;     // Masa del electrón [kg]
const double PROTON_MASS = 1.6726219e-27;        // Masa del protón [kg]

// Calcula el campo eléctrico generado por una partícula cargada.
Vector2D calcularCampo(const Particle &fuente, const Vector2D &destino)
{
    double dx = destino.x - fuente.position.x; // Diferencia en x [m]
    double dy = destino.y - fuente.position.y; // Diferencia en y [m]
    double r2 = dx * dx + dy * dy;             // Distancia al cuadrado [m²]
    double r = std::sqrt(r2);                  // Distancia [m]

    // Evita división por cero si las partículas están muy cerca
    if (r < 1e-12)
        return Vector2D(0.0, 0.0);

    // Ley de Coulomb: E = (1/4πε₀) * (q/r²) * (vector unitario r̂)
    double coef = (1.0 / (4 * M_PI * EPSILON_0)) * (fuente.charge / r2);
    return Vector2D(coef * dx / r, coef * dy / r); // Campo en componentes x/y
}

#endif // UTILS_H