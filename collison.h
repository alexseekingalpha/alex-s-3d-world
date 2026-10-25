#pragma once

#include "vector3.h"

struct WallCollider {
    Vector3 position;
    Vector3 halfSize;
};

bool checkWallCollision(Vector3 playerPosition, const WallCollider& wall);