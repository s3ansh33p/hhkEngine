/**
 * @file rectangle.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Rectangle class for the engine
 * @version 1.1
 * @date 2021-12-23
 */

#pragma once

#include "entity.hpp"

class Rectangle: public Entity {
    public:
        int width;
        int height;
        void createRectangle(int x, int y, int width, int height, int color);
        void render(int rendererX, int rendererY, int rendererWidth, int rendererHeight);
};

// Create a rectangle given a position, dimensions, and color.
void Rectangle::createRectangle(int x, int y, int width, int height, int color) {
    this->create(x, y, color);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
}

void Rectangle::render (int rendererX, int rendererY, int rendererWidth, int rendererHeight) {
    bool renderLeft = true;
    bool renderRight = true;
    bool renderTop = true;
    bool renderBottom = true;

    // Check x bounds
    if(this->x < rendererX) {
        if (this->x + this->width > rendererX + rendererWidth) {
            renderLeft = false;
            renderRight = false;
        } else {
            renderLeft = false;
            this->x = rendererX;
            this->width = this->width - (rendererX - this->x);
        }
    } else if (this->x + this->width > rendererX + rendererWidth) {
        renderRight = false;
        this->width = rendererX + rendererWidth - this->x;
    }

    // Check y bounds
    if(this->y < rendererY) {
        if (this->y + this->height > rendererY + rendererHeight) {
            renderTop = false;
            renderBottom = false;
        } else {
            renderTop = false;
            this->y = rendererY;
            this->height = this->height - (rendererY - this->y);
        }
    } else if (this->y + this->height > rendererY + rendererHeight) {
        renderBottom = false;
        this->height = rendererY + rendererHeight - this->y;
    }

    // Render
    if (renderLeft) {
        line(this->x, this->y, this->x, this->y + this->height, this->color);
    }
    if (renderRight) {
        line(this->x + this->width, this->y, this->x + this->width, this->y + this->height, this->color);
    }
    if (renderTop) {
        line(this->x, this->y, this->x + this->width, this->y, this->color);
    }
    if (renderBottom) {
        line(this->x, this->y + this->height, this->x + this->width, this->y + this->height, this->color);
    }

}
