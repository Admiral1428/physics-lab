#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "core/types.hpp"

namespace Constants 
{
    // Render resolution and world scale
    inline constexpr CoreTypes::Resolution RENDER_RES{1920, 1080};
    inline constexpr int PIXELS_PER_METER = 100;

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
    inline constexpr float PHYS_DT = 1.0f / 120.0f;

    // Max number of physics updates per rendering frame (prevent "spiral of death")
    inline constexpr int MAX_PHYS_STEPS = 5;

    // Default attributes for particle
    inline constexpr float PARTICLE_MASS = 0.1;
    inline constexpr float PARTICLE_RADIUS = 6.0f/(2*PIXELS_PER_METER);  // equivalent to 6 pixel diameter
    inline constexpr float PARTICLE_MU = 0.1;  // static and dynamic friction coefficient
    inline constexpr float PARTICLE_RESTITUTION = 0.5;  // 0 no bounce, 1 fully elastic (no energy loss)

    // Default gravity in meters per second squared
    inline constexpr float GRAV = -9.81f;

}

#endif
