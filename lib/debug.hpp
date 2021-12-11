/**
 * @file debug.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Debug menu that is toggled toggleDebug();
 * @version 1.1
 * @date 2021-12-11
 * 
 * It can be useful to track memory usage, framerate and other information.
 * @code{cpp}
 * // Add the toggleDebug() function to your main.cpp - can use any key
 * addListener(KEY_BACKSPACE, toggleDebug);
 * // render the debug menu - put this in your game loop
 * debugger();
 * @endcode
 */

#include <stdint.h>
#include "../calc.hpp"
#include "../fps_functions.hpp"

bool DEBUG = false;

uint32_t memMax = 65536;

void debugger(uint32_t frame) {
    if(DEBUG){
        int i = 0; while (i<(width*12*3)) vram[i++]=0; //clear the top 3 lines
        Debug_Printf(0,0,true,0,"FRAME");
        Debug_Printf(0,1,true,0,"%05d", frame);
        Debug_Printf(7,0,true,0,"Mem %8d",memUsed);
        Debug_Printf(7,1,true,0,"Max %8d",memMax);
        Debug_Printf(20,0,true,0,"Mem Usage %8d% \%",((memUsed*100+memMax/2)/memMax));
        Debug_Printf(20,1,true,0,"Fonts %01d",fLoaded);
        Debug_Printf(28,1,true,0,"Textures %02d",txLoaded);
        Debug_Printf(46,1,true,0,"V 0.0.1");
        // 3rd line for Listeners
        Debug_Printf(0,2,true,0,"DEBUG");
        Debug_Printf(7,2,true,0,"Listeners %02d",listener_count+listener_count2);
        Debug_Printf(20,2,true,0,"Key1 %11d",ev_key1);
        Debug_Printf(37,2,true,0,"Key2 %11d",ev_key2);
        fps_update();
		fps_formatted_update();
		fps_display();
    }
}

void toggleDebug() {
    DEBUG=!DEBUG;
}
