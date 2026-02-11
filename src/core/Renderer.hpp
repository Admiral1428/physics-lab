#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL3/SDL.h>
#include "core/constants.hpp"
#include "core/types.hpp"
#include "physics/Particle.hpp"

using CoreTypes::Color;

class Renderer 
{
public:
    Renderer(SDL_Renderer* _renderer);
    void clear(const Color& color);
    void draw(double &alpha, std::vector<Particle>& particles);
    void drawFilledCircle(int cx, int cy, int radius, const Color& color);
    void present();
    void render(const Color& color, double &alpha, std::vector<Particle>& particles);

private:
    SDL_Renderer* renderer;
};

#endif
