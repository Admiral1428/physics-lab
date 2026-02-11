#include "core/Engine.hpp"
#include "core/constants.hpp"
#include <SDL3/SDL.h>

using namespace Constants;

Engine::Engine(Renderer& _renderer, std::unique_ptr<PhysicsSystem> _physics_system)
        : renderer(_renderer), physics_system(std::move(_physics_system)) {}

void Engine::run()
{
    SDL_Event event;
    auto& particles = physics_system->getParticles();

    while (!quit) {
        // delta time since last frame
        Uint64 current_frame_time = SDL_GetPerformanceCounter();
        float frame_dt = static_cast<float>(current_frame_time - last_frame_time) / perf_freq;
        last_frame_time = current_frame_time;

        processEvents(event);  // inputs from user

        if (simulation_started)
        {
            accumulator += frame_dt;

            int steps = 0; 
            while (accumulator >= PHYS_DT && steps < MAX_PHYS_STEPS)
            { 
                physics_system->update(PHYS_DT);
                accumulator -= PHYS_DT; 
                steps++;
            }
        }
        else
        {
            accumulator = 0.0f;
        }
        
        double alpha = accumulator / PHYS_DT;  // Interpolation value between physics frames
        renderer.render(WHITE, alpha, particles);
    }
}

void Engine::processEvents(SDL_Event &event)
{
    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            quit = true;
        }
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
        { 
            simulation_started = true;
        }
    }
}