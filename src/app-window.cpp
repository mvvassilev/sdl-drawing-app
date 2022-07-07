#include "../lib/app-window.h"

void AppWindow::clean(SDL_Window *m_pSdlWindow)
{
    SDL_DestroyRenderer(m_pRenderer);
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
            switch (m_tool) // check current tool
            {
            case TOOL::usingPencil:
                m_points = draw_squigle(
                    m_pRenderer, &m_sdlEvent, &m_clicked,
                    m_points, m_brushSize, m_color);
                break;
            case TOOL::usingEraser:
                set_color(COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);
                m_points = draw_squigle(
                    m_pRenderer, &m_sdlEvent, &m_clicked,
                    m_points, m_brushSize, m_color);
                break;
            default:
                break;
            }
            save_to_file();
            change_tool();
            change_color();
            display_color_palette();
            display_icons();
            display_tools_border();
            SDL_RenderPresent(m_pRenderer);
        }
    }
    save_to_file();
}

void AppWindow::change_color()
{
    Uint8 startX = 10;
    Uint8 startY = 10;
    if (m_sdlEvent.type == SDL_MOUSEBUTTONDOWN)
    {
        if (m_sdlEvent.button.button == SDL_BUTTON_LEFT)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (10 <= x && x <= 170)
            {
                if (10 <= y && y <= 170)
                {
                    Uint8 red = x - startX;
                    Uint8 green = y - startY;
                    Uint8 blue = (red + green) / 2;
                    set_color(Uint8(red), Uint8(green), Uint8(blue), 0);
                }
            }
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
    SDL_Rect r = {startX - border,
                  startY - border,
                  startX + len + border - 1,
                  len + border * 2};
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

void AppWindow::display_tools_border()
{
    SDL_Rect x = {0, 253, 180, 2};
    SDL_Rect y = {178, 0, 2, 255};

    SDL_SetRenderDrawColor(m_pRenderer, 10, 10, 10, 0); // black
    SDL_RenderFillRect(m_pRenderer, &x);
    SDL_RenderFillRect(m_pRenderer, &y);
}

SDL_Window *AppWindow::create()
{
    m_pSdlWindow = nullptr;
    m_width = 1024;
    m_height = 576;
    m_flags = SDL_WINDOW_OPENGL;
    m_color = COLOR_WHITE;
    m_screenSize = SCREENSIZE::is1024x576;
    m_tool = TOOL::usingPencil;

    m_pSdlWindow = SDL_CreateWindow(
        "Drawing App",          // window title
        SDL_WINDOWPOS_CENTERED, // initial x position
        SDL_WINDOWPOS_CENTERED, // initial y position
        m_width,                // width, in pixels
        m_height,               // height, in pixels
        m_flags                 // flags - see below
    );

    m_pRenderer = SDL_CreateRenderer(m_pSdlWindow, -1, SDL_RENDERER_ACCELERATED);
    m_pSurface = SDL_GetWindowSurface(m_pSdlWindow);
    m_pTexture = SDL_CreateTexture(m_pRenderer, 8, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
    set_color(COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, COLOR_BLACK.a);
    return m_pSdlWindow;
}

void AppWindow::display_icons()
{
    int width;
    int height;
    SDL_Texture *pPencilIcon = IMG_LoadTexture(
        m_pRenderer, "../icons/pencil.png");
    SDL_Texture *pEraserIcon = IMG_LoadTexture(
        m_pRenderer, "../icons/eraser.png");
    SDL_Texture *pSaveIcon = IMG_LoadTexture(
        m_pRenderer, "../icons/save.png");

    SDL_QueryTexture(pPencilIcon, NULL, NULL, &width, &height);
    SDL_QueryTexture(pEraserIcon, NULL, NULL, &width, &height);
    SDL_QueryTexture(pSaveIcon, NULL, NULL, &width, &height);

    SDL_Rect pencil;
    pencil.x = 18;
    pencil.y = 175;
    pencil.w = width;
    pencil.h = height;

    SDL_Rect eraser;
    eraser.x = 100;
    eraser.y = 175;
    eraser.w = width;
    eraser.h = height;

    SDL_Rect save;
    save.x = 50;
    save.y = m_height - 100;
    save.w = width;
    save.h = height;

    SDL_RenderDrawRect(m_pRenderer, &pencil);
    SDL_RenderDrawRect(m_pRenderer, &eraser);
    SDL_RenderDrawRect(m_pRenderer, &save);

    SDL_RenderCopy(m_pRenderer, pPencilIcon, NULL, &pencil);
    SDL_RenderCopy(m_pRenderer, pEraserIcon, NULL, &eraser);
    SDL_RenderCopy(m_pRenderer, pSaveIcon, NULL, &save);
}

void AppWindow::change_tool()
{
    if (m_sdlEvent.type == SDL_MOUSEBUTTONDOWN)
    {
        if (m_sdlEvent.button.button == SDL_BUTTON_LEFT)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            set_tool_pencil(x, y, 1);
            set_tool_eraser(x, y, 1);
        }
    }
    else if (m_sdlEvent.type == SDL_MOUSEBUTTONUP)
    {
        if (m_sdlEvent.button.button == SDL_BUTTON_LEFT)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            set_tool_pencil(x, y, 0);
            set_tool_eraser(x, y, 0);
        }
    }
}

void AppWindow::set_tool_pencil(int x, int y, int isPressed)
{
    if (18 <= x && x <= 78)
    {
        if (175 <= y && y <= 235)
        {
            m_tool = TOOL::usingPencil;
            SDL_Rect pencil_shadow = {18, 175, 60, 60};
            switch (isPressed)
            {
            case 0:
                SDL_SetRenderDrawColor(
                    m_pRenderer,
                    COLOR_WHITE.r,
                    COLOR_WHITE.g,
                    COLOR_WHITE.b,
                    COLOR_WHITE.a);
                break;
            case 1:
                SDL_SetRenderDrawColor(
                    m_pRenderer,
                    COLOR_GREY.r,
                    COLOR_GREY.g,
                    COLOR_GREY.b,
                    COLOR_GREY.a);
                break;
            default:
                break;
            }
            SDL_RenderFillRect(m_pRenderer, &pencil_shadow);
        }
    }
}

void AppWindow::set_tool_eraser(int x, int y, int isPressed)
{
    if (100 <= x && x <= 160)
    {
        if (175 <= y && y <= 235)
        {
            m_tool = TOOL::usingEraser;
            SDL_Rect eraser_shadow = {100, 175, 60, 60};
            switch (isPressed)
            {
            case 0:
                SDL_SetRenderDrawColor(
                    m_pRenderer,
                    COLOR_WHITE.r,
                    COLOR_WHITE.g,
                    COLOR_WHITE.b,
                    COLOR_WHITE.a);
                break;
            case 1:
                SDL_SetRenderDrawColor(
                    m_pRenderer,
                    COLOR_GREY.r,
                    COLOR_GREY.g,
                    COLOR_GREY.b,
                    COLOR_GREY.a);
                break;
            default:
                break;
            }
            SDL_RenderFillRect(m_pRenderer, &eraser_shadow);
        }
    }
}

void AppWindow::set_brush_size(int size)
{
    m_brushSize = size;
}

void AppWindow::set_color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    m_color = {red, green, blue, alpha};
}

void AppWindow::save_to_file()
{
    if (m_sdlEvent.type == SDL_MOUSEBUTTONDOWN)
    {
        if (m_sdlEvent.button.button == SDL_BUTTON_LEFT)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (50 <= x && x <= 110 && m_height - 100 <= y && y <= m_height - 50)
            {
                SDL_Texture *target = SDL_GetRenderTarget(m_pRenderer);
                SDL_SetRenderTarget(m_pRenderer, m_pTexture);
                SDL_RenderReadPixels(m_pRenderer, NULL, m_pSurface->format->format, m_pSurface->pixels, m_pSurface->pitch);

                char filename[256] = "../out/image.png";
                IMG_SavePNG(m_pSurface, filename);
                SDL_FreeSurface(m_pSurface);
                SDL_SetRenderTarget(m_pRenderer, target);
                SDL_Rect save_shadow = {50, m_height - 100, 60, 60};
                SDL_SetRenderDrawColor(
                    m_pRenderer,
                    COLOR_GREY.r,
                    COLOR_GREY.g,
                    COLOR_GREY.b,
                    COLOR_GREY.a);
                SDL_RenderFillRect(m_pRenderer, &save_shadow);
            }
        }
    }
    if (m_sdlEvent.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (50 <= x && x <= 110 && m_height - 100 <= y && y <= m_height - 50)
        {
            SDL_Rect save_shadow = {50, m_height - 100, 60, 60};
            SDL_SetRenderDrawColor(
                m_pRenderer,
                COLOR_WHITE.r,
                COLOR_WHITE.g,
                COLOR_WHITE.b,
                COLOR_WHITE.a);
            SDL_RenderFillRect(m_pRenderer, &save_shadow);
        }
    }
}

int AppWindow::start()
{
    m_pSdlWindow = create();
    listen(m_pSdlWindow);
    clean(m_pSdlWindow);
    return 0;
}
