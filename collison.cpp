#include "collison.h"

#include <cmath>

bool checkWallCollision(Vector3 playerPosition, const WallCollider& wall) {
    float dx = std::abs(playerPosition.x - wall.position.x);
    float dz = std::abs(playerPosition.z - wall.position.z);

    return dx < wall.halfSize.x &&
    dz < wall.halfSize.z;
}