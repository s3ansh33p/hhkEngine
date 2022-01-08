#define PIXEL(x, y) (vram[(x) + (y) * width])

void drawCircle(int32_t x0, int32_t y0, int radius, uint16_t color) {
	for (int32_t dx = -radius; dx < radius; ++dx) {
		for (int32_t dy = -radius; dy < radius; ++dy) {
			if (dx * dx + dy * dy < radius * radius) {
				int32_t x = x0 + dx;
				int32_t y = y0 + dy;

				if (x < 0 || x > width || y < 0 || y > height) {
					continue;
				}

				PIXEL(x, y) = color;
			}
		}
	}
}
