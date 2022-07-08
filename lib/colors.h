#ifndef COLORS_H
#define COLORS_H

#include <SDL2/SDL.h>

struct ColorPoint
{
    SDL_Rect rect;
    SDL_Color color;
};

const SDL_Color COLOR_BLACK = {0, 0, 0, 255};
const SDL_Color COLOR_WHITE = {255, 255, 255, 255};
const SDL_Color COLOR_RED = {255, 0, 0, 255};
const SDL_Color COLOR_BLUE = {0, 0, 255, 255};
const SDL_Color COLOR_YELLOW = {255, 255, 255, 255};
const SDL_Color COLOR_GREEN = {0, 255, 0, 255};
const SDL_Color COLOR_GREY = {140, 140, 140, 255};

#endif // COLORS_H