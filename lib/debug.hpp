#include <stdint.h>
#include "../calc.hpp"
#include "../fps_functions.hpp"

uint32_t key1, key2;
uint32_t old1 = 0;
uint32_t old2 = 0;
bool DEBUG = false;

uint32_t memMax = 65536;

void debug_init(uint32_t frame) {
    if(DEBUG){
        int i = 0; while (i<(width*12*2)) vram[i++]=0; //clear the top 2 lines
        Debug_Printf(0,0,true,0,"%05d", frame);
        Debug_Printf(0,1,true,0,"DEBUG");
        Debug_Printf(7,0,true,0,"Mem %8d",memUsed);
        Debug_Printf(7,1,true,0,"Max %8d",memMax);
        Debug_Printf(20,0,true,0,"Mem Usage %8d% \%",((memUsed*100+memMax/2)/memMax));
        Debug_Printf(20,1,true,0,"Fonts %01d",fLoaded);
        Debug_Printf(28,1,true,0,"Textures %02d",txLoaded);
        Debug_Printf(45,1,true,0,"V 0.0.1");
        fps_update();
		fps_formatted_update();
		fps_display();
    }
            
    //Read the keyboard
    old1 = key1;
    old2 = key2;
    getKey(&key1, &key2);

    if (old1 != key1 || old2 != key2) {
        if (testKey(key1,key2,KEY_BACKSPACE)) { //BACKSPACE toggles DEBUG
            DEBUG=!DEBUG;
        }
    }

}