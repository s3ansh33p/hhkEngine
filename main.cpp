#include <appdef.hpp>

#include "calc.hpp"
#include "draw_functions.hpp"
#include "lib/core/event_handler.hpp"
#include "lib/debug.hpp"
#include "lib/renderer.hpp"
#include "lib/3d/3d.cpp"
#include "lib/save.hpp"

#ifndef PC
	APP_NAME("HHK Game Engine")
	APP_DESCRIPTION("Game Engine in development for HHK")
	APP_AUTHOR("InterChan / s3ansh33p")
	APP_VERSION("0.0.1")
#endif

// Tracks the main game loop
bool game_running = true;

// Sprint
int sprint = 1;

// Ends the game and is called by the event handler
void endGame() {
	game_running = false;
}

void camXIncrease() {
	camx += sprint;
   	Debug_Printf(25,31,true,0,"+Cam X: %i",camx);
}
void camXDecrease() {
	camx -= sprint;
   	Debug_Printf(25,31,true,0,"-Cam X: %i",camx);
}
void camYIncrease() {
	camy += sprint;
   	Debug_Printf(25,31,true,0,"+Cam Y: %i",camy);
}
void camYDecrease() {
	camy -= sprint;
   	Debug_Printf(25,31,true,0,"-Cam Y: %i",camy);
}
void camZIncrease() {
	camz += sprint;
   	Debug_Printf(25,31,true,0,"+Cam Z: %i",camz);
}
void camZDecrease() {
	camz -= sprint;
   	Debug_Printf(25,31,true,0,"-Cam Z: %i",camz);
}
void camAIncrease() {
	cama += sprint;
   	Debug_Printf(25,31,true,0,"+Cam A: %i",cama);
}
void camADecrease() {
	cama -= sprint;
   	Debug_Printf(25,31,true,0,"-Cam A: %i",cama);
}
void camBIncrease() {
	camb += sprint;
   	Debug_Printf(25,31,true,0,"+Cam B: %i",camb);
}
void camBDecrease() {
	camb -= sprint;
   	Debug_Printf(25,31,true,0,"-Cam B: %i",camb);
}

void toggleSprint() {
	if (sprint == 1) {
		sprint = 10;
	} else {
		sprint = 1;
	}
	Debug_Printf(25,31,true,0,"Sprint: %i",sprint);
}

void save() {
	writeSave("save.sav");
}

void load() {
	loadSave("save.sav");
}

void runParticleSim() {
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

	camx = 25;
	camy = -200;
	camz = 25;
	
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

	// Add event listeners
	addListener(KEY_BACKSPACE, toggleDebug); // toggle debug mode
	addListener(KEY_CLEAR, endGame); // end the game

	// 3D Camera controls
   	addListener(KEY_LEFT, camXDecrease);
	addListener(KEY_RIGHT, camXIncrease);
	addListener2(KEY_UP, camYIncrease);
	addListener2(KEY_DOWN, camYDecrease);
	addListener(KEY_ADD, camZIncrease);
	addListener(KEY_SUBTRACT, camZDecrease);
	addListener(KEY_6, camAIncrease);
	addListener2(KEY_4, camADecrease);
	addListener2(KEY_8, camBIncrease);
	addListener2(KEY_2, camBDecrease);
	addListener2(KEY_5, toggleSprint);

	// Particle Sim
	addListener2(KEY_EQUALS, runParticleSim);

	// Save files
	addListener2(KEY_X, load);
	addListener2(KEY_Y, save);

	while (game_running) {
		frame++;
		fillScreen(color(22, 22, 22));
		checkEvents();
		
		renderer.render();

		Debug_Printf(25,30,true,0,"Float: %f",1.4);

		cube(10,10,10,30,color(0,255,0));//The innner cube
		cube(0,0,20,50,color(255,0,0));//The outer  cube

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
