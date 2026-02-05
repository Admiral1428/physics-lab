#include "core/constants.hpp"
#include "core/Window.hpp"
#include "core/Renderer.hpp"
#include "core/Engine.hpp"
#include <SDL3/SDL.h>

int main() 
{
    Window window("Physics Lab");
    Renderer renderer(window.getRenderer());
    Engine engine(renderer);

    engine.run();  // Main loop to process application logic

    return 0;
}
