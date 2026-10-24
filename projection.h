#pragma once

#include "vector3.h"
#include "camera.h"
#include <SDL3/SDL.h>

bool projectPoint(
    const Vector3& point,
    const Camera& camera,
    int screenWidth,
    int screenHeight,
    SDL_FPoint& result 
);