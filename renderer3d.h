#pragma once
#include <SDL3/SDL.h>
#include "cube.h"
#include "camera.h"

void drawCube(SDL_Renderer* renderer, const Cube& cube, float angle, const Camera& camera, Vector3 cubePosition, SDL_Color cubeColour, Vector3 cubeScale = {1.0f, 1.0f, 1.0f});
