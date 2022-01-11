/**
 * @file rectangle.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Rectangle class for the engine
 * @version 1.1
 * @date 2021-12-29
 */

#pragma once

#include "entity.hpp"

class Rectangle: public Entity {
    public:
        int width;
        int height;
        void create(int x, int y, int width, int height, int color);
        void render(int rendererX, int rendererY, int rendererWidth, int rendererHeight);
        void tileChecks();
        void remove();
};

// Create a rectangle given a position, dimensions, and color.
void Rectangle::create(int x, int y, int width, int height, int color) {
    this->createEnt(x, y, color, 0);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
}

void Rectangle::render (int rendererX, int rendererY, int rendererWidth, int rendererHeight) {
    if (!this->hasUpdate) return;
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

    this->hasUpdate = false;

}

void Rectangle::tileChecks() {
    
    // Check for updating tiles
    /*
		50,50	150,50
		|-----------|
		|           |
		|-----------|
		50,102	150,102

		Tiles are 16x16 pixels
		20 x 33 tiles

		X CALC
		50 / 16 = 3.5
		Tile Index 3 gets updated
		100 / 16 = 6.25
		The next 6 tiles get updated

		Y CALC
		50 / 16 + 1 = 4.5
		Tile Index 4 gets updated
		52 / 16 + 1 = 4.125
		The next 4 tiles get updated

		Tile updated
		3,3 to 3,10
		to
		7,3 to 7,10
	*/
    if (isTileManagerActive && this->hasUpdate) {
        int tileX = this->x / TILE_WIDTH;
        int tileY = this->y / TILE_HEIGHT;
        int tileWidth = this->width / TILE_WIDTH + 1;
        int tileHeight = this->height / TILE_HEIGHT + 1;

        for (int i = 0; i < tileWidth; i++) {
            for (int j = 0; j < tileHeight; j++) {
                // tile_manager_pointer->RefreshTile(tileX + i, tileY + j);
                tile_manager_pointer->UpdateTile(tileX + i, tileY + j, 1);
            }
        }
    }

}

void Rectangle::remove() {
	this->hasUpdate = true;
	this->tileChecks();
	this->remove();
}