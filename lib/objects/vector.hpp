/**
 * @file vector.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Vector struct and functions
 * @version 1.1
 * @date 2021-12-13
 */

// Two dimensional vector.
typedef struct {
    int x;
    int y;
} Vector2;

// Three dimensional vector.
typedef struct {
    int x;
    int y;
    int z;
} Vector3;

// Add 2D vectors.
Vector2 vector2_add(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

// Add 3D vectors.
Vector3 vector3_add(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

// Subtract 2D vectors.
Vector2 vector2_subtract(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

// Subtract 3D vectors.
Vector3 vector3_subtract(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

// Dot product of 2D vectors.
int vector2_dot(Vector2 a, Vector2 b) {
    return a.x * b.x + a.y * b.y;
}

// Dot product of 3D vectors.
int vector3_dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Cross product of 3D vectors.
Vector3 vector3_cross(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

// Scale 2D vector.
Vector2 vector2_scale(Vector2 a, int scale) {
    Vector2 result;
    result.x = a.x * scale;
    result.y = a.y * scale;
    return result;
}

// Scale 3D vector.
Vector3 vector3_scale(Vector3 a, int scale) {
    Vector3 result;
    result.x = a.x * scale;
    result.y = a.y * scale;
    result.z = a.z * scale;
    return result;
}
