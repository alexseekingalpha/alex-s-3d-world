
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include "game.h"

#include <SDL3/SDL.h>
#include "player.h"
#include "renderer3d.h"
#include "camera.h"
#include "floor.h"
#include "level1.h"
#include "level2.h"
#include "level.h"
#include "collison.h"
#include <cmath>


SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    Game* game = new Game();
    *appstate = game;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_APP_FAILURE;
    }

    game->window = SDL_CreateWindow(
        "Alex's 3D World",
        1000,
        700,
        SDL_WINDOW_RESIZABLE
    );

    if (!game->window) {
        return SDL_APP_FAILURE;
    }

    game->renderer = SDL_CreateRenderer(game->window, nullptr);

    if (!game->renderer) {
        return SDL_APP_FAILURE;
    }

    SDL_SetWindowRelativeMouseMode(game->window, true);
    game->lastTime = SDL_GetTicks();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    Game* game = static_cast<Game*>(appstate);

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_MOUSE_MOTION) {
        float sensitivity = 0.003f;

        game->camera.yaw += event->motion.xrel * sensitivity;
        game->camera.pitch -= event->motion.yrel * sensitivity;

        if (game->camera.pitch > 1.5f)
            game->camera.pitch = 1.5f;

        if (game->camera.pitch < -1.5f)
            game->camera.pitch = -1.5f;
    }

    if (event->type == SDL_EVENT_KEY_DOWN &&
        event->key.scancode == SDL_SCANCODE_ESCAPE) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    Game* game = static_cast<Game*>(appstate);

    SDL_Renderer* renderer = game->renderer;
    Camera& camera = game->camera;
    int& currentLevel = game->currentLevel;

    Uint64 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - game->lastTime) / 1000.0f;
    game->lastTime = currentTime;

    game->cubeAngle += 1.0f * deltaTime;
    game->cubeAngle2 += 1.0f * deltaTime;

    float cameraSpeed = 3.0f;

    const bool* keyboard = SDL_GetKeyboardState(nullptr);

    float forwardX = std::sin(camera.yaw);
    float forwardZ = std::cos(camera.yaw);

    float rightX = std::cos(camera.yaw);
    float rightZ = -std::sin(camera.yaw);

    float moveX = 0.0f;
    float moveZ = 0.0f;

    if (keyboard[SDL_SCANCODE_W]) {
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

    if (keyboard[SDL_SCANCODE_S]) {
        moveX -= forwardX;
        moveZ -= forwardZ;
    }

    //normalise diag monement
    float moveLength = std::sqrt(moveX * moveX + moveZ * moveZ);

    if (moveLength > 0.0f) {
        moveX /= moveLength;
        moveZ /= moveLength;
    }

    Vector3 proposedPosition = camera.position;

    proposedPosition.x += moveX * cameraSpeed * deltaTime;
    proposedPosition.z += moveZ * cameraSpeed * deltaTime;

    WallCollider wall = {
        {0.0f, 0.0f, 3.0f},
        {10.0f, 3.0f, 0.25f}
    };

    if (!checkWallCollision(proposedPosition, wall)) {
        camera.position = proposedPosition;
    }

    Vector3 portalPosition = {0.0f, 0.0f, 5.0f};

    float dx = camera.position.x - portalPosition.x;
    float dz = camera.position.z - portalPosition.z;

    float distance = std::sqrt(dx * dx + dz * dz);

    if (distance < 1.5f) {
        if (currentLevel == 1) {
            currentLevel = 2;
            camera.position = {0.0f, 0.0f, -5.0f};
        }
        else if (currentLevel == 2) {
            currentLevel = 1;
            camera.position = {0.0f, 0.0f, -5.0f};
        }
    }

    //movePlayer(rectangle, keyboard, speed, deltaTime, velocity);

    Level levels[] = {
        {{25, 55, 95, 255}},
        {{130, 35, 45, 255}}
    };

    SDL_Color color = levels[currentLevel - 1].backgroundColor;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);

    //SDL_SetRenderDrawColor(renderer, 239, 156, 60, 255);
    //SDL_RenderFillRect(renderer, &rectangle);
    drawFloor(renderer, camera);

    // drawCube(renderer, cube, cubeAngle, camera, cubePosition);
    // drawCube(renderer, cube, 0.0f, camera,{0.0f, 0.0f, 8.0f} );

    if (currentLevel == 1) {
        drawLevel1(renderer, camera);
    }
    else if (currentLevel == 2) {
        drawLevel2(renderer, camera);
    }

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    Game* game = static_cast<Game*>(appstate);

    if (game) {
        if (game->renderer) {
            SDL_DestroyRenderer(game->renderer);
        }

        if (game->window) {
            SDL_DestroyWindow(game->window);
        }

        delete game;
    }

    SDL_Quit();
}
