#include "projection.h"

bool projectPoint( 
    const Vector3& point,
    const Camera& camera,
    int screenWidth,
    int screenHeight,
    SDL_FPoint& result
) {
    float relativeX = point.x - camera.position.x;
    float relativeY = point.y - camera.position.y;
    float relativeZ = point.z - camera.position.z;

    const float nearPlane = 0.1f;

    if (relativeZ <= nearPlane){
        return false;
    }

    float scale = 300.0f / relativeZ;

    result.x = screenWidth / 2.0f + relativeX * scale;
    result.y = screenHeight / 2.0f - relativeY * scale;

    return true;
}

