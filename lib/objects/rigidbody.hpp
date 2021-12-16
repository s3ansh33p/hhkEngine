/**
 * @file rigidbody.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Basic rigid body for the engine
 * @version 1.0
 * @date 2021-12-17
 * 
 * @code{cpp}
 * createRigidBody(10, 20, 0, 0, 0, 0, 0, 0, 4, 2, 2);  create a rigid body at 10,20, at 0 degrees
 *                                                      with no starting velocity / forces, 4x2 with
 *                                                      a mass of 2
 * 
 * renderRigidBodies();                                 render the rigid body
 * 
 * computeRigidBodies();                                compute the rigid body's new position / forces
 * 
 * removeRigidBody(3);                                  remove the rigid body with ID 3
 * @endcode
 */

#pragma once

#include "../environment.hpp"
#include "../../trig_functions.hpp"

int rigidBodyCount = 0;
int rigidBodyIDCounter = 0;

// 2D box shape. Physics engines usually have a couple different classes of shapes
// such as circles, spheres (3D), cylinders, capsules, polygons, polyhedrons (3D)...
typedef struct {
    int width;
    int height;
    int mass;
    int momentOfInertia;
} BoxShape;

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
} RigidBody;

// Global array of rigid bodies.
RigidBody rigidBodies[MAX_RIGIDBODIES];

class RigidBodyManager {
public:
    ~RigidBodyManager();

    void createRigidBody(int positionX, int positionY, int velocityX, int velocityY, int angle, int angularVelocity, int width, int height, int mass);
    void renderRigidBodies();
    void removeAllRigidBodies();
    void computeRigidBodyStep(int dt);
    void removeRigidBody(int rigidBodyId);
    RigidBody getRigidBody(int rigidBodyId);
};

// Calculates the inertia of a box shape and stores it in the momentOfInertia variable.
void CalculateBoxInertia(BoxShape *boxShape) {
    int m = boxShape->mass;
    int w = boxShape->width;
    int h = boxShape->height;
    boxShape->momentOfInertia = m * (w * w + h * h) / 12;
}

void RigidBodyManager::renderRigidBodies() {
    for (int i = 0; i < rigidBodyCount; i++) {
        RigidBody *rigidBody = &rigidBodies[i];
        // check if the rigid body is visible
        if (rigidBody->position.x > 0 && rigidBody->position.x < width && rigidBody->position.y > 0 && rigidBody->position.y < height) {

            // Draw a line from the position of the body to itself rotated by the angle.
            line(rigidBody->position.x, rigidBody->position.y, rigidBody->position.x + COS(rigidBody->angle, rigidBody->shape.height), rigidBody->position.y + SIN(rigidBody->angle, rigidBody->shape.height), color(255, 255, 255));

            Debug_Printf(8,26 + i,true,0,"[%i] p(%i, %i) a = %i, i = %i, t = %i", i, rigidBody->position.x, rigidBody->position.y, rigidBody->angle, rigidBody->shape.momentOfInertia, rigidBody->torque);

        }
    }
}

// Create a rigidbody given a position, velocity, angle, angular velocity, and shape.
void RigidBodyManager::createRigidBody(int positionX, int positionY, int velocityX, int velocityY, int angle, int angularVelocity, int width, int height, int mass) {
    if (rigidBodyCount < MAX_RIGIDBODIES) {
        RigidBody *rigidBody = &rigidBodies[rigidBodyCount];
        rigidBody->id = rigidBodyIDCounter;
        rigidBodyIDCounter++;
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
void RigidBodyManager::removeRigidBody(int rigidBodyId) {
    if (rigidBodyId < rigidBodyCount) {
        for (int i = rigidBodyId; i < rigidBodyCount; i++) {
            rigidBodies[i] = rigidBodies[i + 1];
        }
        rigidBodyCount--;
    }
}

// Remove all rigid bodies from the array.
void RigidBodyManager::removeAllRigidBodies() {
    rigidBodyCount = 0;
}

// Get a rigid body from the array given an id.
RigidBody RigidBodyManager::getRigidBody(int rigidBodyId) {
    for (int i = 0; i < rigidBodyCount; i++) {
        if (rigidBodies[i].id == rigidBodyId) {
            return rigidBodies[i];
        }
    }
    // return an empty rigid body if doesn't exist with id of -1
    return {-1, Vector2{0, 0}, Vector2{0, 0}, 0, 0, Vector2{0, 0}, 0, BoxShape{0, 0, 0, 0}};
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
void RigidBodyManager::computeRigidBodyStep(int dt) {
    for (int i = 0; i < rigidBodyCount; i++) {
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
    }
}
