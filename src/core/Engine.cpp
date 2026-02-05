#include "Engine.hpp"
#include <SDL3/SDL.h>
#include "constants.hpp"

using namespace Constants;

Engine::Engine(Renderer& input_renderer) : renderer(input_renderer) {}

void Engine::run()
{
    SDL_Event event;

    while (!quit) {
        // delta time since last frame
        Uint64 current_frame_time = SDL_GetPerformanceCounter();
        float frame_dt = static_cast<float>(current_frame_time - last_frame_time) / perf_freq;
        last_frame_time = current_frame_time;
        accumulator += frame_dt;

        process_events(event);  // inputs from user

        int steps = 0; 
        while (accumulator >= PHYS_DT && steps < MAX_PHYS_STEPS)
        { 
            // update physics based on PHYS_DT, then:
            accumulator -= PHYS_DT; 
            steps++;
        }

        double alpha = accumulator / PHYS_DT;  // Interpolation value between physics frames
        renderer.render(WHITE, alpha);
    }
}

void Engine::process_events(SDL_Event &event)
{
    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            quit = true;
        }
    }
}