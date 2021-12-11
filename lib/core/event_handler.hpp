/**
 * @file event_handler.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Event handler class to keep track of events and their handlers.
 * @version 1.0
 * @date 2021-12-11
 * 
 * It can be useful to track memory usage, framerate and other information.
 * 
 * @code{cpp}
 * // add a listener to the Power Key that calls myFunctionName when pressed
 * addListener(KEY_EXP, myFunctionName);  
 * 
 * // starts a game loop
 * bool game_running = true;
 * while (game_running) {
 *     // check for events, including key presses
 *     checkEvents();                      
 * }
 * @endcode
 */

#pragma once
#include "../../calc.hpp"

uint32_t ev_key1, ev_key2;
uint32_t ev_old1 = 0;
uint32_t ev_old2 = 0;

// Currently only storing 5 events
Keys1 listeners[5] = {KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR};
void (*func_ptr[5])() = {0, 0, 0, 0, 0};
uint8_t listener_count = 0;

void addListener(Keys1 key, void (*func)()) {
   listeners[listener_count] = key;
   func_ptr[listener_count] = func;
   listener_count++;
}

void checkEvents() {
   //Read the keyboard
   ev_old1 = ev_key1;
   ev_old2 = ev_key2;
   getKey(&ev_key1, &ev_key2);

   if (ev_old1 != ev_key1 || ev_old2 != ev_key2) {
      for (uint8_t i = 0; i < listener_count; i++) {
         // Check if the listener is not 0
         if (listeners[i] != KEY_CLEAR) {
            // Check if the key is pressed
            if (testKey(ev_key1,ev_key2,listeners[i])) {
               // check for the function pointer
               if (func_ptr[i] != 0) {
                  // call the function
                  (*func_ptr[i])();
               }
            }
         } else {
            break; // no need to check the rest of the listeners
         }
      }
   }
}
