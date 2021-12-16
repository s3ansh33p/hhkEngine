/**
 * @file renderer.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Renderer for the engine
 * @version 1.0
 * @date 2021-12-16
 */

#pragma once

#include "objects/particle.hpp"
#include "objects/rigidbody.hpp"
#include "objects/rectangle.hpp"
#include "../calc.hpp"

class Renderer {
    public:
    
    int x = 0;              // x position of the renderer
    int y = 0;              // y position of the renderer
    int width = 0;          // width of the window
    int height = 0;         // height of the window
    int currentTime = 0;    // current time of the renderer
    int deltaTime = 1;      // time (in seconds) for each step
	ParticleManager *particleManager = new ParticleManager();
    RigidBodyManager *rigidBodyManager = new RigidBodyManager();
    RectangleManager *rectangleManager = new RectangleManager();

    /**
     * Create a new renderer
     * 
     * @param x,y The coordinates to print the formatted string at.
     * @param width The width of the renderer
     * @param height The height of the renderer
     */
    Renderer(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;    
        this->rectangleManager->setRenderDimensions(x, y, width, height);
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
        return this->width;
    }

    int getHeight() {
        return this->height;
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
        Debug_Printf(4,40,true,0,"Renderer (%i, %i) %ix%i", this->x, this->y, this->width, this->height);

        // Outline renderer
        line(this->x,this->y,this->x + this->width,this->y,color(255,255,0));
        line(this->x,this->y + this->height,this->x + this->width,this->y + this->height,color(255,255,0));
        line(this->x,this->y,this->x,this->y + this->height,color(255,255,0));
        line(this->x + width,this->y,this->x + this->width,this->y + this->height,color(255,255,0));
    };

};


