#include "player.h"

void movePlayer(SDL_FRect& player, const bool * keyboard, float speed, float deltaTime) {
    if (keyboard[SDL_SCANCODE_D]) {
        player.x += speed * deltaTime;
    }

    if (keyboard[SDL_SCANCODE_A]) {
        player.x -= speed * deltaTime;
    }

    if (keyboard[SDL_SCANCODE_W]) {
        player.y -= speed * deltaTime;
    }

    if (keyboard[SDL_SCANCODE_S]) {
        player.y += speed * deltaTime;
    }

}

