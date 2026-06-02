#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream> // Para operaciones de entrada/salida (cout, cin)
#include <fstream>  // Para manejo de archivos (ofstream)

// Estructura que representa un vector bidimensional con unidades en metros (m)
struct Vector2D
{
    double x; // Componente x en metros (m)
    double y; // Componente y en metros (m)

    // Constructor con valores por defecto (0.0 m, 0.0 m)
    Vector2D(double x_ = 0.0, double y_ = 0.0) : x(x_), y(y_) {}

    // Sobrecarga del operador + para suma de vectores
    Vector2D operator+(const Vector2D &other) const
    {
        return Vector2D(x + other.x, y + other.y); // Retorna suma componente a componente
    }

    // Sobrecarga del operador * para multiplicación por escalar (adimensional)
    Vector2D operator*(double scalar) const
    {
        return Vector2D(x * scalar, y * scalar); // Escala ambas componentes
    }

    // Sobrecarga del operador / para división por escalar (adimensional)
    Vector2D operator/(double scalar) const
    {
        return Vector2D(x / scalar, y / scalar); // Divide ambas componentes
    }

    // Sobrecarga del operador << para salida por consola (unidades implícitas)
    friend std::ostream &operator<<(std::ostream &os, const Vector2D &v)
    {
        os << v.x << " " << v.y; // Formato: "x y"
        return os;
    }

    // Sobrecarga del operador << para salida a archivo (unidades implícitas)
    friend std::ofstream &operator<<(std::ofstream &ofs, const Vector2D &v)
    {
        ofs << v.x << " " << v.y; // Formato: "x y"
        return ofs;
    }
};

// Clase que modela una partícula física
class Particle
{
public:
    double mass;       // Masa en kilogramos (kg)
    double charge;     // Carga en culombios (C)
    Vector2D position; // Posición en metros (m)
    Vector2D velocity; // Velocidad en metros/segundo (m/s)

    // Constructor con inicialización de parámetros
    Particle(double m, double q, Vector2D pos, Vector2D vel)
        : mass(m), charge(q), position(pos), velocity(vel) {}

    // Método para actualizar posición y velocidad bajo un campo eléctrico
    // electricField: Campo eléctrico en voltios/metro (V/m)
    // dt: Paso temporal en segundos (s)
    void update(const Vector2D &electricField, double dt);
};

#endif // Fin del guardia de inclusión