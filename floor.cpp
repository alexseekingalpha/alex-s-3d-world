#include "floor.h"
#include "projection.h"

void drawFloor(SDL_Renderer* renderer, const Camera& camera){

    int width, height;
    SDL_GetRenderOutputSize(renderer, &width, &height);

    float groundY = -2.0f;

    SDL_SetRenderDrawColor(renderer, 90, 120, 150, 255);

    float gridSize = 20.0f;
    float spacing = 1.0f;
    float nearPlane = 0.1f;

    // Draws lines runnign forwards and backwards 
    for (float x = -gridSize; x <= gridSize; x += spacing) {

        Vector3 start = {x, groundY, camera.position.z + nearPlane + 0.01f};
        Vector3 end = {x, groundY, camera.position.z + 30.0f};

        SDL_FPoint screenStart;
        SDL_FPoint screenEnd;

        bool startVisible = projectPoint(
            start, camera, width, height, screenStart
        );

        bool endVisible = projectPoint(
            end, camera, width, height, screenEnd
        );

        if (startVisible && endVisible) {
            SDL_RenderLine(
                renderer,
                screenStart.x, screenStart.y,
                screenEnd.x, screenEnd.y 
            );
        }

    }

    //lines left and right 
    for (float z = -gridSize; z <= gridSize; z += spacing) {

        Vector3 start = {-gridSize, groundY, z};
        Vector3 end = {gridSize, groundY, z};

        SDL_FPoint screenStart;
        SDL_FPoint screenEnd;

        bool startVisible = projectPoint(
            start, camera, width, height, screenStart
        );

        bool endVisible = projectPoint(
            end, camera, width, height, screenEnd
        );

        if (startVisible && endVisible) {
            SDL_RenderLine( 
                renderer, 
                screenStart.x, screenStart.y,
                screenEnd.x, screenEnd.y 
            );
        };
        
    }

}