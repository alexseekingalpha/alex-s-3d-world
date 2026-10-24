#include "renderer3d.h"
#include <cmath>
#include "projection.h"

void drawCube(SDL_Renderer* renderer, const Cube& cube, float angle, const Camera& camera) {

    SDL_FPoint screenPoints[8];
    bool visible[8];

    int width, height;
    SDL_GetRenderOutputSize(renderer, &width, &height);

    for (int i = 0; i < 8; i++) {
        Vector3 vertex = cube.vertices[i];

        float rotatedX = vertex.x * std::cos(angle) - vertex.z * std::sin(angle);
        float rotatedZ = vertex.x * std::sin(angle) + vertex.z * std::cos(angle);

        Vector3 rotatedVertex = {
            rotatedX,
            vertex.y,
            rotatedZ
        };

        visible[i] = projectPoint(
            rotatedVertex,
            camera,
            width,
            height,
            screenPoints[i]
        );
    
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
            screenPoints[start].x,
            screenPoints[start].y,
            screenPoints[end].x,
            screenPoints[end].y
        );
    };
}