#include "../lib/draw.h"

void draw_squigle(SDL_Renderer *pRenderer, SDL_Event *pSdlEvent, bool *pClicked, std::vector<SDL_Point> *pPoints)
{
    if (pSdlEvent->type == SDL_MOUSEBUTTONDOWN)
    {
        if (pSdlEvent->button.button == SDL_BUTTON_LEFT)
            *pClicked = true;
    }
    else if (pSdlEvent->type == SDL_MOUSEMOTION && *pClicked)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        pPoints->push_back({x, y});
    }

    SDL_SetRenderDrawColor(pRenderer, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);
    SDL_RenderClear(pRenderer);

    SDL_SetRenderDrawColor(pRenderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, COLOR_BLACK.a);

    for (auto &point : *pPoints)
        SDL_RenderDrawPoint(pRenderer, point.x, point.y);

    SDL_RenderPresent(pRenderer);
}