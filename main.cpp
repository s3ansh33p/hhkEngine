#include <appdef.hpp>

#include "calc.hpp"
#include "draw_functions.hpp"
#include "lib/debug.hpp"

#ifndef PC
	APP_NAME("HHK Game Engine")
	APP_DESCRIPTION("Game Engine in development for HHK")
	APP_AUTHOR("InterChan / s3ash33p")
	APP_VERSION("0.0.1")
#endif

//The acutal main
void main2() {
	
	// load the textures and fonts
	LOAD_FONT_PTR("fnt\\7x8", f_7x8);
	

	// game starting screen
	for (int i = 0; i < 100; i+=5) {
		fillScreen(color(22, 22, 22));
		draw_font_shader(f_7x8, "HHK Engine", 1, 128, color(255, 60, 0), 0, 0, 4, color(255, 190, 0));
		LCD_Refresh();
	}
	
	bool game_running = true;
	uint32_t frame = 0;
	while (game_running) {
		frame++;
		uint32_t key1, key2;
		getKey(&key1, &key2);
		if (testKey(key1, key2, KEY_CLEAR)) game_running = false; 
		fillScreen(color(22, 22, 22));
		debug_init(frame);
		Debug_Printf(13,5,true,0,"Game Runing: %8d",game_running);
		LCD_Refresh();
	}
	
	// game ending screen
	for (int i = 0; i < 30; i+=2) {
		fillScreen(color(240, 240, 240));
		draw_font_shader(f_7x8, "HHK Engine", 1, 248, color(50, 45, 45), 0, 0, 3, i);
		LCD_Refresh();
	}
}
