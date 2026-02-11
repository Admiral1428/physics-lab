#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include <vector>
#include "physics/Particle.hpp"

class Integrator 
{
public:
    // using virtual type to allow for integrator swap flexiblity
    virtual ~Integrator() = default;
    virtual void step(std::vector<Particle>& particles, float dt) = 0;
};

#endif