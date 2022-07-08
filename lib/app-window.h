#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include "../lib/draw.h"
#include "../lib/colors.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>

#define OUTPUT_FILE_FORMAT "../out/%Y%m%d_%H%M%S"

class AppWindow
{
private:
    SDL_Window *m_pSdlWindow;
    SDL_Renderer *m_pRenderer;
    SDL_Texture *m_pTexture;
    SDL_Surface *m_pSurface;
    SDL_Event m_sdlEvent;
    std::vector<std::vector<ColorPoint>> m_points;
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

    enum class TOOL
    {
        usingPencil,
        usingEraser
    } m_tool;

public:
    int start();
    SDL_Window *create();
    void display_icons();
    void change_tool();
    void change_color();
    void set_tool_pencil(int, int, int);
    void set_tool_eraser(int, int, int);
    void set_brush_size(int);
    void set_color(SDL_Color);
    void listen(SDL_Window *);
    void clean(SDL_Window *);
    void display_color_palette();
    void display_tools_border();
    void save_to_file();
};
#endif // APP_WINDOW_H