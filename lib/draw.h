#ifndef DRAW_H
#define DRAW_H

#include "../lib/colors.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <vector>

void draw_squigle(SDL_Renderer *, SDL_Event *, bool *, std::vector<SDL_Point> *);
void draw_rectangle(SDL_Event, SDL_Renderer *);
void draw_circle(SDL_Event, SDL_Renderer *);

#endif // DRAW_H