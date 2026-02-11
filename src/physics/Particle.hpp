#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <Eigen/Dense>
#include "core/constants.hpp"

class Particle
{
public:
    Particle(
        Eigen::Vector2f pos = Eigen::Vector2f::Zero(),
        Eigen::Vector2f vel = Eigen::Vector2f::Zero(),
        float mass = Constants::PARTICLE_MASS, 
        float radius = Constants::PARTICLE_RADIUS,
        float mu = Constants::PARTICLE_MU,
        float restitution = Constants::PARTICLE_RESTITUTION,
        CoreTypes::Color color = Constants::BLUE
    );

    // Non-const getters (intended modification)
    Eigen::Vector2f& getPositionPrevious();
    Eigen::Vector2f& getPosition();
    Eigen::Vector2f& getVelocity();
    Eigen::Vector2f& getForces();

    // Const getters
    const Eigen::Vector2f& getPositionPrevious() const;
    const Eigen::Vector2f& getPosition() const;
    float getMass() const; 
    float getInvMass() const; 
    float getRadius() const; 
    float getMu() const; 
    float getRestituion() const; 
    const CoreTypes::Color& getColor() const;

    void applyForce(const Eigen::Vector2f& f);

private:
    // Physical state
    Eigen::Vector2f pos_previous;
    Eigen::Vector2f pos;
    Eigen::Vector2f vel;
    Eigen::Vector2f forces;

    // Physical properties
    float mass;
    float inv_mass;
    float radius;
    float mu;
    float restitution;
    CoreTypes::Color color;
};

#endif