/**
 * @file rigidbody.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Basic rigid body for the engine
 * @version 1.0
 * @date 2021-12-29
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

#include "entity.hpp"
#include "../../trig_functions.hpp"

// 2D box shape. Physics engines usually have a couple different classes of shapes
// such as circles, spheres (3D), cylinders, capsules, polygons, polyhedrons (3D)...
typedef struct {
    int width;
    int height;
    int mass;
    int momentOfInertia;
} BoxShape;

class RigidBody: public Entity {
    public:
        Vector2 linearVelocity;
        uint16_t angle;
        int angularVelocity;
        Vector2 force;
        int torque;
        BoxShape shape;

        void create(int x, int y, int vx, int vy, int angle, int av, int width, int height, int mass, int color);
        void render(int dt, int rendererX, int rendererY, int rendererWidth, int rendererHeight);
        void computeStep(int dt);
        void computeForceAndTorque();
        void remove();
};

// Calculates the inertia of a box shape and stores it in the momentOfInertia variable.
void CalculateBoxInertia(BoxShape *boxShape) {
    int m = boxShape->mass;
    int w = boxShape->width;
    int h = boxShape->height;
    boxShape->momentOfInertia = m * (w * w + h * h) / 12;
}

void RigidBody::render(int dt, int rendererX, int rendererY, int rendererWidth, int rendererHeight) {
    computeStep(dt);
    if (this->x > rendererX && this->x < rendererX + rendererWidth && this->y > rendererY && this->y < rendererY + rendererHeight) {

        // Draw a line from the position of the body to itself rotated by the angle.
        line(this->x, this->y, this->x + COS(this->angle, this->shape.height), this->y + SIN(this->angle, this->shape.height), this->color);

        // Debug_Printf(8,26 + this->id,true,0,"[%i] p(%i, %i) a = %i, i = %i, t = %i", this->id, this->x, this->y, this->angle, this->shape.momentOfInertia, this->torque);

    }
}

// Create a rigidbody given a position, velocity, angle, angular velocity, and shape.
void RigidBody::create(int x, int y, int vx, int vy, int angle, int av, int width, int height, int mass, int color) {
    this->createEnt(x, y, color, 2);
    this->x = x;
    this->y = y;
    this->linearVelocity = Vector2{vx, vy};
    this->angle = angle;
    this->angularVelocity = av;

    BoxShape shape;
    shape.width = width;
    shape.height = height;
    shape.mass = mass;

    CalculateBoxInertia(&shape);
    this->shape = shape;
}

// Applies a force at a point in the body, inducing some torque.
void RigidBody::computeForceAndTorque() {
    Vector2 f = Vector2{2, 4};
    this->force = f;
    // r is the 'arm vector' that goes from the center of mass to the point of force application
    Vector2 r = Vector2{this->shape.width / 2, this->shape.height / 2};
    this->torque = r.x * f.y - r.y * f.x;
}

// Computes the new position and velocity of the rigidbodies given a time step.
void RigidBody::computeStep(int dt) {
    this->computeForceAndTorque();
    Vector2 linearAcceleration = Vector2{this->force.x / this->shape.mass, this->force.y / this->shape.mass};
    this->linearVelocity.x += linearAcceleration.x * dt;
    this->linearVelocity.y += linearAcceleration.y * dt;
    this->x += this->linearVelocity.x * dt;
    this->y += this->linearVelocity.y * dt;
    int angularAcceleration = this->torque / this->shape.momentOfInertia;
    this->angularVelocity += angularAcceleration * dt;
    this->angle += this->angularVelocity * dt;
    if (this->angle > 360) {
        this->angle -= 360;
    }
}


void RigidBody::remove() {
	this->hasUpdate = true;
	// this->tileChecks(); // tba
    this->removeEnt();
}