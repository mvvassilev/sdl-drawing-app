#include "../lib/app-window.h"

void AppWindow::clean(SDL_Window *m_pSdlWindow)
{
    SDL_DestroyWindow(m_pSdlWindow);
    SDL_Quit();
}

void AppWindow::listen(SDL_Window *m_pSdlWindow)
{
    bool isRunning = true;
    while (isRunning)
    {
        // 1. check events
        while (SDL_PollEvent(&m_sdlEvent) != 0)
        {
            if (m_sdlEvent.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (m_sdlEvent.type == SDL_KEYDOWN)
            {
                switch (m_sdlEvent.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                case SDLK_F11:
                    if (m_currScreenSize != SCREENSIZE::fullscreen) // then set it to fullscreen and save prev state
                    {
                        m_lastNonFullScreenSize = m_currScreenSize;
                        m_currScreenSize = SCREENSIZE::fullscreen;
                        SDL_SetWindowFullscreen(m_pSdlWindow, m_flags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                    }
                    else // is currently fullscreen, set it back to the prev state
                    {
                        m_currScreenSize = m_lastNonFullScreenSize;
                        SDL_SetWindowFullscreen(m_pSdlWindow, m_flags);
                    }
                    SDL_GetWindowSize(m_pSdlWindow, &m_width, &m_height);
                    glViewport(0, 0, m_width, m_height);
                    break;
                case SDLK_F10: // toggle screensizes, does nothing if fullscreen
                    switch (m_currScreenSize)
                    {
                    case SCREENSIZE::fullscreen:
                        break;
                    case SCREENSIZE::is640x480:
                        m_currScreenSize = SCREENSIZE::is1366x768;
                        SDL_SetWindowSize(m_pSdlWindow, 1366, 768);
                        SDL_GetWindowSize(m_pSdlWindow, &m_width, &m_height);
                        glViewport(0, 0, m_width, m_height);
                        break;
                    case SCREENSIZE::is1366x768:
                        m_currScreenSize = SCREENSIZE::is640x480;
                        SDL_SetWindowSize(m_pSdlWindow, 640, 480);
                        SDL_GetWindowSize(m_pSdlWindow, &m_width, &m_height);
                        glViewport(0, 0, m_width, m_height);
                        break;
                    }
                    break;
                }
            }

            // 2. update screen

            // clear screen
            glClear(GL_COLOR_BUFFER_BIT);

            // add new updates
            // your updated stuff to render here (future todo)

            // swap to new updated screen to render
            SDL_GL_SwapWindow(m_pSdlWindow);
        }
    }
}

int AppWindow::start()
{
    SDL_Window *m_pSdlWindow = nullptr;
    int m_width = 1280;
    int m_height = 720;
    unsigned int m_flags = SDL_WINDOW_OPENGL;

    enum class SCREENSIZE
    {
        is640x480,
        is1366x768,
        fullscreen
    } m_currScreenSize = SCREENSIZE::is640x480,
      m_lastNonFullScreenSize = SCREENSIZE::is640x480;

    m_pSdlWindow = SDL_CreateWindow(
        "Drawing App",           // window title
        SDL_WINDOWPOS_UNDEFINED, // initial x position
        SDL_WINDOWPOS_UNDEFINED, // initial y position
        m_width,                 // width, in pixels
        m_height,                // height, in pixels
        m_flags                  // flags - see below
    );

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GLContext Context = SDL_GL_CreateContext(m_pSdlWindow);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // white background
    glViewport(0, 0, m_width, m_height);

    listen(m_pSdlWindow);
    clean(m_pSdlWindow);
    return 0;
}
