#include <SDL3/SDL.h>
#include "player.h"
#include "renderer3d.h"
#include "camera.h"
#include "floor.h"
#include "level1.h"
#include "level2.h"
#include "level.h"
#include <cmath>

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
float cubeAngle2 = 0.0f;

int currentLevel = 1;

Level levels[] = {
    {{25, 55, 95, 255}},
    {{130, 35, 45, 255}}
};

SDL_SetWindowRelativeMouseMode(window, true);

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
    cubeAngle2 += 1.0f * deltaTime;

    while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
        running = false;
        }
        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            float sensitivity = 0.003f;

            camera.yaw += event.motion.xrel * sensitivity;
            camera.pitch -= event.motion.yrel * sensitivity;

            if (camera.pitch > 1.5f)
            camera.pitch = 1.5f;

            if(camera.pitch < -1.5f)
            camera.pitch = -1.5f;

        }

        if (event.type ==  SDL_EVENT_KEY_DOWN &&
        event.key.scancode == SDL_SCANCODE_ESCAPE) {
        running = false;
        }
    }
    
    float cameraSpeed = 3.0f;

    const bool * keyboard = SDL_GetKeyboardState(nullptr);

    float forwardX = std::sin(camera.yaw);
    float forwardZ = std::cos (camera.yaw);

    float rightX = std::cos(camera.yaw);
    float rightZ = -std::sin(camera.yaw);

    float moveX = 0.0f;
    float moveZ = 0.0f;

    if(keyboard[SDL_SCANCODE_W]) {
        moveX += forwardX;
        moveZ += forwardZ;

    }

    if (keyboard[SDL_SCANCODE_D]) {
        moveX += rightX;
        moveZ += rightZ;
    }

    if (keyboard[SDL_SCANCODE_A]) {
        moveX -= rightX;
        moveZ -= rightZ;
    }

    if(keyboard[SDL_SCANCODE_S]) {
        moveX -= forwardX;
        moveZ -= forwardZ;
        
    }

    //normalise diag monement
    float moveLength = std::sqrt(moveX * moveX + moveZ * moveZ);

    if (moveLength > 0.0f) {
        moveX /= moveLength;
        moveZ /= moveLength;
    }

    camera.position.x += moveX * cameraSpeed * deltaTime;
    camera.position.z += moveZ * cameraSpeed * deltaTime;

    Vector3 portalPosition = {0.0f, 0.0f, 5.0f};

    float dx = camera.position.x - portalPosition.x;
    float dz = camera.position.z - portalPosition.z;

    float distance = std::sqrt(dx * dx + dz * dz);

    if (distance < 1.5f) {
        if (currentLevel == 1 && distance < 1.5f) {
        currentLevel = 2;
        camera.position = {0.0f, 0.0f, -5.0f};
    }
    else if (currentLevel == 2) {
        currentLevel = 1;
        camera.position = {0.0f, 0.0f, -5.0f};
    }
        }         

    //movePlayer(rectangle, keyboard, speed, deltaTime, velocity);


        SDL_Color color = levels[currentLevel -1].backgroundColor;

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderClear(renderer);

        //SDL_SetRenderDrawColor(renderer, 239, 156, 60, 255);
        //SDL_RenderFillRect(renderer, &rectangle);
        drawFloor(renderer, camera);

        Vector3 cubePosition = {5.0f, 0.0f, 0.0f};

       // drawCube(renderer, cube, cubeAngle, camera, cubePosition);
       // drawCube(renderer, cube, 0.0f, camera,{0.0f, 0.0f, 8.0f} );

       if (currentLevel == 1) {
            drawLevel1(renderer, camera);
       }
       else if (currentLevel == 2) {
            drawLevel2(renderer, camera);
       }

        SDL_RenderPresent(renderer);
    }

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}