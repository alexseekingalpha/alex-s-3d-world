#pragma once
#include <cmath>

struct Vector3 {
    float x;
    float y;
    float z;
};
 
inline float dotProduct(Vector3 a, Vector3 b){ 
    return a.x*b.x + a.y*b.y + a.z*b.z; 
}

inline Vector3 normalize(Vector3 v) {
    float length = std::sqrt(v.x * v.x + v.y * v.y + v. z* v.z);

    return {
        v.x / length,
        v.y / length,
        v.z / length
    };
}

inline Vector3 subtract(Vector3 a, Vector3 b) {
    return{
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

inline Vector3 crossProduct(Vector3 a, Vector3 b) {
    return {
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x
    };
}