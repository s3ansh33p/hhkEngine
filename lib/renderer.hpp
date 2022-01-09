/**
 * @file renderer.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Renderer for the engine
 * @version 1.0
 * @date 2021-12-29
 */

#pragma once

#include "objects/particle.hpp"
#include "objects/rigidbody.hpp"
#include "objects/rectangle.hpp"
#include "objects/circle.hpp"
#include "../calc.hpp"

class Renderer {
    public:
    
    int rendererX = 0;                      // x position of the renderer
    int rendererY = 0;                      // y position of the renderer
    int rendererWidth = 0;                  // width of the window
    int rendererHeight = 0;                 // height of the window
    int currentTime = 0;                    // current time of the renderer
    int deltaTime = 1;                      // time (in seconds) for each step
    Rectangle rectangles[MAX_RECTANGLES];   // array of rectangles
    Particle particles[MAX_PARTICLES];      // array of particles
    RigidBody rigidbodies[MAX_RIGIDBODIES]; // array of rigidbodies
    Circle circles[MAX_CIRCLES];            // array of circles

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

    // Render function
    void render() {

        this->currentTime += this->deltaTime;
        
        // Compute current step
        for (int i = 0; i<typeCounter[0]; i++) {
            this->rectangles[i].render(this->rendererX, this->rendererY, this->rendererWidth, this->rendererHeight);
        }
        for (int i = 0; i<typeCounter[1]; i++) {
            this->particles[i].render(this->deltaTime, this->rendererX, this->rendererY, this->rendererWidth, this->rendererHeight);
        }
        for (int i = 0; i<typeCounter[2]; i++) {
            this->rigidbodies[i].render(this->deltaTime, this->rendererX, this->rendererY, this->rendererWidth, this->rendererHeight);
        }
        for (int i = 0; i<typeCounter[3]; i++) {
            this->circles[i].render(this->rendererX, this->rendererY, this->rendererWidth, this->rendererHeight);
        }

        // Tmp
        Debug_Printf(4,40,true,0,"Renderer (%i, %i) %ix%i", this->rendererX, this->rendererY, this->rendererWidth, this->rendererHeight);

        // Outline renderer
        line(this->rendererX, this->rendererY, this->rendererX, this->rendererY + this->rendererHeight, color(255,255,0));
        line(this->rendererX, this->rendererY, this->rendererX + this->rendererWidth, this->rendererY, color(255,255,0));
        line(this->rendererX + this->rendererWidth, this->rendererY, this->rendererX + this->rendererWidth, this->rendererY + this->rendererHeight, color(255,255,0));
        line(this->rendererX, this->rendererY + this->rendererHeight, this->rendererX + this->rendererWidth, this->rendererY + this->rendererHeight, color(255,255,0));
    };

    // Add a rectangle to the renderer
    void addRectangle(int x, int y, int width, int height, uint16_t color) {
        this->rectangles[typeCounter[0]].createRectangle(x, y, width, height, color);
        typeCounter[0]++;
    }

    // Add a particle to the renderer
    void addParticle(int x, int y, int vx, int vy, int mass, int color) {
        this->particles[typeCounter[1]].createParticle(x, y, vx, vy, mass, color);
        typeCounter[1]++;
    }

    // Add a rigidbody to the renderer
    void addRigidBody(int x, int y, int vx, int vy, int angle, int av, int width, int height, int mass, int color) {
        this->rigidbodies[typeCounter[2]].createRigidBody(x, y, vx, vy, angle, av, width, height, mass, color);
        typeCounter[2]++;
    }

    // Add a circle to the renderer
    void addCircle(int x, int y, int radius, int color) {
        this->circles[typeCounter[3]].createCircle(x, y, radius, color);
        typeCounter[3]++;
    }

};


