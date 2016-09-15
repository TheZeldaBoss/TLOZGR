#include <SDL2/SDL.h>
#include "DrawMap.h"
#include "Hero.h"
#include "Map.h"

bool execEvent(SDL_Event event, SDL_Window *window, Hero *hero, map testMap)
{
	switch (event.type)
	{
	case SDL_QUIT:
		closeWindow(window);
		return (true);
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			if (testMap.getLayerWalls()[hero->getPosY() - 1][hero->getPosX()] == 0)
			{
				hero->setPosY(hero->getPosY() - 1);
				if (hero->getPosY() > testMap.getHeight() - 15)
					hero->setPosYScreen(30 - testMap.getHeight() + hero->getPosY());
				if (hero->getPosY() < 15)
					hero->setPosYScreen(hero->getPosY());
			}
			DrawMap(testMap, window, *hero, true);
			break;
		case SDLK_DOWN:
			if (testMap.getLayerWalls()[hero->getPosY() + 1][hero->getPosX()] == 0)
			{
				hero->setPosY(hero->getPosY() + 1);
				if (hero->getPosY() > testMap.getHeight() - 15)
					hero->setPosYScreen(30 - testMap.getHeight() + hero->getPosY());
				if (hero->getPosY() < 15)
					hero->setPosYScreen(hero->getPosY());
			}
			DrawMap(testMap, window, *hero, true);
			break;
		case SDLK_RIGHT:
			if (testMap.getLayerWalls()[hero->getPosY()][hero->getPosX() + 1] == 0)
			{
				hero->setPosX(hero->getPosX() + 1);
				if (hero->getPosX() > (testMap.getWidth() - 15))
					hero->setPosXScreen(40 - testMap.getWidth() + hero->getPosY());
				if (hero->getPosX() < 20)
					hero->setPosXScreen(hero->getPosX());
			}
			DrawMap(testMap, window, *hero, true);
			break;
		case SDLK_LEFT:
			if (testMap.getLayerWalls()[hero->getPosY()][hero->getPosX() - 1] == 0)
			{
				hero->setPosX(hero->getPosX() - 1);
				if (hero->getPosX() > (testMap.getWidth() - 15))
					hero->setPosXScreen(40 - testMap.getWidth() + hero->getPosY());
				if (hero->getPosX() < 20)
					hero->setPosXScreen(hero->getPosX());
				DrawMap(testMap, window, *hero, true);
				break;
			}
		}
	default:
		break;
	}
	return (false);
}