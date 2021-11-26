#include "calc.hpp"
#include "fps_functions.hpp"
#include "draw_functions.hpp"

#ifndef PC
	APP_NAME("HHK Game Engine")
	APP_DESCRIPTION("Game Engine in development for HHK")
	APP_AUTHOR("InterChan / s3ash33p")
	APP_VERSION("0.0.1")
#endif

#define B_SIZE 64
#define B_STARTINGSPEED 12

int lerp(int a, int b, int t) { // t is in percent since no float
	return a + t * (b - a) / 100;
}

int clamp(int a, int min, int max) {
	if (a < min) {
		return min;
	} else if (a > max) {
		return max;
	}
	return a;
}

void rect(int x, int y, int w, int h, uint16_t c) {
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			setPixel(x + i, y + j, c);
		}
	}
}

//The acutal main
void main2() {
	
	int ballX = width / 2 - B_SIZE / 2;
	int ballY = height / 2 - B_SIZE / 2;
	int ballVelX = B_STARTINGSPEED;
	int ballVelY = B_STARTINGSPEED;
	
	// load the textures and fonts
	LOAD_FONT_PTR("fnt\\7x8", f_7x8);
	LOAD_TEXTURE_PTR("peter_chen_64", t_peter_chen_64);
	
	// game starting screen
	for (int i = 0; i < 100; i+=5) {
		fillScreen(color(22, 22, 22));
		draw_font_shader(f_7x8, "HHK Engine", 16, 128, color(255, 60, 0), 0, 0, 4, color(122, 222, 222));
		LCD_Refresh();
	}
	
	bool game_running = true;
	while (game_running) {
		uint32_t key1, key2;
		getKey(&key1, &key2);
		if (testKey(key1, key2, KEY_CLEAR)) game_running = false;
		
		// ball physics
		ballX += ballVelX;
		ballY += ballVelY;
		if (ballX < 0) {
			ballX = -ballX;
			ballVelX = -ballVelX;
		}
		if (ballX > width - B_SIZE) {
			ballX = -ballX - 2 * B_SIZE + 2 * width;
			ballVelX = -ballVelX;
		}

		// at your edge
		if (ballY + B_SIZE > height) {
			ballY = -ballY - 2 * B_SIZE + 2 * height;
			ballVelY = -ballVelY;
		}
		// at cp's edge
		if (ballY < 0) {
			ballVelY = -ballVelY;
		}
		
		fps_update();
		fps_formatted_update();
		
		// draw
		fillScreen(color(22, 22, 22));

		DRAW_TEXTURE(t_peter_chen_64, ballX, ballY);
		
		draw_font_shader(f_7x8, fps_formatted, 0, 0, 0xFFFF, 0, 0, 5, color(255, 128, 0));
		LCD_Refresh();
	}
	
	// game ending screen
	for (int i = 0; i < 30; i+=2) {
		fillScreen(color(240, 240, 240));
		draw_font_shader(f_7x8, "HHK Engine", 16, 248, color(50, 45, 45), 0, 0, 3, i);
		LCD_Refresh();
	}
}
