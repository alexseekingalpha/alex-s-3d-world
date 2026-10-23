#pragma once
#include <SDL3/SDL.h>

struct PlayerVelocity {
    float x = 0.0f;
    float y = 0.0f;
};

void movePlayer(SDL_FRect& player, const bool* keyboard, float speed, float deltaTime, PlayerVelocity& velocity);

