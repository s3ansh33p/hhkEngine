/**
 * @file particle.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Basic particle for the engine
 * @version 1.0
 * @date 2021-12-29
 * 
 * @code{cpp}
 * 
 * createParticle(10, 20, 0, 0, 2);     create a particle at 10,20, with no starting
*                                       velocity, and with a mass of 2
 * 
 * renderParticles();                   render all particles
 * 
 * computeParticles();                  compute all particles next step
 * 
 * removeParticle(3);                   remove the particle with ID 3
 * @endcode
 */

#pragma once

#include "entity.hpp"

class Particle: public Entity {
    public: 
        Vector2 velocity;
        int mass;

        void create(int x, int y, int vx, int vy, int mass, int color);
        void render(int dt, int rendererX, int rendererY, int rendererWidth, int rendererHeight);
        void computeStep(int dt);
        Vector2 computeForce();
        void remove();
};

void Particle::render(int dt, int rendererX, int rendererY, int rendererWidth, int rendererHeight) {
    this->computeStep(dt);
    if (this->x > rendererX && this->x < rendererX + rendererWidth && this->y > rendererY && this->y < rendererY + rendererHeight) {
        // draw the particle
        setPixel(this->x, this->y, this->color);

        // Debug_Printf(8,30 + this->id,true,0,"[%i] p(%i, %i) v(%i, %i)", this->id, this->x, this->y, this->velocity.x, this->velocity.y);
    }
}

// Create a particle given a position, velocity, mass and color
void Particle::create(int x, int y, int vx, int vy, int mass, int color) {
    this->createEnt(x, y, color, 1);
    this->x = x;
    this->y = y;
    this->velocity = Vector2{vx, vy};
    this->mass = mass;
    this->color = color;
}

// Just applies Earth's gravity force (mass times gravity acceleration 9.81 m/s^2) to each particle. approximated to 10 m/s^2 as can;t use floats
Vector2 Particle::computeForce() {
    return Vector2{0, this->mass * GRAVITY};
}

// Compute the next step for the particle
void Particle::computeStep(int dt) {
    Vector2 force = this->computeForce();
    Vector2 acceleration = Vector2{force.x / this->mass, force.y / this->mass};
    this->velocity.x += acceleration.x * dt;
    this->velocity.y += acceleration.y * dt;
    this->x += this->velocity.x * dt;
    this->y += this->velocity.y * dt;
}

void Particle::remove() {
	this->hasUpdate = true;
	// this->tileChecks(); // tba
    this->removeEnt();
}