#include <appdef.hpp>

#include "calc.hpp"
#include "draw_functions.hpp"
#include "lib/core/event_handler.hpp"
#include "lib/debug.hpp"

#ifndef PC
	APP_NAME("HHK Game Engine")
	APP_DESCRIPTION("Game Engine in development for HHK")
	APP_AUTHOR("InterChan / s3ash33p")
	APP_VERSION("0.0.1")
#endif

void fun1() {
   Debug_Printf(25,31,true,0,"func1");
}
void fun2() {
   Debug_Printf(25,31,true,0,"func2");
}
void fun3() {
   Debug_Printf(25,31,true,0,"func3");
}
void fun4() {
   Debug_Printf(25,31,true,0,"func4");
}

// Tracks the main game loop
bool game_running = true;

// Ends the game and is called by the event handler
void endGame() {
	game_running = false;
}

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
	
	uint32_t frame = 0;

	// Add event listeners
	addListener(KEY_BACKSPACE, toggleDebug); // toggle debug mode
	addListener(KEY_CLEAR, endGame); // end the game

	addListener(KEY_BACKSPACE, fun1);
   	addListener(KEY_LEFT, fun2);
	addListener(KEY_RIGHT, fun3);
	addListener2(KEY_DOWN, fun4);

	while (game_running) {
		frame++;
		fillScreen(color(22, 22, 22));
		debugger(frame);
		checkEvents();
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
