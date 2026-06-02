#include "Particle.h"

// Actualiza el estado de la partícula bajo un campo eléctrico aplicado.
void Particle::update(const Vector2D &electricField, double dt)
{
    // Fuerza eléctrica: F = q * E (Ley de Lorentz para campos estáticos)
    Vector2D force = electricField * charge;

    // Aceleración: a = F/m (Segunda Ley de Newton)
    Vector2D acceleration = force / mass;

    // Integración tipo Euler explícito:
    velocity = velocity + acceleration * dt; // Actualiza velocidad [m/s]
    position = position + velocity * dt;     // Actualiza posición [m]
}