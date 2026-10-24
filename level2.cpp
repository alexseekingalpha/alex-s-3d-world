#include "renderer3d.h"
#include "level2.h"
#include <SDL3/SDL.h>
#include "camera.h"

void drawLevel2(SDL_Renderer* renderer, const Camera& camera) {
    Cube cube; 

    float angle = 0.0f;
    Vector3 position = {0.0f, 0.0f, 5.0f};

    SDL_Color portalColour = {40, 130, 255, 255}; 

    drawCube(renderer, cube, angle, camera, position, portalColour);

    


}


