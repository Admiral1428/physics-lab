#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL3/SDL.h>
#include "constants.hpp"
#include "types.hpp"

using CoreTypes::Color;

class Renderer 
{
public:
    Renderer(SDL_Renderer* renderer);
    void clear(const Color& color);
    void draw(double &alpha);
    void present();
    void render(const Color& color, double &alpha);

private:
    SDL_Renderer* renderer;
};

#endif
