#include "../lib/app-window.h"

void AppWindow::clean(SDL_Window *m_pSdlWindow)
{
    SDL_DestroyWindow(m_pSdlWindow);
    SDL_Quit();
}

void AppWindow::listen(SDL_Window *m_pSdlWindow)
{
    m_isRunning = true;
    m_clicked = false;
    while (m_isRunning)
    {
        // events
        while (SDL_PollEvent(&m_sdlEvent) != 0)
        {
            if (m_sdlEvent.type == SDL_QUIT)
            {
                m_isRunning = false;
            }
            else if (m_sdlEvent.type == SDL_KEYDOWN)
            {
                switch (m_sdlEvent.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    m_isRunning = false;
                    break;
                case SDLK_F11:
                    if (m_screenSize != SCREENSIZE::fullscreen)
                    {
                        m_screenSize = SCREENSIZE::fullscreen;
                        SDL_SetWindowFullscreen(m_pSdlWindow, m_flags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                    }
                    else
                    {
                        m_screenSize = SCREENSIZE::is1024x576;
                        SDL_SetWindowFullscreen(m_pSdlWindow, m_flags);
                    }
                    SDL_GetWindowSize(m_pSdlWindow, &m_width, &m_height);
                    break;
                }
            }
            m_points = draw_squigle(m_pRenderer, &m_sdlEvent, &m_clicked, m_points, m_brushSize);
            display_color_palette();

            SDL_RenderPresent(m_pRenderer);
        }
    }
}

void AppWindow::display_color_palette()
{
    Uint8 startX = 10;
    Uint8 startY = 10;
    Uint8 len = 150;
    Uint8 size = 5;
    Uint8 border = 3;

    // Border
    SDL_SetRenderDrawColor(m_pRenderer, 10, 10, 10, 0); // black
    SDL_Rect r = {startX - border, startY - border, startX + len + border - 1, len + border * 2};
    SDL_RenderFillRect(m_pRenderer, &r);

    // Palette
    for (Uint8 row = startY; row < startY + len; row += size)
    {
        for (Uint8 col = startX; col <= startX + len; col += size)
        {
            SDL_Rect r = {col, row, size, size};
            Uint8 blue = Uint8((col + row) / 2);
            SDL_SetRenderDrawColor(m_pRenderer, col - startX, row - startY, blue, 0);
            SDL_RenderFillRect(m_pRenderer, &r);
        }
    }
}

SDL_Window *AppWindow::create()
{
    m_pSdlWindow = nullptr;
    m_width = 1024;
    m_height = 576;
    m_flags = SDL_WINDOW_OPENGL;
    m_color = COLOR_WHITE;

    enum class SCREENSIZE
    {
        is1024x576,
        fullscreen
    } m_screenSize = SCREENSIZE::is1024x576;

    m_pSdlWindow = SDL_CreateWindow(
        "Drawing App",          // window title
        SDL_WINDOWPOS_CENTERED, // initial x position
        SDL_WINDOWPOS_CENTERED, // initial y position
        m_width,                // width, in pixels
        m_height,               // height, in pixels
        m_flags                 // flags - see below
    );

    m_pRenderer = SDL_CreateRenderer(m_pSdlWindow, -1, SDL_RENDERER_ACCELERATED);
    return m_pSdlWindow;
}

void AppWindow::set_brush_size(int size)
{
    m_brushSize = size;
}

void AppWindow::set_color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    m_color = {red, green, blue, alpha};
}

int AppWindow::start()
{
    m_pSdlWindow = create();
    listen(m_pSdlWindow);
    clean(m_pSdlWindow);
    return 0;
}
