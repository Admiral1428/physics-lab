#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "types.hpp"

namespace Constants 
{
    // Render resolution
    inline constexpr CoreTypes::Resolution RENDER_RES{1920, 1080};

    // Colors
    inline constexpr CoreTypes::Color BLACK     {  0,   0,   0, 255 };
    inline constexpr CoreTypes::Color WHITE     {255, 255, 255, 255 };
    inline constexpr CoreTypes::Color GRAY      {200, 200, 200, 255 };
    inline constexpr CoreTypes::Color RED       {255,   0,   0, 255 };
    inline constexpr CoreTypes::Color BLUE      {  0,   0, 255, 255 };
    inline constexpr CoreTypes::Color ORANGE    {255,  69,   0, 255 };
    inline constexpr CoreTypes::Color GREEN     {  0, 255,   0, 255 };
    inline constexpr CoreTypes::Color YELLOW    {255, 255,   0, 255 };
    inline constexpr CoreTypes::Color MAGENTA   {255,   0, 255, 255 };
    inline constexpr CoreTypes::Color CYAN      {  0, 255, 255, 255 };
    inline constexpr CoreTypes::Color BROWN     {150,  75,   0, 255 };
    inline constexpr CoreTypes::Color SKY_BLUE  {135, 206, 235, 255 };

    // Target time interval for how often to update physics
    inline constexpr double PHYS_DT = 1.0 / 120.0;

    // Max number of physics updates per rendering frame (prevent "spiral of death")
    inline constexpr int MAX_PHYS_STEPS = 5;
}

#endif
