# Writing your First Program
In this tutorial, we will be making a simple program where an image bounces around the screen, similar to the DVD screensaver.
## 1. Setup the environment
Install hollyhock-2 and complete the [patching](https://github.com/SnailMath/hollyhock-2/blob/master/doc/user/developing.md) docs with newlib if you haven't already.
- duplicate the hhkEngine folder and call it myFirstGame
- delete the contents in the textures folder
- delete the contents in the res folder (will be unnecessary in the future)

Now you've got everything setup to start working on the game.

## 2. Hello World
First, let's create a basic loop which will display the text "Hello World!" on the screen. This will also check for keypresses and exit the program if the user presses the clear key.

Let's start by creating a new file in the folder named main.cpp (if it already exists, delete it first, again in the future this will be cleaner and it will instead be a template for hello world).

We need to include the calc.hpp file, which contains information about the screen size and the keys. Additonaly, we need to include the event_handler.hpp file, which contains the keypresses.

```cpp
// main.cpp
#include <appdef.hpp>

#include "calc.hpp"
#include "lib/core/event_handler.hpp"
```

After that, let's add our app information.
```cpp
// main.cpp
#ifndef PC
	APP_NAME("MyGame")
	APP_DESCRIPTION("My First Game")
	APP_AUTHOR("Your Name")
	APP_VERSION("1.0")
#endif
```

Let's add the game loop. We will use a variable called `game_running` and set it to true. Then create a function called `endGame` which will be called when the user presses the clear key.
```cpp
// main.cpp
bool game_running = true;

void endGame() {
	game_running = false;
}
```

Now, let's add the main loop, with some text and a listener for the clear key.
```cpp
// main.cpp
void main2() {

	// Add event listener
	addListener(KEY_CLEAR, endGame);
	
    // Set the background color to black
	fillScreen(color(0, 0, 0));

    // Game loop
	while (game_running) {

        // Will check for keypresses and call the function endGame if the clear key is pressed
		checkEvents();

        // Draw text on screen at position (0, 0)
        Debug_Printf(0,0,true,0,"Hello World!");

        // Refresh the screen - must be called to show the text / updates since last call
		LCD_Refresh();
	}
}
```

## 3. Build the game
We now have a basic game loop, and some text. Let's build the game.
```bash
make clean && make hhk
```
This command will delete the old build files and build the game.

Now copy the game to the calculator and run it.
You should see the text "Hello World!" on the screen, and be able to press the clear key to end the program.

## 4. Adding images
Now we can add images to the game. Let's add a square image to the game. You can use any 64x64 image for this tutorial, as long as it has a bit depth of 24 (RGB).

Using the python script `convert_textures.py`, we can convert the image to a texture that the classpad can use.

- Copy your image to the textures folder and name it `sqaure.png`.

- Run the python script: `python3 convert_textures.py`
- The script will create a new file in the res folder, named `square`.

Now, we can add the image to the game, by referencing the texture as `square`.

Before we can draw the image, we need to include the `draw_functions.hpp` file. Add it with the other includes at the top of the file.
```cpp
// main.cpp
#include <appdef.hpp>

#include "calc.hpp"
#include "draw_functions.hpp"
#include "lib/core/event_handler.hpp"
```

Let's draw the square on the screen.
```cpp
// main.cpp

// Load the texture, saving a pointer to it in the variable `myImage`
LOAD_TEXTURE_PTR("square", myImage);

// Game loop
while (game_running) {

    checkEvents();

    Debug_Printf(0,0,true,0,"Hello World!");

    // Draw the square on the screen at pixels (50, 50)
    DRAW_TEXTURE(myImage, 50, 50);

    LCD_Refresh();
}
```

Although this will work, it is not handling memory correctly. At the end of the program we need to free the memory allocated for the texture.

We will do this after the game loop.

```cpp
// main.cpp
free(myImage);
```

Before we build the game again, we need to add the texture to the classpad. This is done by copying the `res` folder to the root of the classpad's storage. If this is not done, the classpad will crash / freeze / throw an error.

Now let's build the game again.

```bash
make clean && make hhk
```
We should now see the square image on the screen. This is good and all, but we need to add a bit more to the game, maybe some movement.

Before we write the code, let's think about how we want to move the square.

- The box is constantly moving, but we want to make it bounce around the screen.
When the box hits the edge of the screen, we can change the direction of the movement. This can be done by multiplying the current direction by `-1`.

- Let's say that the box is moving to the right, and we want to change it to the left.

- We can multiply the X direction by `-1`.

- Or if the box is moving up, we can multiply the Y direction by `-1` once it hits the top of the screen.

Let's add the code to move the square, above the game loop.
```cpp
// main.cpp

// Size of the square
int8_t imageSize = 64;

// Starting position of the square (the middle of the screen)
// Note that width and height are defined in calc.hpp that is included in main.cpp
// As the origin is the top left corner, we need to subtract half the image size
int16_t imageX = width / 2 - imageSize / 2;
int16_t imageY = height / 2 - imageSize / 2;

// Direction of the square (+ = right, - = left) / (+ = up, - = down)
// Moves 8 pixels per frame in both x and y.
int8_t imageVelX = 8;
int8_t imageVelY = 8;
```

Now that we have our variables, let's add movement in the game loop
```cpp
// main.cpp
while (game_running) {

    checkEvents();

    Debug_Printf(0,0,true,0,"Hello World!");

    // Move the square
    imageX += imageVelX;
    imageY += imageVelY;

    // Check for left bound
    if (imageX < 0) {
        imageX = -imageX;
        imageVelX = -imageVelX;
    }

    // Check for right bound
    if (imageX > width - imageSize) {
        imageX = -imageX - 2 * imageSize + 2 * width;
        imageVelX = -imageVelX;
    }

    // Check for top bound
    if (imageY < 0) {
        imageVelY = -imageVelY;
    }

    // Check for bottom bound
    if (imageY + imageSize > height) {
        imageY = -imageY - 2 * imageSize + 2 * height;
        imageVelY = -imageVelY;
    }

    // Draw the square on the screen at pixels (imageX, imageY)
    // Replace the existing DRAW_TEXTURE line with this one.
    DRAW_TEXTURE(myImage, imageX, imageY);

    LCD_Refresh();
}
```

Build the game again, and run it. You should see the square moving around the screen. 

You may notice that as the square moves, the text "Hello World!" is sometimes no longer visible. This is because the sqaure is being drawn on top of the text.

To fix this, you can move the line to add the text after the square is drawn.

Congratulations, you have completed the tutorial!
