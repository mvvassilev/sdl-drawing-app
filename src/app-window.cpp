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
        // 1. check events
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
            else if (m_sdlEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                if (m_sdlEvent.button.button == SDL_BUTTON_LEFT)
                    m_clicked = true;
            }
            else if (m_sdlEvent.type == SDL_MOUSEMOTION && m_clicked)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                m_points.push_back({x, y});
            }
            // render
            SDL_SetRenderDrawColor(m_pRenderer, m_color.r, m_color.g, m_color.b, m_color.a); // black
            SDL_RenderClear(m_pRenderer);

            SDL_SetRenderDrawColor(m_pRenderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, COLOR_BLACK.a); // black

            for (auto &point : m_points)
                SDL_RenderDrawPoint(m_pRenderer, point.x, point.y);

            // swap to new updated screen to render
            SDL_RenderPresent(m_pRenderer);
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

int AppWindow::start()
{
    m_pSdlWindow = create();
    listen(m_pSdlWindow);
    clean(m_pSdlWindow);
    return 0;
}
