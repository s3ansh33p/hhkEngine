#include <appdef.hpp>

#include "calc.hpp"
#include "draw_functions.hpp"
#include "lib/core/exceptions.hpp"
#include "lib/core/event_handler.hpp"
#include "lib/core/tile_handler.hpp"
#include "lib/renderer.hpp"
#include "lib/core/debug.hpp"
#include "lib/functions/random.hpp"
#include "lib/core/player.hpp"

#ifndef PC
	APP_NAME("HHK Game Engine")
	APP_DESCRIPTION("Game Engine in development for HHK")
	APP_AUTHOR("InterChan / s3ansh33p / SnailMath / DasHeiligeDonerhuhn")
	APP_VERSION("0.0.1")
#endif

// Tracks the main game loop
bool game_running = true;

// RNG pointer
RandomGenerator* rng;

// Player pointer
Player* player_pointer;

// Ends the game and is called by the event handler
void endGame() {
	game_running = false;
}

// left
void left() {
	player_pointer->moveLeft();
}

// right
void right() {
	player_pointer->moveRight();
}

// jump
void jump() {
	player_pointer->moveJump();
}

//The acutal main
void main2() {

	RandomGenerator rngp;
	rngp.SetSeed(1337);
	rng = &rngp;

	// load the textures and fonts
	// LOAD_FONT_PTR("fnt\\7x8", f_7x8);

	// game starting screen
	// for (int i = 0; i < 100; i+=5) {
	// 	fillScreen(color(22, 22, 22));
	// 	draw_font_shader(f_7x8, "HHK Engine", 1, 128, color(255, 60, 0), 0, 0, 4, color(255, 190, 0));
	// 	LCD_Refresh();
	// }
	
	uint32_t frame = 0;

	Renderer renderer(0,0,320,528); // x,y,w,h
	// set the pointer to the renderer
	renderer_pointer = &renderer;

	// Add event listeners
	addListener(KEY_BACKSPACE, toggleDebug); // toggle debug mode
	addListener(KEY_CLEAR, endGame); // end the game

	addListener(KEY_LEFT, left, true); // left
	addListener(KEY_RIGHT, right, true); // right
	addListener2(KEY_UP, jump, true); // jump

	TileManager tileManager;
	tileManager.Init();
	// set the pointer to the tile manager
	tile_manager_pointer = &tileManager;

	Player player;
	player.loadTextures();
	player_pointer = &player;
	
	fillScreen(color(0, 0, 0));

	while (game_running) {
		frame++;
		checkEvents();
		
		renderer.tileChecks();

		player.calculateAnimationFrame();
		tileManager.DrawTiles(0,0);
		player.animate();

		renderer.render();

		debugger(frame);
		LCD_Refresh();
	}
	
	// game ending screen
	// for (int i = 0; i < 30; i+=2) {
	// 	fillScreen(color(240, 240, 240));
	// 	draw_font_shader(f_7x8, "HHK Engine", 1, 248, color(50, 45, 45), 0, 0, 3, i);
	// 	LCD_Refresh();
	// }

	// free memory
	// free(f_7x8);
	tileManager.FreeTextures();
}
