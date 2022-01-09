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
        void createCircle(int x, int y, int radius, int color);
        void render(int rendererX, int rendererY, int rendererWidth, int rendererHeight);
};

// Create a circle given a position, radius, and color.
void Circle::createCircle(int x, int y, int radius, int color) {
    this->create(x, y, color, 3);
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->color = color;
}

void Circle::render(int rendererX, int rendererY, int rendererWidth, int rendererHeight) {
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
}

// void Circle::render(int x0, int y0, int radius, int color) {
//     for (int32_t dx = -radius; dx < radius; ++dx) {
// 		for (int32_t dy = -radius; dy < radius; ++dy) {
// 			if (dx * dx + dy * dy < radius * radius) {
// 				int32_t x = x0 + dx;
// 				int32_t y = y0 + dy;
// 				if (x < 0 || x > width || y < 0 || y > height) {
// 					continue;
// 				}
// 				vram[(x) + (y) * width] = color;
// 			}
// 		}
// 	}
// }
