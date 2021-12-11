/**
 * @file event_handler.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Event handler class to keep track of events and their handlers.
 * @version 1.1
 * @date 2021-12-11
 * 
 * It can be useful to track memory usage, framerate and other information.
 * 
 * @code{cpp}
 * // add a listener to the LEFT key that calls myFunctionName when pressed
 * addListener(KEY_LEFT, myFunctionName);  
 * // there are two different key enums, Keys1 and Keys2, so you use the same function name with a 2 on the end for Keys2
 * addListener2(KEY_UP, myFunctionName2);  
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

// Keys1 - 16 keys in enum
Keys1 listeners[16] = {KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR, KEY_CLEAR};
void (*func_ptr[16])() = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t listener_count = 0;

void addListener(Keys1 key, void (*func)()) {
   listeners[listener_count] = key;
   func_ptr[listener_count] = func;
   listener_count++;
}

void removeListener(Keys1 key) {
   for (uint8_t i = 0; i < listener_count; i++) {
      if (listeners[i] == key) {
         // Shift all elements down
         listener_count--;
         for (uint8_t j = i; j < listener_count; j++) {
            listeners[j] = listeners[j + 1];
            func_ptr[j] = func_ptr[j + 1];
         }
      }
   }
}

// Keys2 - 18 keys in enum
Keys2 listeners2[18] = {KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD, KEY_KEYBOARD};
void (*func_ptr2[18])() = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t listener_count2 = 0;

void addListener2(Keys2 key, void (*func)()) {
   listeners2[listener_count2] = key;
   func_ptr2[listener_count2] = func;
   listener_count2++;
}

void removeListener2(Keys2 key) {
   for (uint8_t i = 0; i < listener_count2; i++) {
      if (listeners2[i] == key) {
         // Shift all elements down
         listener_count2--;
         for (uint8_t j = i; j < listener_count2; j++) {
            listeners2[j] = listeners2[j + 1];
            func_ptr2[j] = func_ptr2[j + 1];
         }
      }
   }
}

void checkEvents() {
   //Read the keyboard
   ev_old1 = ev_key1;
   ev_old2 = ev_key2;
   getKey(&ev_key1, &ev_key2);

   if (ev_old1 != ev_key1 || ev_old2 != ev_key2) {
      bool key1_pressed = false;
      for (uint8_t i = 0; i < listener_count; i++) {
         // Check if the key is pressed
         if (testKey(ev_key1,ev_key2,listeners[i])) {
            // call the function
            (*func_ptr[i])();
            key1_pressed = true;
            break; // no need to check the rest of the keys
         }
      }
      if (!key1_pressed) { // check if key already found
         for (uint8_t i = 0; i < listener_count2; i++) {
            // Check if the key is pressed
            if (testKey(ev_key1,ev_key2,listeners2[i])) {
               // call the function
               (*func_ptr2[i])();
               break; // no need to check the rest of the keys
            }
         }
      }
   }
}
