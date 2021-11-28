// fps_functions.hpp by InterChan

// In main loop add "fps_update();" which updates the variable fps10
// The int "fps10" represents the fps to one decimal place, except without the decimal point so 14.2 is just 142
// The "fps_formatted" string is the FPS to one decimal place, in the format "xx.x FPS"
// Use "fps_formatted_update();" to update the string to current fps10 before displaying it
// Use "fps_display();" to show the formatted FPS in the top left corner

#pragma once

#include <sdk/os/string.hpp>
#include <sdk/os/debug.hpp>

uint8_t *R64CNT = (uint8_t*)0xA413FEC0;
uint8_t prevtime = 0;
int fps10 = 0;
char fps_formatted[9];

void fps_update() {
	// update fps10
	if (*R64CNT - prevtime == 0) {
		fps10 = 1280;
	} else {
		fps10 = 1280 / ((int)((*R64CNT - prevtime) & 0b01111111));
	}
	prevtime = *R64CNT;
}

void fps_formatted_update() {
	int16_t dec00_1 = fps10;
	uint8_t dec01_0 = 0;
	uint8_t dec10_0 = 0;
	while (dec00_1 >= 100) { dec00_1-= 100; dec10_0++; }
	while (dec00_1 >= 10) { dec00_1-=  10; dec01_0++; }
	strcpy(fps_formatted, "  .  FPS");
	fps_formatted[0] = dec10_0 + 48;
	fps_formatted[1] = dec01_0 + 48;
	fps_formatted[3] = (uint8_t)(dec00_1 + 48);
}

inline void fps_display() {
	Debug_Printf(45,0,false,0,fps_formatted);
}