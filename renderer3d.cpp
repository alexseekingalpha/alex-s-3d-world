#include "renderer3d.h"
#include <cmath>

void drawCube(SDL_Renderer* renderer, const Cube& cube, float angle) {

    float screenX[8];
    float screenY[8];

    int width, height;
    SDL_GetRenderOutputSize(renderer, &width, &height);

    for (int i = 0; i < 8; i++) {
        Vector3 vertex = cube.vertices[i];

        float rotatedX = vertex.x * std::cos(angle) + vertex.z * std::sin(angle);
        float rotatedZ = vertex.x * std::sin(angle) + vertex.z * std::cos(angle);

        float distance = rotatedZ + 5.0f;
        float scale = 300.0f / distance;

        screenX[i] = width / 2.0f + rotatedX * scale;
        screenY[i] = height / 2.0f - vertex.y * scale;
    
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < 12; i++) {
        int start = cube.edges[i][0];
        int end = cube.edges[i][1];

        SDL_RenderLine(
            renderer,
            screenX[start], screenY[start],
            screenX[end], screenY[end]
        );
    }
}