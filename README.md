# sdl-drawing-app
An SDL drawing program that runs on the Linux desktop

# Description

Draws and erases pixels on the canvas based on the current selected color from the palette. You can save your image in the /out directroy and its name will be "YYYYMMDD_HHMMSS" based on the current date and time

# Run

The program is already built, so just run:

> cd build

> ./sdl-drawing-app

# Build

NOTE: The project is already built! If you build it after you made changes it might not work properly!

In your project root directory run the following:

> cmake --build build --config Release --target all --

This will generate a binary "sdl-drawing-app" in your "build" directory

# Usage

Use the "Pencil" tool to draw with the specified color from the palette. Use the "Eraser" tool to erase stuff from the screen. Use the "Save" button to save the image to your "out" directory
