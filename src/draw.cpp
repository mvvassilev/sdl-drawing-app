#include "../lib/draw.h"

std::vector<std::vector<SDL_Point>> draw_squigle(SDL_Renderer *pRenderer,
                                                 SDL_Event *pSdlEvent, bool *pClicked,
                                                 std::vector<std::vector<SDL_Point>> points,
                                                 int brushSize,
                                                 SDL_Color color)
{
    if (pSdlEvent->type == SDL_MOUSEBUTTONDOWN)
    {
        if (pSdlEvent->button.button == SDL_BUTTON_LEFT)
        {
            *pClicked = true;
            points.push_back(std::vector<SDL_Point>());
        }
    }
    else if (pSdlEvent->type == SDL_MOUSEBUTTONUP)
    {
        if (pSdlEvent->button.button == SDL_BUTTON_LEFT)
        {
            *pClicked = false;
        }
    }
    else if (pSdlEvent->type == SDL_MOUSEMOTION && *pClicked)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > 180 || y > 255) // check if inside tools border
            points[points.size() - 1].push_back({x, y});
    }

    SDL_SetRenderDrawColor(pRenderer, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);
    SDL_RenderClear(pRenderer);

    for (auto &vector : points)
    {
        for (int i = 0, j = 1; j < vector.size(); i++, j++)
        {
            draw_line(pRenderer, vector[i].x, vector[i].y,
                      vector[j].x, vector[j].y, brushSize, color);
            draw_circle(pRenderer, vector[i].x, vector[i].y, brushSize, color);
        }
    }
    return points;
}

void draw_circle(SDL_Renderer *pRenderer, int x, int y, int brushSize, SDL_Color color)
{
    for (int w = 0; w < brushSize * 2; w++)
    {
        for (int h = 0; h < brushSize * 2; h++)
        {
            int dx = brushSize - w; // horizontal
            int dy = brushSize - h; // vertical offset
            if ((dx * dx + dy * dy) <= (brushSize * brushSize))
            {
                SDL_SetRenderDrawColor(pRenderer, color.r, color.g, color.b, color.a);
                SDL_RenderDrawPoint(pRenderer, x + dx, y + dy);
            }
        }
    }
}

void draw_line(SDL_Renderer *pRenderer, int x1, int y1, int x2, int y2,
               int brushSize, SDL_Color color)
{
    for (int i = -brushSize; i <= brushSize; i++)
    {
        SDL_SetRenderDrawColor(pRenderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(pRenderer, x1 + i, y1 + i, x2 + i, y2 + i);
    }
}