#pragma once
#include <SDL3/SDL.h>
#include "cube.h"
#include "camera.h"

void drawCube(SDL_Renderer* renderer, const Cube& cube, float angle, const Camera& camera, Vector3 cubePosition );
