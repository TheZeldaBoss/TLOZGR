#ifndef DRAWMAP
#define DRAWMAP
#include <vector>
#include "Map.h"
#include <SDL2/SDL.h>
#include "Hero.h"

int DrawMap(map, SDL_Window *, Hero hero, bool drawAll = false);
SDL_Window *initWindow();
int closeWindow(SDL_Window *);


#endif /*DRAWMAP*/