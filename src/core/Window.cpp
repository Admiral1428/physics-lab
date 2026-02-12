#include "core/Window.hpp"
#include "core/Logger.hpp"
#include <SDL3/SDL.h>
#include <iostream>

Window::Window(const char* title, int width, int height)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) 
    {
        Logger::error(std::string("SDL_Init failed: ") + SDL_GetError());
        throw std::runtime_error("SDL initialization failed");
    }

    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;

    if (!SDL_CreateWindowAndRenderer(title, width, height, flags, &window, &renderer)) 
    {
        Logger::error(std::string("SDL_CreateWindowAndRenderer failed: ") + SDL_GetError());
        throw std::runtime_error("Window creation failed");
    }

    // Allow internal render resolution to differ from window resolution
    SDL_SetRenderLogicalPresentation(renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window* Window::getWindow() const
{
    return window;
}

SDL_Renderer* Window::getRenderer() const
{
    return renderer;
}
