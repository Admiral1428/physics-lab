#ifndef CPUPARTICLEINTEGRATOR_HPP
#define CPUPARTICLEINTEGRATOR_HPP

#include <vector>
#include "physics/Integrator.hpp"

class CpuParticleIntegrator : public Integrator 
{
public:
    void step(std::vector<Particle>& particles, float dt) override;
};


#endif