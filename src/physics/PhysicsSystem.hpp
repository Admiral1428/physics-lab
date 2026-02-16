#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include <vector>
#include <memory>
#include "physics/Particle.hpp"
#include "physics/Integrator.hpp"

class PhysicsSystem 
{
public:
    PhysicsSystem(std::unique_ptr<Integrator> integrator);

    void addParticle(const Particle& p);
    std::vector<Particle>& getParticles();
    void update(float dt);

private:
    void applyGravity();
    void checkScreenCollisions();
    size_t hashCell(int x, int y);
    void addParticlesToGrid();
    void checkParticleCollisions();
    bool checkCollision(const Particle& A, const Particle& B);
    void resolveCollision(Particle& A, Particle& B);

    std::vector<Particle> particles;
    std::unique_ptr<Integrator> integrator;
    std::unordered_map<size_t, std::vector<Particle*>> grid;
};

#endif
