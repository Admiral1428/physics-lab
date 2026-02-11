#include <vector>
#include "physics/Particle.hpp"
#include "physics/CpuParticleIntegrator.hpp"

void CpuParticleIntegrator::step(std::vector<Particle>& particles, float dt)
{ 
    for (auto& p : particles) 
    {
        auto& pos_previous = p.getPositionPrevious();
        auto& pos = p.getPosition();
        auto& vel = p.getVelocity();
        auto& forces = p.getForces();
        auto inv_mass = p.getInvMass();

        // Set previous position before updating new position
        pos_previous = pos;

        Eigen::Vector2f accel = forces * inv_mass;

        // Semi Implicit Euler:
        vel += accel * dt;
        pos += vel * dt;

        // Reset sum of forces
        forces.setZero();
    }
}

