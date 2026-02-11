#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL3/SDL.h>
#include "core/constants.hpp"

class Window {
public:
    Window(const char* title,
           int width = Constants::RENDER_RES.width,
           int height = Constants::RENDER_RES.height);
    ~Window();

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

#endif