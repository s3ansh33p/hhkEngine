/**
 * @file particle.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Basic particle for the engine
 * @version 1.0
 * @date 2021-12-12
 * 
 * @code{cpp}
 * // run the simulation - will need to make a nice way to add particles and render them etc.
 * RunSimulation();
 * @endcode
 */

#pragma once

#include "environment.hpp"

int particleCount = 0;

// Two dimensional particle.
typedef struct {
    Vector2 position;
    Vector2 velocity;
    int mass;
} Particle;

// Global array of particles.
Particle particles[MAX_PARTICLES];

void renderParticles() {
    for (int i = 0; i < particleCount; ++i) {
        Particle *particle = &particles[i];
        setPixel(particle->position.x, particle->position.y, color(255, 0, 0));
    }
}

// Create a particle given a position, velocity and mass.
void createParticle(int x, int y, int vx, int vy, int mass) {
    particles[particleCount].position = (Vector2){x, y};
    particles[particleCount].velocity = (Vector2){vx, vy};
    particles[particleCount].mass = mass;
    particleCount++;
}

// Just applies Earth's gravity force (mass times gravity acceleration 9.81 m/s^2) to each particle. approximated to 10 m/s^2 as can;t use floats
Vector2 ComputeForce(Particle *particle) {
    return (Vector2){0, particle->mass * 10};
}

void computeParticleStep(int dt) {
    for (int i = 0; i < particleCount; ++i) {
        Particle *particle = &particles[i];
        Vector2 force = ComputeForce(particle);
        Vector2 acceleration = (Vector2){force.x / particle->mass, force.y / particle->mass};
        particle->velocity.x += acceleration.x * dt;
        particle->velocity.y += acceleration.y * dt;
        particle->position.x += particle->velocity.x * dt;
        particle->position.y += particle->velocity.y * dt;
        Debug_Printf(8,5 + i,true,0,"[%i] p(%i, %i) v(%i, %i)", i, particle->position.x, particle->position.y, particle->velocity.x, particle->velocity.y);
    }
}
