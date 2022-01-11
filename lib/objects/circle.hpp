/**
 * @file shapes.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Shapes for the engine
 * @version 1.0
 * @date 2022-01-09
 */

#pragma once


class Circle: public Entity {
    public:
        int radius;
        void create(int x, int y, int radius, int color);
        void render(int rendererX, int rendererY, int rendererWidth, int rendererHeight);
		void tileChecks();
		void remove();
};

// Create a circle given a position, radius, and color.
void Circle::create(int x, int y, int radius, int color) {
    this->createEnt(x, y, color, 3);
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->color = color;
}

void Circle::render(int rendererX, int rendererY, int rendererWidth, int rendererHeight) {
	if (!this->hasUpdate) return;
    for (int32_t dx = -this->radius; dx < this->radius; ++dx) {
		for (int32_t dy = -this->radius; dy < this->radius; ++dy) {
			if (dx * dx + dy * dy < this->radius * this->radius) {
				int32_t x = this->x + dx;
				int32_t y = this->y + dy;
				if (x < rendererX || x > (rendererX + rendererWidth) || y < rendererY || y > (rendererY + rendererHeight)) {
					continue;
				}
				vram[(x) + (y) * width] = color;
			}
		}
	}

	this->hasUpdate = false;
}

void Circle::tileChecks() {
	
	// Check for updating tiles
    if (isTileManagerActive && this->hasUpdate) {
        int tileX = this->x / TILE_WIDTH;
        int tileY = this->y / TILE_HEIGHT;
        int tileWidth = this->radius / TILE_WIDTH + 1;
        int tileHeight = this->radius / TILE_HEIGHT + 1;

        for (int i = -tileWidth; i < tileWidth + 1; i++) {
            for (int j = -tileHeight; j < tileHeight + 1; j++) {
                tile_manager_pointer->RefreshTile(tileX + i, tileY + j);
                // tile_manager_pointer->UpdateTile(tileX + i, tileY + j, 1);
            }
        }
        
    }

}

void Circle::remove() {
	this->hasUpdate = true;
	this->tileChecks(); //tell the tiles in the circle to update after the circle is removed
	this->removeEnt();
}
