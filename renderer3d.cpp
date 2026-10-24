#include "renderer3d.h"
#include <cmath>
#include "projection.h"
#include <algorithm>
#include <numeric> 

void drawCube(SDL_Renderer* renderer, const Cube& cube, float angle, const Camera& camera, Vector3 cubePosition, SDL_Color cubeColour) {

    SDL_FPoint screenPoints[8];
    bool visible[8];

    Vector3 worldPoints[8];

    float depths[8];

    int width, height;
    SDL_GetRenderOutputSize(renderer, &width, &height);

    for (int i = 0; i < 8; i++) {
        Vector3 vertex = cube.vertices[i];

        float rotatedX = vertex.x * std::cos(angle) - vertex.z * std::sin(angle);
        float rotatedZ = vertex.x * std::sin(angle) + vertex.z * std::cos(angle);

        Vector3 rotatedVertex = {
            rotatedX + cubePosition.x,
            vertex.y + cubePosition.y,
            rotatedZ + cubePosition.z

        };

        worldPoints[i] = rotatedVertex;

        float relativeX = rotatedVertex.x - camera.position.x;
        float relativeY = rotatedVertex.y - camera.position.y;
        float relativeZ = rotatedVertex.z - camera.position.z;

        float yawZ = relativeX * std::sin(camera.yaw)
        + relativeZ * std::cos(camera.yaw);

        depths[i] = relativeY * std::sin(camera.pitch)
                    + yawZ * std::cos(camera.pitch);

        visible[i] = projectPoint(
            rotatedVertex,
            camera,
            width,
            height,
            screenPoints[i]
        );
    
    }

    int triangleOrder[12];

    std::iota(triangleOrder, triangleOrder + 12, 0);

    std::sort(triangleOrder, triangleOrder + 12, [&](int first, int second) {
        auto averageDepth = [&](int triangleIndex) {
            int a = cube.triangles[triangleIndex][0];
            int b = cube.triangles[triangleIndex][1];
            int c = cube.triangles[triangleIndex][2];

            return (depths[a] + depths[b] + depths[c]) / 3.0f;
        };
        
        return averageDepth(first) > averageDepth(second);
    });

    // coloured triangles
    for (int i = 0; i < 12; i++) {
        int triangleIndex = triangleOrder[i];

        int a = cube.triangles[triangleIndex][0];
        int b = cube.triangles[triangleIndex][1];
        int c = cube.triangles[triangleIndex][2];

    if(!visible[a] || !visible[b] || !visible[c]) {
        continue;
    }

    Vector3 edge1 = subtract(worldPoints[b], worldPoints[a]);
    Vector3 edge2 = subtract(worldPoints[c], worldPoints[a]);

    Vector3 normal = normalize(crossProduct(edge1, edge2));
    Vector3 lightDirection = normalize({1.0f, 1.0f, -1.0f});

    float intensity = std::max(0.0f, dotProduct(normal, lightDirection));

    float abX = screenPoints[b].x - screenPoints[a].x;
    float abY = screenPoints[b].y - screenPoints[a].y;

    float acX = screenPoints[c].x - screenPoints[a].x;
    float acY = screenPoints[c].y - screenPoints[a].y;

    float signedArea = abX * acY - abY * acX;

    if (signedArea >= 0.0f) {
        continue;
    }

    float brightness = 0.2f + intensity * 0.8f;

    SDL_FColor colour = {
        (cubeColour.r / 255.0f) * brightness,
        (cubeColour.g / 255.0f) * brightness,
        (cubeColour.b / 255.0f) * brightness,
        cubeColour.a / 255.0f
    };

    SDL_Vertex triangle[3] = {
        {screenPoints[a], colour, {0.0f, 0.0f}},
        {screenPoints[b], colour, {0.0f, 0.0f}},
        {screenPoints[c], colour, {0.0f, 0.0f}}
    };

    SDL_RenderGeometry(renderer, nullptr, triangle, 3, nullptr, 0);

    }
    
    return;

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