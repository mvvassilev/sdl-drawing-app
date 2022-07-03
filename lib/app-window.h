#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include "../lib/draw.h"
#include "../lib/colors.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>

class AppWindow
{
private:
    SDL_Window *m_pSdlWindow;
    SDL_Event m_sdlEvent;
    SDL_Renderer *m_pRenderer;
    std::vector<std::vector<SDL_Point>> m_points;
    std::vector<SDL_Rect> m_rects;
    SDL_Rect m_rect;
    SDL_Color m_color;
    unsigned int m_flags;
    bool m_isRunning;
    bool m_clicked;
    int m_width;
    int m_height;
    int m_brushSize = 1;

    enum class SCREENSIZE
    {
        is1024x576,
        fullscreen
    } m_screenSize;

public:
    int start();
    SDL_Window *create();
    void set_brush_size(int);
    void set_color(Uint8, Uint8, Uint8, Uint8);
    void listen(SDL_Window *);
    void clean(SDL_Window *);
    void display_color_palette();
};
#endif // APP_WINDOW_H