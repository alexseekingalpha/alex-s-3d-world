#include "renderer3d.h"
#include <cmath>

void drawCube(SDL_Renderer* renderer, const Cube& cube, float angle, const Camera& camera) {

    float screenX[8];
    float screenY[8];
    bool visible[8];

    int width, height;
    SDL_GetRenderOutputSize(renderer, &width, &height);

    for (int i = 0; i < 8; i++) {
        Vector3 vertex = cube.vertices[i];

        float rotatedX = vertex.x * std::cos(angle) - vertex.z * std::sin(angle);
        float rotatedZ = vertex.x * std::sin(angle) + vertex.z * std::cos(angle);

        float relativeX = rotatedX - camera.position.x;
        float relativeY = vertex.y - camera.position.y;
        float relativeZ = rotatedZ - camera.position.z;

        visible[i] = relativeZ > 0.1f;

        if (!visible[i]) {
            continue;
        }

        float scale = 300.0f / relativeZ;

        screenX[i] = width / 2.0f + relativeX * scale;
        screenY[i] = height / 2.0f - relativeY * scale;
    
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < 12; i++) {
        int start = cube.edges[i][0];
        int end = cube.edges[i][1];

    if(!visible[start] || !visible[end]) {
        continue;
    }

        SDL_RenderLine(
            renderer,
            screenX[start], screenY[start],
            screenX[end], screenY[end]
        );
    }
}