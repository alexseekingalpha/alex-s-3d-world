#include "player.h"
#include <cmath>    

void movePlayer(SDL_FRect& player, const bool * keyboard, float speed, float deltaTime, PlayerVelocity& velocity) {

    float acceleration = 300.0f;
    float friction = 2.0f;

    float inputX = 0.0f;
    float inputY = 0.0f;

    if (keyboard[SDL_SCANCODE_D]) inputX += 1.0f;
    if (keyboard[SDL_SCANCODE_A]) inputX -= 1.0f;
    if (keyboard[SDL_SCANCODE_W]) inputY -= 1.0f;
    if (keyboard[SDL_SCANCODE_S]) inputY += 1.0f;

    float length = std::sqrt(inputX * inputX + inputY * inputY); //length of movement direction

    if (length > 0.0f) {  //normalise it so diagonal is not faster 
        inputX /= length;
        inputY /= length;
    }

    velocity.x += inputX * acceleration * deltaTime;  //apply accelerartion 
    velocity.y += inputY * acceleration * deltaTime;  // ^^
 
    float damping = 1.0f / (1.0f + friction * deltaTime);

    velocity.x *= damping;
    velocity.y *= damping;

    player.x += velocity.x * deltaTime;
    player.y += velocity.y *  deltaTime;

}

