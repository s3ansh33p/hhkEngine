#include <appdef.hpp>

#include "calc.hpp"
#include "draw_functions.hpp"
#include "lib/core/event_handler.hpp"
#include "lib/core/save.hpp"
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

// Sprint
// int sprint = 1;

// Ends the game and is called by the event handler
void endGame() {
	game_running = false;
}

/*
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
*/

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
	for (int i = 0; i < 100; i+=5) {
		fillScreen(color(22, 22, 22));
		draw_font_shader(f_7x8, "HHK Engine", 1, 128, color(255, 60, 0), 0, 0, 4, color(255, 190, 0));
		LCD_Refresh();
	}
	
	uint32_t frame = 0;

	Renderer renderer(10,10,150,400); // x,y,w,h

	// renderer.addRectangle(50,50,100,52,color(255,20,80));
	// renderer.addRectangle(55,265,200,500,color(255,255,90));
	// renderer.addRectangle(60,270,200,500,color(255,255,125));
	// renderer.addRectangle(65,275,200,500,color(255,255,160));
	// renderer.addRectangle(70,280,200,500,color(255,255,195));
	// renderer.addRectangle(75,285,200,500,color(255,255,220));
	// renderer.addRectangle(80,290,200,500,color(255,255,255));

	// renderer.addRectangle(50,50,100,52,color(255,20,80)); // does not work for some reason??
	renderer.rectangles[typeCounter[0]].createRectangle(50,50,100,52,color(255,20,80));
	typeCounter[0]++;
	// renderer.addParticle(20,10,0,0,2,color(255,255,255));
	// renderer.addParticle(40,10,0,0,2,color(255,255,255));
	// renderer.addParticle(60,10,0,0,2,color(255,255,255));
	// renderer.addParticle(80,10,0,0,2,color(255,255,255));

	// renderer.addRigidBody(40, 10, 0, 0, 0, 0, 2, 8, 2, color(255, 0, 0));
	// renderer.addRigidBody(100, 10, 0, 0, 0, 0, 2, 8, 2, color(255, 0, 0));

	// Add event listeners
	addListener(KEY_BACKSPACE, toggleDebug); // toggle debug mode
	addListener(KEY_CLEAR, endGame); // end the game

	/*
	// 3D Camera controls
   	addListener(KEY_LEFT, camXDecrease, true);
	addListener(KEY_RIGHT, camXIncrease, true);
	addListener2(KEY_UP, camYIncrease, true);
	addListener2(KEY_DOWN, camYDecrease, true);
	addListener(KEY_ADD, camZIncrease, true);
	addListener(KEY_SUBTRACT, camZDecrease, true);
	addListener(KEY_6, camAIncrease, true);
	addListener2(KEY_4, camADecrease, true);
	addListener2(KEY_8, camBIncrease, true);
	addListener2(KEY_2, camBDecrease, true);
	addListener2(KEY_5, toggleSprint);
	*/

	/*
	// Save files
	addListener2(KEY_X, load);
	addListener2(KEY_Y, save);
	*/

	/*
	RandomGenerator rng;
	rng.SetSeed(12345);
	*/

	while (game_running) {
		frame++;
		fillScreen(color(0, 0, 64));
		checkEvents();
		

		// Debug_Printf(25,30,true,0,"Float: %f",1.4); needs --withmultilib=m4-nofpu in gcc and --m4a-nofpu in makefile

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
