#include "projection.h"
#include <cmath>

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

    float cosYaw = std::cos(camera.yaw);
    float sinYaw = std::sin(camera.yaw);

    // rotate coord's horizontally 
    float yawX = relativeX * cosYaw - relativeZ * sinYaw;
    float yawZ = relativeX * sinYaw + relativeZ * cosYaw;

    float cosPitch = std::cos(camera.pitch);
    float sinPitch = std::sin(camera.pitch);

    //rotate coord's vertically
    float pitchY = relativeY *  cosPitch - yawZ * sinPitch;
    float pitchZ = relativeY * sinPitch + yawZ * cosPitch;


    const float nearPlane = 0.5f;

    if (pitchZ < nearPlane) {
        return false;
    }

    float scale = 300.0f / pitchZ;

    result.x = screenWidth / 2.0f + yawX * scale;
    result.y = screenHeight / 2.0f - pitchY * scale;
    return true;
}

bool projectLine(
    Vector3 start,
    Vector3 end,
    const Camera& camera,
    int screenWidth,
    int screenHeight,
    SDL_FPoint& screenStart,
    SDL_FPoint& screenEnd 
) { 
    const float nearPlane = 0.5f;

    auto toCameraSpace = [&](Vector3 point) {
        float x = point.x - camera.position.x;
        float y = point.y - camera.position.y;
        float z = point.z - camera.position.z;

        float cy = std::cos(camera.yaw);
        float sy = std::sin(camera.yaw);

        float cameraX = x * cy - z * sy;
        float cameraZ = x * sy + z * cy;

        float cp = std::cos(camera.pitch); 
        float sp = std::sin(camera.pitch);

        return Vector3{
            cameraX,
            y * cp - cameraZ * sp,
            y * sp + cameraZ * cp 
        };
    };

    Vector3 a = toCameraSpace(start);
    Vector3 b = toCameraSpace(end);

    if (a.z < nearPlane && b.z < nearPlane) {
        return false;
    }

    if (a.z < nearPlane || b.z < nearPlane) {
        float t = (nearPlane - a.z) / (b.z - a.z);

        Vector3 intersection = {
            a.x + t * (b.x - a.x),
            a.y + t * (b.y - a.y),
            nearPlane
        };

        if (a.z < nearPlane) {
            a = intersection;
        } else { 
            b = intersection;
        }
    }

    screenStart.x = screenWidth / 2.0f + a.x * 300.0f / a.z;
    screenStart.y = screenHeight / 2.0f - a.y * 300.0f / a.z;
    
    screenEnd.x = screenWidth / 2.0f + b.x * 300.0f / b.z;
    screenEnd.y = screenHeight / 2.0f - b.y * 300.0f / b.z;

    return true;
}

