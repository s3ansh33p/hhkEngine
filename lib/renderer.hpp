/**
 * @file renderer.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Renderer for the engine
 * @version 1.0
 * @date 2021-12-16
 */

#pragma once

#include "objects/entityManager.hpp"
#include "objects/particle.hpp"
#include "objects/rigidbody.hpp"
#include "objects/rectangle.hpp"
#include "../calc.hpp"

class Renderer {
    public:
    
    int rendererX = 0;      // x position of the renderer
    int rendererY = 0;      // y position of the renderer
    int rendererWidth = 0;  // width of the window
    int rendererHeight = 0; // height of the window
    int currentTime = 0;    // current time of the renderer
    int deltaTime = 1;      // time (in seconds) for each step
	ParticleManager *particleManager = new ParticleManager();
    RigidBodyManager *rigidBodyManager = new RigidBodyManager();

    /**
     * Create a new renderer
     * 
     * @param x,y The coordinates to print the formatted string at.
     * @param width The width of the renderer
     * @param height The height of the renderer
     */
    Renderer(int x, int y, int width, int height) {
        this->rendererX = x;
        this->rendererY = y;
        this->rendererWidth = width;
        this->rendererHeight = height;    
    }

    // Time functions
    void setCurrentTime(int currentTime) {
        this->currentTime = currentTime;
    }

    void setDeltaTime(int deltaTime) {
        this->deltaTime = deltaTime;
    }

    int getCurrentTime() {
        return this->currentTime;
    }

    // Dimensions functions
    int getWidth() {
        return this->rendererWidth;
    }

    int getHeight() {
        return this->rendererHeight;
    }

    // Render function
    void render() {

        this->currentTime += this->deltaTime;
        
        // Compute current step

        // check if we need to render rigidbodies
        // will need to check if the rigidbody is in the bounds of the renderer
        if (rigidBodyCount > 0) {
            this->rigidBodyManager->computeRigidBodyStep(this->deltaTime);
            this->rigidBodyManager->renderRigidBodies();
        }

        // check if we need to render particles
        if (particleCount > 0) {
            this->particleManager->computeParticleStep(this->deltaTime);
            this->particleManager->renderParticles();
        }

        // Tmp
        Debug_Printf(4,40,true,0,"Renderer (%i, %i) %ix%i", this->rendererX, this->rendererY, this->rendererWidth, this->rendererHeight);

        // Outline renderer
        line(this->rendererX, this->rendererY, this->rendererX, this->rendererY + this->rendererHeight, color(255,255,0));
        line(this->rendererX, this->rendererY, this->rendererX + this->rendererWidth, this->rendererY, color(255,255,0));
        line(this->rendererX + this->rendererWidth, this->rendererY, this->rendererX + this->rendererWidth, this->rendererY + this->rendererHeight, color(255,255,0));
        line(this->rendererX, this->rendererY + this->rendererHeight, this->rendererX + this->rendererWidth, this->rendererY + this->rendererHeight, color(255,255,0));
    };

};


