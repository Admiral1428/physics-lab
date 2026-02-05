cmake_minimum_required(VERSION 3.20)
project(PhysicsLabEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL3
find_package(SDL3 CONFIG REQUIRED)

# Find Eigen (system-installed)
find_package(Eigen3 REQUIRED)

# Add include directory
include_directories(include)

# Collect all source files
file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)

add_executable(PhysicsLab ${ENGINE_SOURCES})

# Link SDL3
target_link_libraries(PhysicsLab PRIVATE SDL3::SDL3)

# Link Eigen
target_link_libraries(PhysicsLab PRIVATE Eigen3::Eigen)
