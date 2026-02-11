#include "core/Logger.hpp"
#include "core/Window.hpp"
#include "core/Renderer.hpp"
#include "core/Engine.hpp"
#include "physics/PhysicsSystem.hpp"
#include "physics/CpuParticleIntegrator.hpp"
#include "physics/Particle.hpp"
#include <SDL3/SDL.h>

int main() 
{
    Logger::init("physics_lab.log");

    try
    {
        Window window("Physics Lab");
        Renderer renderer(window.getRenderer());

        // Smart pointers for physics integrator and system
        auto integrator = std::make_unique<CpuParticleIntegrator>();
        auto physics_system = std::make_unique<PhysicsSystem>(std::move(integrator));

        // Get particles for system
        Particle test_particle;
        physics_system->addParticle(test_particle);

        Engine engine(renderer, std::move(physics_system));

        engine.run();  // Main loop to process application logic
    }
    catch (const std::exception & e)
    {
        Logger::error(std::string("Unhandled exception: ") + e.what()); 
        return 1;
    }

    return 0;
}
