#include <SDL3/SDL.h>
#include "player.h"
#include "renderer3d.h"
#include "camera.h"
#include "floor.h"

int main () { 
    if (!SDL_Init(SDL_INIT_VIDEO)){
        return 1;
    }
SDL_Window* window = SDL_CreateWindow(
    "Alex's 3D World",
    1000,
    700,
    SDL_WINDOW_RESIZABLE
);
if (!window) {
    return 1;
}
SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
if (!renderer) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}
SDL_FRect rectangle = {100, 100, 200, 150};
Cube cube;
Camera camera;
float cubeAngle = 0.0f;

bool running = true;

SDL_Event event; 

float speed = 200.0f;
PlayerVelocity velocity;

Uint64 lastTime = SDL_GetTicks();

while (running) {
    Uint64 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    cubeAngle += 1.0f * deltaTime;

    while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
        running = false;
        }
    }
    
    float cameraSpeed = 3.0f;

    const bool * keyboard = SDL_GetKeyboardState(nullptr);

    if (keyboard[SDL_SCANCODE_W])
        camera.position.z += cameraSpeed * deltaTime;

    if (keyboard[SDL_SCANCODE_S])
        camera.position.z -= cameraSpeed * deltaTime;

    if (keyboard[SDL_SCANCODE_A])
        camera.position.x -= cameraSpeed * deltaTime;
    
    if (keyboard[SDL_SCANCODE_D])
        camera.position.x += cameraSpeed * deltaTime;
        

    //movePlayer(rectangle, keyboard, speed, deltaTime, velocity);


        SDL_SetRenderDrawColor(renderer, 25, 55, 95, 255);
        SDL_RenderClear(renderer);

        //SDL_SetRenderDrawColor(renderer, 239, 156, 60, 255);
        //SDL_RenderFillRect(renderer, &rectangle);
        drawFloor(renderer, camera);
        drawCube(renderer, cube, cubeAngle, camera);

        SDL_RenderPresent(renderer);
    }

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}