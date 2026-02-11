#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL3/SDL.h>
#include "core/constants.hpp"
#include "core/Renderer.hpp"
#include "physics/PhysicsSystem.hpp"

class Engine 
{
public:
    Engine(Renderer& _renderer, std::unique_ptr<PhysicsSystem> _physics_system);
    void run();
    void processEvents(SDL_Event &event);

private:
    Renderer& renderer;
    std::unique_ptr<PhysicsSystem> physics_system;
    bool quit = false;
    bool simulation_started = false;
    Uint64 last_frame_time = SDL_GetPerformanceCounter();  // Frame timing
    const float perf_freq = static_cast<float>(SDL_GetPerformanceFrequency());
    double accumulator = 0.0;  // Ensure appropriate physics update frequency
};

#endif
