#include "Renderer.hpp"
#include "constants.hpp"
#include <SDL3/SDL.h>

Renderer::Renderer(SDL_Renderer* input_renderer) : renderer(input_renderer) {}

// Clear renderer with a solid color
void Renderer::clear(const Color& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

// Draw physics objects
void Renderer::draw(double &alpha)
{
    // draw physics objects based on interpolation value between states
}

// Present the updated renderer to the screen
void Renderer::present()
{
    SDL_RenderPresent(renderer);
}

void Renderer::render(const Color& color, double &alpha)
{
    clear(color);
    draw(alpha); 
    present();
}