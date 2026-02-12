#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <string>
#include <vector>
#include "physics/Particle.hpp"

std::vector<Particle> loadParticles(const std::string& filename);

#endif