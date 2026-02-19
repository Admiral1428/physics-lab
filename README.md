# physics-lab
A modular 2D physics engine built in modern C++, featuring particle‑based fluids, rigid‑body dynamics, and planned GPU acceleration via custom CUDA kernels.

## Current Capabilities
* Cross‑platform build system using **CMake**
* Automated **Linux + Windows CI** using GitHub Actions
* Integrated **SDL3** rendering layer within clean, modular architecture
* Vendored **Eigen** library for linear algebra foundations
* Data‑driven initialization through a **JSON** scene input file defining particle properties and initial state
* Basic particle simulation with screen‑edge collision response using per-particle restitution and friction values
* **Impulse‑based particle–particle collision detection and resolution**, including positional correction and stability safeguards

## Planned Features
* Rigid‑body dynamics for convex polygons and constraints
* GPU acceleration of physics calculations using custom CUDA kernels
* Continuous delivery of build artifacts (Linux + Windows)

## Current Demo

https://github.com/user-attachments/assets/1c0a31d0-6d88-4872-83e9-d369f04a8cb7
