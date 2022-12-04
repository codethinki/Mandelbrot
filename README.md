# Mandelbrot
Mandelbrot set using the Vulkan API

Controls:
* w-a-s-d (side to side movement)
* scroll (zoom +/-)
* left/right mouse (more/less detail)

Precompiled Binarys:
* ensure .exe and shaders folder are in the same dir
* Lag and blurry image are float/double overflow problems i'll fix that at some point

:)

# Repo cloning

Requirements:
* Vulkan sdk
* glm
* GLFW3
* C++ 20 or above (may be lower didn't test that)

Hardcoded paths to change:
* in the Vert_Frag_Compiler.bat -> path to local glsl compiler
* in main.cpp -> path to the Vert_Frag_Compiler.bat

