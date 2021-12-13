#include <appdef.hpp>

#include "calc.hpp"
#include "draw_functions.hpp"
#include "lib/core/event_handler.hpp"
#include "lib/debug.hpp"
#include "lib/renderer.hpp"
#include "lib/trig3d.hpp"

#ifndef PC
	APP_NAME("HHK Game Engine")
	APP_DESCRIPTION("Game Engine in development for HHK")
	APP_AUTHOR("InterChan / s3ansh33p")
	APP_VERSION("0.0.1")
#endif

// Tracks the main game loop
bool game_running = true;

// Ends the game and is called by the event handler
void endGame() {
	game_running = false;
}

void camXIncrease() {
	CamXPos++;
   	Debug_Printf(25,31,true,0,"+Cam X: %i",CamXPos);
}
void camXDecrease() {
	CamXPos--;
   	Debug_Printf(25,31,true,0,"-Cam X: %i",CamXPos);
}
void camZIncrease() {
	CamZPos++;
   	Debug_Printf(25,31,true,0,"+Cam Z: %i",CamZPos);
}
void camZDecrease() {
	CamZPos--;
   	Debug_Printf(25,31,true,0,"-Cam Z: %i",CamZPos);

	removeAllParticles();
	removeAllRigidBodies();

	createParticle(10, 10, 0, 0, 2);
	createParticle(40, 10, 0, 0, 2);
	createParticle(70, 10, 0, 0, 2);

	createRigidBody(100, 10, 0, 0, 0, 0, 2, 8, 2);
	createRigidBody(150, 10, 0, 0, 0, 0, 2, 8, 2);
	createRigidBody(200, 10, 0, 0, 0, 0, 2, 8, 2);
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
	Renderer renderer(0,0,320,528); // x,y,w,h
	// will need to refactor
	createParticle(10, 10, 0, 0, 2);
	createParticle(40, 10, 0, 0, 2);
	createParticle(70, 10, 0, 0, 2);

	createRigidBody(100, 10, 0, 0, 0, 0, 2, 8, 2);
	createRigidBody(150, 10, 0, 0, 0, 0, 2, 8, 2);
	createRigidBody(200, 10, 0, 0, 0, 0, 2, 8, 2);

	// Add event listeners
	addListener(KEY_BACKSPACE, toggleDebug); // toggle debug mode
	addListener(KEY_CLEAR, endGame); // end the game

   	addListener(KEY_LEFT, camXIncrease);
	addListener(KEY_RIGHT, camXDecrease);
	addListener2(KEY_UP, camZIncrease);
	addListener2(KEY_DOWN, camZDecrease);

	while (game_running) {
		frame++;
		fillScreen(color(22, 22, 22));
		checkEvents();
		
		renderer.render();

		DrawTri3D(10,10,2,10,10,8,10,5,2);

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
