#ifndef TYPES_HPP
#define TYPES_HPP

#include <SDL3/SDL.h>

namespace CoreTypes 
{
    struct Color 
    {
        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;
    };

    struct Resolution 
    {
        int width;
        int height;
    };
}

#endif
