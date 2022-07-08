#ifndef DRAW_H
#define DRAW_H

#include "../lib/colors.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <vector>

std::vector<std::vector<ColorPoint>> draw_squigle(
    SDL_Renderer *, SDL_Event *, bool *,
    std::vector<std::vector<ColorPoint>>,
    int, SDL_Color);
void draw_circle(SDL_Renderer *, int x, int y, int, SDL_Color);
void draw_line(SDL_Renderer *, int, int, int, int, int, SDL_Color);

#endif // DRAW_H