#include "renderer3d.h"
#include "level1.h"
#include <SDL3/SDL.h>
#include "camera.h"

void drawLevel1(SDL_Renderer* renderer, const Camera& camera) {
    Cube cube; 

    float angle = 0.0f;
    Vector3 position = {0.0f, 0.0f, 5.0f};
    SDL_Color portalColour = {255, 40, 40, 255};


    drawCube(renderer, cube, angle, camera, position, portalColour);

    SDL_Color wallColour = {0, 225, 0, 255};

    Vector3 wallPosition = {0.0f, 0.0f, 3.0f};
    Vector3 wallscale = {10.0f, 3.0f, 0.25f};

    drawCube(renderer, cube, 0.0f, camera, wallPosition, wallColour, wallscale);


}


