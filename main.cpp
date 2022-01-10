#include <appdef.hpp>

#include "calc.hpp"
#include "draw_functions.hpp"
#include "lib/core/event_handler.hpp"
#include "lib/core/save.hpp"
#include "lib/core/tile_handler.hpp"
#include "lib/core/debug.hpp"
#include "lib/renderer.hpp"
// #include "lib/3d/3d.cpp"
// #include "lib/functions/random.hpp"

#ifndef PC
	APP_NAME("HHK Game Engine")
	APP_DESCRIPTION("Game Engine in development for HHK")
	APP_AUTHOR("InterChan / s3ansh33p / SnailMath / DasHeiligeDonerhuhn")
	APP_VERSION("0.0.1")
#endif

// Tracks the main game loop
bool game_running = true;

// Ends the game and is called by the event handler
void endGame() {
	game_running = false;
}

//The acutal main
void main2() {

	/*
	// 3D camera
	camx = 25;
	camy = -200;
	camz = 25;
	*/

	// load the textures and fonts
	LOAD_FONT_PTR("fnt\\7x8", f_7x8);

	// game starting screen
	// for (int i = 0; i < 100; i+=5) {
	// 	fillScreen(color(22, 22, 22));
	// 	draw_font_shader(f_7x8, "HHK Engine", 1, 128, color(255, 60, 0), 0, 0, 4, color(255, 190, 0));
	// 	LCD_Refresh();
	// }
	
	uint32_t frame = 0;

	Renderer renderer(0,0,320,528); // x,y,w,h

	// renderer.rectangles[typeCounter[0]].createRectangle(50,50,100,52,color(255,20,80));

	// renderer.circles[typeCounter[3]].createCircle(80,80,210,color(255,0,40));
	// renderer.circles[typeCounter[3]].createCircle(90,90,210,color(255,0,80));
	// renderer.circles[typeCounter[3]].createCircle(100,100,210,color(255,0,120));
	// renderer.circles[typeCounter[3]].createCircle(110,110,210,color(255,0,160));
	// renderer.circles[typeCounter[3]].createCircle(120,120,210,color(255,0,200));
	// renderer.circles[typeCounter[3]].createCircle(130,130,210,color(255,0,255));
	// renderer.circles[typeCounter[3]].createCircle(140,140,210,color(255,40,255));
	// renderer.circles[typeCounter[3]].createCircle(150,150,210,color(255,80,255));
	// renderer.circles[typeCounter[3]].createCircle(160,160,210,color(255,120,255));

	// Add event listeners
	addListener(KEY_BACKSPACE, toggleDebug); // toggle debug mode
	addListener(KEY_CLEAR, endGame); // end the game

	TileManager tileManager;
	tileManager.Init();
	// set the pointer to the tile manager
	tile_manager_pointer = &tileManager;

	// will need to write docs at some point
	
	fillScreen(color(0, 0, 64));

	while (game_running) {
		frame++;
		checkEvents();
		
		tileManager.DrawTiles(0,0);

		/*
		cube(10,10,10,30,color(0,255,0));//The innner cube
		cube(0,0,20,50,color(255,0,0));//The outer cube
		triangle( 0,0,0, 50,0,0, 0,50,50, color(255,128,128),color(255,0,0));//The triangle
		*/
		
		/*
		rng.Generate(1000);	
		Debug_Printf(1,20,true,0,"RNG: %i",rng.m_x);
		*/

		renderer.render();

		debugger(frame);
		LCD_Refresh();
	}
	
	// game ending screen
	for (int i = 0; i < 30; i+=2) {
		fillScreen(color(240, 240, 240));
		draw_font_shader(f_7x8, "HHK Engine", 1, 248, color(50, 45, 45), 0, 0, 3, i);
		LCD_Refresh();
	}
}
