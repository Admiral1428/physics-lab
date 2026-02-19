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
    integrator->step(particles, dt);

    bool do_normal_impulse = true;

    // Multiple solver passes to help with collision detection stability
    for (int i = 0; i < Constants::SOLVER_ITERS; ++i)
    {
        // Do normal impulse only on first solver iteration
        if (i > 0)
        {
            do_normal_impulse = false;
        }
        addParticlesToGrid();
        checkParticleCollisions(do_normal_impulse);
        checkScreenCollisions();
    }

    stabilizeFloorContact();

    for (auto& p : particles)
    {
        p.getPositionPrevious() = p.getPosition();
    }

}

void PhysicsSystem::applyGravity() 
{
    for (auto& p : particles) 
    {
        auto& forces = p.getForces();
        auto mass = p.getMass();

        forces += Eigen::Vector2f(0.0f, Constants::GRAV * mass);
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
        if (pos[1] + radius > half_h)
        {
            pos[1] = half_h - radius;
            vel[1] = -vel[1] * restitution; // Normal bounce
            vel[0] *= (1.0f - mu);
        }

        // top wall (ceiling)
        if (pos[1] - radius < -half_h)
        {
            pos[1] = -half_h + radius;
            vel[1] = -vel[1] * restitution;
            vel[0] *= (1.0f - mu);
        }

    }
}

size_t PhysicsSystem::hashCell(int x, int y) 
{
    // Large primes to spread inputs far apart in hash space
    const size_t p1 = 73856093;
    const size_t p2 = 19349663;
    return (size_t(x) * p1) ^ (size_t(y) * p2);
}

void PhysicsSystem::addParticlesToGrid()
{
    grid.clear();
    auto cellSize = Constants::CELL_SIZE;

    for (auto & p: particles)
    {
        auto &pos = p.getPosition();
        int cell_x = int(floor(pos[0] / cellSize));
        int cell_y = int(floor(pos[1] / cellSize));

        size_t cellKey = hashCell(cell_x, cell_y);

        grid[cellKey].push_back(&p); 
    }
}

void PhysicsSystem::checkParticleCollisions(const bool & do_normal_impulse)
{
    auto cellSize = Constants::CELL_SIZE;

    for (auto& A : particles)
    {
        const auto& posA = A.getPosition();
        int cellX = int(floor(posA[0] / cellSize));
        int cellY = int(floor(posA[1] / cellSize));

        // Check current cell + neighbors
        for (auto& off : Constants::OFFSETS)
        {
            int nx = cellX + off[0];
            int ny = cellY + off[1];

            size_t key = hashCell(nx, ny);

            auto it = grid.find(key);
            if (it == grid.end())
                continue;

            // Check against all particles in this bucket
            for (Particle* B : it->second)
            {
                /* avoid repetitive checks and self (only resolve 
                when the memory address of A is before B.) */
                if (&A >= B)
                    continue; 

                if (checkCollision(A, *B))
                {
                    resolveCollision(A, *B, do_normal_impulse);
                }
            }
        }
    }
}

bool PhysicsSystem::checkCollision(const Particle& A, const Particle& B)
{
    auto& posA = A.getPosition();
    auto& posB = B.getPosition();

    auto radA = A.getRadius();
    auto radB = B.getRadius();

    /* Get Euclidean distance between Particles 
    (squared norm less expensive than sqrt) */
    auto delta = posB-posA;
    auto dist_squared = delta.squaredNorm();

    auto radSum = radA + radB;

    // If distance less than sum of radii, collision occured
    if (dist_squared < radSum * radSum)
    {
        return true;
    }
    return false;
}

void PhysicsSystem::resolveCollision(Particle& A, Particle& B, const bool & do_normal_impulse)
{
    auto& posA = A.getPosition();
    auto& posB = B.getPosition();

    auto& velA = A.getVelocity();
    auto& velB = B.getVelocity();

    float radA = A.getRadius();
    float radB = B.getRadius();

    float inv_massA = A.getInvMass();
    float inv_massB = B.getInvMass();

    float restA = A.getRestituion();
    float restB = B.getRestituion();

    // Relative position
    Eigen::Vector2f delta = posB - posA;
    float dist = delta.norm();

    // Collision normal with stable fallback
    Eigen::Vector2f coll_normal;
    if (dist > 1e-8f)
        coll_normal = delta / dist;
    else
        coll_normal = Eigen::Vector2f(1.0f, 0.0f); // deterministic fallback

    float radSum = radA + radB;
    float penetration = radSum - dist;

    // If no penetration, no action
    if (penetration <= 0.0f)
        return;

    // Relative velocity
    Eigen::Vector2f vel_rel = velB - velA;

    // Ensure normal points from A to B against relative motion
    if (vel_rel.dot(coll_normal) > 0.0f)
        coll_normal = -coll_normal;

    float vel_rel_normal = vel_rel.dot(coll_normal);

    // Impulse: only if approaching (not separating) and only if specified
    if (do_normal_impulse && vel_rel_normal < 0.0f)
    {
        float e = std::min(restA, restB);

        float j = -(1.0f + e) * vel_rel_normal / (inv_massA + inv_massB);
        Eigen::Vector2f j_vec = j * coll_normal;

        velA -= j_vec * inv_massA;
        velB += j_vec * inv_massB;
    }

    // Positional correction: always if penetration > 0
    penetration = std::min(penetration, Constants::CLAMP_PEN * radSum);

    float correction = std::max(penetration - Constants::SLOP, 0.0f) * Constants::PCT;
    correction = std::min(correction, Constants::CLAMP_CORR * radSum);

    Eigen::Vector2f corr_vec = correction * coll_normal;

    float invMassSum = inv_massA + inv_massB;
    if (invMassSum > 0.0f)
    {
        posA -= corr_vec * (inv_massA / invMassSum);
        posB += corr_vec * (inv_massB / invMassSum);
    }
}

void PhysicsSystem::stabilizeFloorContact()
{
    float half_h = (Constants::RENDER_RES.height * 0.5f) / Constants::PIXELS_PER_METER;

    for (auto& p : particles)
    {
        auto& pos_prev = p.getPositionPrevious();
        auto& pos = p.getPosition();
        auto& vel = p.getVelocity();
        float radius = p.getRadius();

        bool onFloor = (pos[1] + radius >= half_h);

        // If particle on floor and vertical velocity is tiny, snap to resting state
        if (onFloor && std::abs(vel[1]) < Constants::VEL_THRESHOLD)
        {
            pos[1] = half_h - radius;   // snap to floor
            vel[1] = 0.0f;              // eliminate vertical jitter
            pos_prev = pos;
        } 
    }

    
}
