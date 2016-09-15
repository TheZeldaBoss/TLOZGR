#ifndef EVENT_H_
#define EVENT_H_

#include <SDL2/SDL.h>
#include "Hero.h"
bool execEvent(SDL_Event event, SDL_Window *window, Hero *hero, map);

#endif