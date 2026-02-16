#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "core/types.hpp"
#include <unordered_map>
#include <string>

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
    inline constexpr CoreTypes::Color DKGREEN   {  0, 150,   0, 255 };
    inline constexpr CoreTypes::Color YELLOW    {255, 255,   0, 255 };
    inline constexpr CoreTypes::Color MAGENTA   {255,   0, 255, 255 };
    inline constexpr CoreTypes::Color CYAN      {  0, 255, 255, 255 };
    inline constexpr CoreTypes::Color BROWN     {150,  75,   0, 255 };
    inline constexpr CoreTypes::Color SKY_BLUE  {135, 206, 235, 255 };

    // Map to store colors
    inline const std::unordered_map<std::string, CoreTypes::Color> COLOR_MAP = 
    {
        {"BLACK",    BLACK},
        {"WHITE",    WHITE},
        {"GRAY",     GRAY},
        {"RED",      RED},
        {"BLUE",     BLUE},
        {"ORANGE",   ORANGE},
        {"GREEN",    GREEN},
        {"DKGREEN",  DKGREEN},
        {"YELLOW",   YELLOW},
        {"MAGENTA",  MAGENTA},
        {"CYAN",     CYAN},
        {"BROWN",    BROWN},
        {"SKY_BLUE", SKY_BLUE}
    };


    // Target time interval for how often to update physics
    inline constexpr float PHYS_DT = 1.0f / 240.0f;

    // Max number of physics updates per rendering frame (prevent "spiral of death")
    inline constexpr int MAX_PHYS_STEPS = 5;

    // Default attributes for particle
    inline constexpr float PARTICLE_MASS = 0.1f;
    inline constexpr float PARTICLE_RADIUS = 6.0f/(2*PIXELS_PER_METER);  // equivalent to 6 pixel diameter
    inline constexpr float PARTICLE_MU = 0.1f;  // static and dynamic friction coefficient
    inline constexpr float PARTICLE_RESTITUTION = 0.5f;  // 0 no bounce, 1 fully elastic (no energy loss)

    // Grid for particle collision detection
    inline constexpr int CELL_SIZE = PARTICLE_RADIUS*2;
    inline constexpr int OFFSETS[9][2] = {
        { 0, 0}, { 1, 0}, {-1, 0},
        { 0, 1}, { 0,-1},
        { 1, 1}, { 1,-1}, {-1, 1}, {-1,-1}
    };

    // Solver iterations to help with stability of collision detection
    inline constexpr int SOLVER_ITERS = 20;

    // Constants for positional correction to prevent jitter
    inline constexpr float SLOP = 0.002f;
    inline constexpr float PCT = 0.3f;
    inline constexpr float CLAMP_PEN = 0.05f;
    inline constexpr float CLAMP_CORR = 0.02f;

    // Default gravity in meters per second squared
    inline constexpr float GRAV = -9.81f;

}

#endif
