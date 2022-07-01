#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include "../lib/draw.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>

class AppWindow
{
private:
    SDL_Window *m_pSdlWindow;
    SDL_Event m_sdlEvent;
    SDL_Renderer *m_pRenderer;
    std::vector<SDL_Point> m_points;
    std::vector<SDL_Rect> m_rects;
    SDL_Rect m_rect;
    SDL_Color m_color;
    unsigned int m_flags;
    bool m_isRunning;
    bool m_clicked;
    int m_width;
    int m_height;

    enum class SCREENSIZE
    {
        is1024x576,
        fullscreen
    } m_screenSize;

public:
    int start();
    SDL_Window *create();
    void listen(SDL_Window *);
    void clean(SDL_Window *);
};
#endif // APP_WINDOW_H