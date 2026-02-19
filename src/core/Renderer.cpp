#include "core/Renderer.hpp"
#include "core/constants.hpp"
#include "physics/Particle.hpp"
#include <SDL3/SDL.h>
#include <cmath>

Renderer::Renderer(SDL_Renderer* _renderer) : renderer(_renderer) {}

// Clear renderer with a solid color
void Renderer::clear(const Color& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

// Draw physics objects
void Renderer::draw(double &alpha, std::vector<Particle>& particles)
{
    int cx = Constants::RENDER_RES.width / 2;
    int cy = Constants::RENDER_RES.height / 2;

    // draw physics objects based on interpolation value between states
    for (const auto & p: particles)
    {
        const auto& pos_previous = p.getPositionPrevious();
        const auto& pos = p.getPosition();
        const auto radius = p.getRadius();
        const auto& color = p.getColor();
        auto interp_pos = pos_previous * (1.0 - alpha) + pos * alpha;

        // convert world position to screen position
        float sx_f = cx + interp_pos[0] * Constants::PIXELS_PER_METER;
        float sy_f = cy + interp_pos[1] * Constants::PIXELS_PER_METER;

        int sx = (int)std::round(sx_f);
        int sy = (int)std::round(sy_f);

        int pixel_radius = static_cast<int>(radius * Constants::PIXELS_PER_METER); 
        drawFilledCircle(sx, sy, pixel_radius, color);
    }
}

// Drawing filled circle for particle
void Renderer::drawFilledCircle(int sx, int sy, int radius, const Color& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int dy = -radius; dy <= radius; dy++)
    {
        // logic to get symmetric circle (ensuring boundaries don't round inward)
        float fx = sqrtf(radius*radius - dy*dy);
        int left  = (int)ceil(sx - fx);
        int right = (int)floor(sx + fx);
        SDL_RenderLine(renderer, left, sy + dy, right, sy + dy);
    }
}

// Present the updated renderer to the screen
void Renderer::present()
{
    SDL_RenderPresent(renderer);
}

void Renderer::render(const Color& color, double &alpha, std::vector<Particle>& particles)
{
    clear(color);
    draw(alpha, particles); 
    present();
}