#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>

class AppWindow
{
private:
    SDL_Window *m_pSdlWindow;
    SDL_Event m_sdlEvent;
    unsigned int m_flags;
    bool m_isRunning;
    int m_width;
    int m_height;

    enum class SCREENSIZE
    {
        is640x480,
        is1366x768,
        fullscreen
    } m_currScreenSize,
        m_lastNonFullScreenSize;

public:
    int start();
    void clean(SDL_Window *);
    void listen(SDL_Window *);
};
#endif // APP_WINDOW_H