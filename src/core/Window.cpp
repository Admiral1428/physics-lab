#include "window.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_mixer.h>
#include <iostream>

Window::Window(const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        throw std::runtime_error("SDL initialization failed");
    }

    if (MIX_Init() < 0) {
        SDL_Log("MIX_Init failed: %s", SDL_GetError());
        throw std::runtime_error("SDL_mixer initialization failed");
    }

    MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!mixer) {
        SDL_Log("Could not create mixer: %s", SDL_GetError());
        throw std::runtime_error("Mixer creation failed");
    }

    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;

    if (!SDL_CreateWindowAndRenderer(title, width, height, flags, &window, &renderer)) 
    {
        SDL_Log("SDL_CreateWindowAndRenderer failed: %s", SDL_GetError());
        throw std::runtime_error("Window creation failed");
    }

    // Allow internal render resolution to differ from window resolution
    SDL_SetRenderLogicalPresentation(renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    MIX_Quit();
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