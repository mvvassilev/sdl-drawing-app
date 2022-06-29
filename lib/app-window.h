#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>

class AppWindow
{
public:
    SDL_Window *sdl_window;
    unsigned int window_flags;
    bool isRunning;
    SDL_Event sdl_event;
    int win_width = 640;
    int win_height = 480;

    enum class SCREENSIZE
    {
        is640x480,
        is1366x768,
        fullscreen
    } curr_screen_size,
        last_non_fullscreen_size;

    static int start();
    static int resizeCallback(void *data, SDL_Event *event);
    static int createWindow(SDL_Window *, unsigned int, int, int);
};
#endif // APP_WINDOW_H