// Event Handler written by s3ansh33p - WIP

/*

addListener(&myFunctionName, KEY_EXP);  // add a listener to the Power Key that calls myFunctionName when pressed

bool game_running = true;               // starts a game loop
while (game_running) {                  // the game loop
    checkEvents();                      // check for events, including key presses
}

*/

#pragma once
#include "../../../calc.hpp"

uint32_t key1, key2;
typedef void (*printer_t)(int);

// Class listerner that stores a function pointer
class Listener {
    public:
        Keys1 key;
        printer_t p;
};

// Listeners array with size 10
Listener listeners[10];

// Will also include touch events in the future
void checkEvents() {
    getKey(&key1, &key2);
    for (int i = 0; i < sizeof(listeners); i++) {
        // if the key is pressed, call the listener
        if (testKey(key1, key2, listeners[i].key)) {
            (*listeners[i].p);
        }
    }
}

// function that creates a listener and adds it to the listeners array
void addListener(printer_t p, Keys1 key) {
    listeners[sizeof(listeners)+1].key = key;
    listeners[sizeof(listeners)+1].p = p;
}