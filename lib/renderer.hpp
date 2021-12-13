/**
 * @file renderer.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Renderer for the engine
 * @version 1.0
 * @date 2021-12-12
 */

#pragma once

#include "particle.hpp"
#include "rigidbody.hpp"
#include "../calc.hpp"

class Renderer {
    public:
    int x = 0;              // x position of the renderer
    int y = 0;              // y position of the renderer
    int width = 0;          // width of the window
    int height = 0;         // height of the window
    int currentTime = 0;    // current time of the renderer
    int deltaTime = 1;      // time (in seconds) for each step

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

        // Outline renderer
        line(this->x,this->y,this->x + this->width-1,this->y,color(255,255,0));
        line(this->x,this->y + this->height-1,this->x + this->width-1,this->y + this->height-1,color(255,255,0));
        line(this->x,this->y,this->x,this->y + this->height-1,color(255,255,0));
        line(this->x + width-1,this->y,this->x + this->width-1,this->y + this->height-1,color(255,255,0));
        
        // Compute current step

        // check if we need to render rigidbodies
        if (rigidBodyCount > 0) {
            computeRigidBodyStep(this->deltaTime);
            renderRigidBodies();
        }

        // check if we need to render particles
        if (particleCount > 0) {
            computeParticleStep(this->deltaTime);
            renderParticles();
        }

        // Tmp
        Debug_Printf(4,40,true,0,"Renderer (%i, %i) %ix%i", this->x, this->y, this->width, this->height);
    };

};
