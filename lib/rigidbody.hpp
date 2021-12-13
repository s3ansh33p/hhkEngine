/**
 * @file rigidbody.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Basic rigid body for the engine
 * @version 1.0
 * @date 2021-12-12
 * 
 * @code{cpp}
 * // create a rigid body at 10,20, at 0 degrees with no starting velocity / forces, 4x2 with mass 2
 * createRigidBody(10, 20, 0, 0, 0, 0, 0, 0, 4, 2, 2);
 * // render the rigid body
 * renderRigidBodies();
 * // compute the rigid body's new position / forces
 * computeRigidBodies();
 * // render the rigid body
 * renderRigidBodies();
 * @endcode
 */

#pragma once

#include "environment.hpp"
#include "../trig_functions.hpp"

int rigidBodyCount = 0;

// 2D box shape. Physics engines usually have a couple different classes of shapes
// such as circles, spheres (3D), cylinders, capsules, polygons, polyhedrons (3D)...
typedef struct {
    int width;
    int height;
    int mass;
    int momentOfInertia;
} BoxShape;

// Calculates the inertia of a box shape and stores it in the momentOfInertia variable.
void CalculateBoxInertia(BoxShape *boxShape) {
    int m = boxShape->mass;
    int w = boxShape->width;
    int h = boxShape->height;
    boxShape->momentOfInertia = m * (w * w + h * h) / 12;
}

// Two dimensional rigid body
typedef struct {
    int id;
    Vector2 position;
    Vector2 linearVelocity;
    uint16_t angle;
    int angularVelocity;
    Vector2 force;
    int torque;
    BoxShape shape;
    int getID() { return id; }
} RigidBody;

// Global array of rigid bodies.
RigidBody rigidBodies[MAX_RIGIDBODIES];

void renderRigidBodies() {
    for (int i = 0; i < rigidBodyCount; ++i) {
        RigidBody *rigidBody = &rigidBodies[i];
        // Draw a line from the position of the body to itself rotated by the angle.
        line(rigidBody->position.x, rigidBody->position.y, rigidBody->position.x + COS(rigidBody->angle, rigidBody->shape.height), rigidBody->position.y + SIN(rigidBody->angle, rigidBody->shape.height), color(255, 255, 255));
    }
}

// Create a rigidbody given a position, velocity, angle, angular velocity, and shape.
void createRigidBody(int positionX, int positionY, int velocityX, int velocityY, int angle, int angularVelocity, int forceX, int forceY, int width, int height, int mass) {
    if (rigidBodyCount < MAX_RIGIDBODIES) {
        RigidBody *rigidBody = &rigidBodies[rigidBodyCount];
        rigidBody->id = rigidBodyCount;
        rigidBody->position = Vector2{positionX, positionY};
        rigidBody->linearVelocity = Vector2{velocityX, velocityY};
        rigidBody->angle = angle;
        rigidBody->angularVelocity = angularVelocity;

        BoxShape shape;
        shape.width = width;
        shape.height = height;
        shape.mass = mass;

        CalculateBoxInertia(&shape);
        rigidBody->shape = shape;
        rigidBodyCount++;
    }
}

// Remove a rigid body from the array.
void removeRigidBody(int rigidBodyId) {
    if (rigidBodyId < rigidBodyCount) {
        for (int i = rigidBodyId; i < rigidBodyCount; ++i) {
            rigidBodies[i] = rigidBodies[i + 1];
        }
        rigidBodyCount--;
    }
}

// Remove all rigid bodies from the array.
void removeAllRigidBodies() {
    rigidBodyCount = 0;
}

// Applies a force at a point in the body, inducing some torque.
void ComputeForceAndTorque(RigidBody *rigidBody) {
    Vector2 f = Vector2{2, 4};
    rigidBody->force = f;
    // r is the 'arm vector' that goes from the center of mass to the point of force application
    Vector2 r = Vector2{rigidBody->shape.width / 2, rigidBody->shape.height / 2};
    rigidBody->torque = r.x * f.y - r.y * f.x;
}

// Computes the new position and velocity of the rigidbodies given a time step.
void computeRigidBodyStep(int dt) {
    for (int i = 0; i < rigidBodyCount; ++i) {
        RigidBody *rigidBody = &rigidBodies[i];
        ComputeForceAndTorque(rigidBody);
        Vector2 linearAcceleration = Vector2{rigidBody->force.x / rigidBody->shape.mass, rigidBody->force.y / rigidBody->shape.mass};
        rigidBody->linearVelocity.x += linearAcceleration.x * dt;
        rigidBody->linearVelocity.y += linearAcceleration.y * dt;
        rigidBody->position.x += rigidBody->linearVelocity.x * dt;
        rigidBody->position.y += rigidBody->linearVelocity.y * dt;
        int angularAcceleration = rigidBody->torque / rigidBody->shape.momentOfInertia;
        rigidBody->angularVelocity += angularAcceleration * dt;
        rigidBody->angle += rigidBody->angularVelocity * dt;
        if (rigidBody->angle > 360) {
            rigidBody->angle -= 360;
        }
        Debug_Printf(8,5 + i,true,0,"[%i] p(%i, %i) a = %i, i = %i, t = %i", i, rigidBody->position.x, rigidBody->position.y, rigidBody->angle, rigidBody->shape.momentOfInertia, rigidBody->torque);
    }
}
