#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL3/SDL.h>
#include "constants.hpp"
#include "Renderer.hpp"

class Engine 
{
public:
    Engine(Renderer& input_renderer);
    void run();
    void process_events(SDL_Event &event);

private:
    Renderer& renderer;
    bool quit = false;
    Uint64 last_frame_time = 0;  // Frame timing
    const float perf_freq = static_cast<float>(SDL_GetPerformanceFrequency());
    double accumulator = 0.0;  // Ensure appropriate physics update frequency
};

#endif
