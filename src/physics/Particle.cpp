#include "physics/Particle.hpp"
#include "core/Logger.hpp"
#include "core/types.hpp"
#include <stdexcept>


Particle::Particle(
    Eigen::Vector2f _pos,
    Eigen::Vector2f _vel,
    float _mass, 
    float _radius,
    float _mu,
    float _restitution,
    CoreTypes::Color _color
)
    : pos_previous(_pos)
    , pos(_pos)
    , vel(_vel)
    , mass(_mass)
    , radius(_radius)
    , mu(_mu)
    , restitution(_restitution)
    , color(_color)
{
    forces = Eigen::Vector2f::Zero();
    if (_mass > 0)
    {
        inv_mass = 1/_mass;
    }
    else
    {
        Logger::error("Invalid particle mass: " + std::to_string(mass));
        throw std::runtime_error("Mass must be greater than zero for a particle.");
    }
}

Eigen::Vector2f& Particle::getPositionPrevious()
{
    return pos_previous; 
}

Eigen::Vector2f& Particle::getPosition()
{
    return pos; 
}
    
Eigen::Vector2f& Particle::getVelocity()
{
    return vel;
}

Eigen::Vector2f& Particle::getForces()
{
    return forces;
}

const Eigen::Vector2f& Particle::getPositionPrevious() const
{
    return pos_previous; 
}

const Eigen::Vector2f& Particle::getPosition() const
{
    return pos; 
}

float Particle::getMass() const
{ 
    return mass;
} 

float Particle::getInvMass() const
{ 
    return inv_mass; 
} 
    
float Particle::getRadius() const 
{ 
    return radius;
} 

float Particle::getMu() const
{
    return mu;
} 

float Particle::getRestituion() const
{
    return restitution;
} 

const CoreTypes::Color& Particle::getColor() const
{
    return color;
} 

void Particle::applyForce(const Eigen::Vector2f& f)
{
    forces += f;
}