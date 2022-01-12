/**
 * @file debug.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Debug menu that is toggled toggleDebug();
 * @version 1.1
 * @date 2021-12-29
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
#include "../../calc.hpp"
#include "../../draw_functions.hpp"
#include "../../fps_functions.hpp"
#include "../objects/entity.hpp"

bool DEBUG = false;

void debugger(uint32_t frame) {
    if(DEBUG){
        int i = 0; while (i<(width*12*3)) vram[i++]=0; //clear the top 3 lines
        Debug_Printf(0,0,true,0,"FRAME");
        // E = Entities, R = Rectangles, P = Particles, RB = RigidBodies C = Circles US = Usage (out of max entities)
        int totalEnts = typeCounter[0] + typeCounter[1] + typeCounter[2] + typeCounter[3];
		Debug_Printf(7,0,true,0,"E %i R %i P %i RB %i C %i US %4d% \%",totalEnts,typeCounter[0], typeCounter[1], typeCounter[2], typeCounter[3], ((totalEnts*100+MAX_ENTITIES/2)/MAX_ENTITIES));
        Debug_Printf(0,1,true,0,"%05d", frame);
        Debug_Printf(7,1,true,0,"Mem %8d",memUsed);
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

    // this initial implementation assumes that the tile size is
    // 16x16 and the tiles start at the top left of the screen
    if (isTileManagerActive) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < TILE_COUNT_X; j++) {
                // set the cell hasUpdate to true
                tile_manager_pointer->map[(i*TILE_COUNT_X) + j].hasUpdate = true;
            }
        }
        if (renderer_pointer != nullptr) {
            renderer_pointer->updateAll();
        }
    }
}
