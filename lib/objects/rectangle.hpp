/**
 * @file rectangle,hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Rectangle class for the engine
 * @version 1.0
 * @date 2021-12-17
 */

#pragma once

#include "../environment.hpp"
#include "../../calc.hpp"

class ParentClass;

int rectangleCount = 0;
int rectangleIDCounter = 0;

// A rectangle
typedef struct {
    int id;
    int x;
    int y;
    int width;
    int height;
    int color;
} Rectangle;


// Global array of rectangles.
Rectangle rectangles[MAX_RECTANGLES];

class RectangleManager {
public:
    ~RectangleManager();
    int rendererX;
    int rendererY;
    int rendererWidth;
    int rendererHeight;

    void setRenderDimensions(int x, int y, int width, int height);
    void createRectangle(int x, int y, int width, int height, int color);
    void renderRectangles();
    void removeAllRectangles();
    void removeRectangle(int rectangleId);
    Rectangle getRectangle(int rectangleId);
    
};

void RectangleManager::setRenderDimensions(int x, int y, int width, int height) {
    this->rendererX = x;
    this->rendererY = y;
    this->rendererWidth = width;
    this->rendererHeight = height;
}

void RectangleManager::renderRectangles() {
    for (int i = 0; i < rectangleCount; i++) {
        Rectangle *rectangle = &rectangles[i];


        bool renderLeft = true;
        bool renderRight = true;
        bool renderTop = true;
        bool renderBottom = true;

        // Check x bounds
        if(rectangle->x < rendererX) {
            if (rectangle->x + rectangle->width > rendererX + rendererWidth) {
                renderLeft = false;
                renderRight = false;
            } else {
                renderLeft = false;
                rectangle->x = rendererX;
                rectangle->width = rectangle->width - (rendererX - rectangle->x);
            }
        } else if (rectangle->x + rectangle->width > rendererX + rendererWidth) {
            renderRight = false;
            rectangle->width = rendererX + rendererWidth - rectangle->x;
        }

        // Check y bounds
        if(rectangle->y < rendererY) {
            if (rectangle->y + rectangle->height > rendererY + rendererHeight) {
                renderTop = false;
                renderBottom = false;
            } else {
                renderTop = false;
                rectangle->y = rendererY;
                rectangle->height = rectangle->height - (rendererY - rectangle->y);
            }
        } else if (rectangle->y + rectangle->height > rendererY + rendererHeight) {
            renderBottom = false;
            rectangle->height = rendererY + rendererHeight - rectangle->y;
        }

        // Render
        if (renderLeft) {
            line(rectangle->x, rectangle->y, rectangle->x, rectangle->y + rectangle->height, rectangle->color);
        }
        if (renderRight) {
            line(rectangle->x + rectangle->width, rectangle->y, rectangle->x + rectangle->width, rectangle->y + rectangle->height, rectangle->color);
        }
        if (renderTop) {
            line(rectangle->x, rectangle->y, rectangle->x + rectangle->width, rectangle->y, rectangle->color);
        }
        if (renderBottom) {
            line(rectangle->x, rectangle->y + rectangle->height, rectangle->x + rectangle->width, rectangle->y + rectangle->height, rectangle->color);
        }

    }
}

// Create a rectangle given a position, velocity and mass.
void RectangleManager::createRectangle(int x, int y, int width, int height, int color) {
    rectangles[rectangleCount].x = x;
    rectangles[rectangleCount].y = y;
    rectangles[rectangleCount].width = width;
    rectangles[rectangleCount].height = height;
    rectangles[rectangleCount].color = color;
    rectangles[rectangleCount].id = rectangleIDCounter;
    rectangleCount++;
    rectangleIDCounter++;
}

// Remove a rectangle from the array.
void RectangleManager::removeRectangle(int rectangleId) {
    if (rectangleId < rectangleCount) {
        for (int i = rectangleId; i < rectangleCount; i++) {
            rectangles[i] = rectangles[i + 1];
        }
        rectangleCount--;
    }
}

// Remove all rectangles from the array.
void RectangleManager::removeAllRectangles() {
    rectangleCount = 0;
}

// Get a rectangle from the array given an id.
Rectangle RectangleManager::getRectangle(int rectangleId) {
    for (int i = 0; i < rectangleCount; i++) {
        if (rectangles[i].id == rectangleId) {
            return rectangles[i];
        }
    }
    // return an empty rectangle if doesnt exist with id of -1
    return {-1, 0, 0, 0, 0, 0};
}
