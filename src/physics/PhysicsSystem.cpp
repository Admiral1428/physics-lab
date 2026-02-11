#include <vector>
#include "physics/PhysicsSystem.hpp"
#include "core/constants.hpp"

PhysicsSystem::PhysicsSystem(std::unique_ptr<Integrator> integrator)
        : integrator(std::move(integrator)) {}

void PhysicsSystem::addParticle(const Particle& p) 
{
    particles.push_back(p);
}

std::vector<Particle>& PhysicsSystem::getParticles()
{
    return particles;
}

void PhysicsSystem::update(float dt) 
{
    applyGravity();
    checkScreenCollisions();
    integrator->step(particles, dt);
}

void PhysicsSystem::applyGravity() 
{
    for (auto& p : particles) 
    {
        auto& forces = p.getForces();
        auto mass = p.getMass();
        forces += Eigen::Vector2f(0.0f, -Constants::GRAV * mass);
    }
}

void PhysicsSystem::checkScreenCollisions()
{
    float half_w = (Constants::RENDER_RES.width  * 0.5f) / Constants::PIXELS_PER_METER;
    float half_h = (Constants::RENDER_RES.height * 0.5f) / Constants::PIXELS_PER_METER;

    for (auto& p : particles)
    {
        auto &pos = p.getPosition();
        auto &vel = p.getVelocity();
        float radius = p.getRadius();
        float restitution = p.getRestituion();
        float mu = p.getMu();

        // left wall
        if (pos[0] - radius < -half_w) 
        {
            pos[0] = -half_w + radius;       // positional correction
            vel[0] = -vel[0] * restitution;  // bounce 
            vel[1] *= (1.0f - mu);          // friction
        }

        // right wall
        if (pos[0] + radius > half_w) 
        {
            pos[0] = half_w - radius;       // positional correction
            vel[0] = -vel[0] * restitution;  // bounce 
            vel[1] *= (1.0f - mu);          // friction
        }

        // bottom wall (floor)
        if (pos[1] - radius < -half_h)
        {
            pos[1] = -half_h + radius;
            vel[1] = -vel[1] * restitution;
            vel[0] *= (1.0f - mu);
        }

        // top wall (ceiling)
        if (pos[1] + radius > half_h)
        {
            pos[1] = half_h - radius;
            vel[1] = -vel[1] * restitution;
            vel[0] *= (1.0f - mu);
        }

    }
}