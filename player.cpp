#include "player.h"

void movePLayer(SDL_FRect& player, const bool * keyboard, float speed, float deltaTime) {
    if (keyboard[SDL_SCANCODE_D]) {
        player.x += speed * deltaTime;
    }

}

