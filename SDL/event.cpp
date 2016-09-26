#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include "DrawMap.h"
#include "Hero.h"
#include "Map.h"

bool execEvent(SDL_Event event, void *data)
{
	DataToDraw *dat;
	dat = (DataToDraw *)data;
	int actualPosScreenX = (int)(dat->getHero()->getPosXScreen());
	int actualPosScreenY = (int)(dat->getHero()->getPosYScreen());
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	//continuous-response keys
	if (keystate[SDL_SCANCODE_LEFT])
	{
		if (dat->getHero()->getPosX() >= 1)
		{
			if (dat->getMap()->getLayerWalls()[(int)(dat->getHero()->getPosY())][(int)(dat->getHero()->getPosX()) - 1] == 0)
			{
				dat->getHero()->setPosX(dat->getHero()->getPosX() - (float)0.125);
				if (dat->getHero()->getPosX() >= (dat->getMap()->getWidth() - 15))
					dat->getHero()->setPosXScreen(40 - dat->getMap()->getWidth() + dat->getHero()->getPosY());
				if (dat->getHero()->getPosX() <= 20)
					dat->getHero()->setPosXScreen(dat->getHero()->getPosX());
			}
			if (dat->getHero()->getPosYScreen() == actualPosScreenY && dat->getHero()->getPosXScreen() == actualPosScreenX)
				dat->setDrawAll(true);
		}
		dat->getHero()->setActualImage(dat->getHero()->getActualImage() + 1);
		if (dat->getHero()->getActualImage() > 10)
			dat->getHero()->setActualImage(0);
		dat->getHero()->setActualPos(1);
		DrawMap(data, dat->getHero()->getActualImage(), 1);
	}
	if (keystate[SDL_SCANCODE_RIGHT])
	{
		if (dat->getHero()->getPosX() < (dat->getMap()->getWidth() - 1))
		{
			if (dat->getMap()->getLayerWalls()[(int)(dat->getHero()->getPosY())][(int)(dat->getHero()->getPosX()) + 1] == 0)
			{
				dat->getHero()->setPosX(dat->getHero()->getPosX() + (float)0.125);
				if (dat->getHero()->getPosX() >= (dat->getMap()->getWidth() - 15))
					dat->getHero()->setPosXScreen(40 - dat->getMap()->getWidth() + dat->getHero()->getPosY());
				if (dat->getHero()->getPosX() <= 20)
					dat->getHero()->setPosXScreen(dat->getHero()->getPosX());
			}
		}
		if (dat->getHero()->getPosYScreen() == actualPosScreenY && dat->getHero()->getPosXScreen() == actualPosScreenX)
			dat->setDrawAll(true);
		dat->getHero()->setActualImage(dat->getHero()->getActualImage() + 1);
		if (dat->getHero()->getActualImage() > 10)
			dat->getHero()->setActualImage(0);
		dat->getHero()->setActualPos(3);
		DrawMap(data, dat->getHero()->getActualImage(), 3);
	}
	if (keystate[SDL_SCANCODE_UP])
	{
		if (dat->getHero()->getPosY() >= 1)
		{
			if (dat->getMap()->getLayerWalls()[(int)(dat->getHero()->getPosY()) - 1][(int)(dat->getHero()->getPosX())] == 0)
			{
				dat->getHero()->setPosY(dat->getHero()->getPosY() - (float)(0.125));
				if (dat->getHero()->getPosY() >= dat->getMap()->getHeight() - 15)
					dat->getHero()->setPosYScreen(30 - dat->getMap()->getHeight() + dat->getHero()->getPosY());
				if (dat->getHero()->getPosY() <= 15)
					dat->getHero()->setPosYScreen(dat->getHero()->getPosY());
			}
		}
		if (dat->getHero()->getPosYScreen() == actualPosScreenY && dat->getHero()->getPosXScreen() == actualPosScreenX)
			dat->setDrawAll(true);
		dat->getHero()->setActualImage(dat->getHero()->getActualImage() + 1);
		if (dat->getHero()->getActualImage() > 10)
			dat->getHero()->setActualImage(0);
		dat->getHero()->setActualPos(2);
	}
	if (keystate[SDL_SCANCODE_DOWN])
	{
		if (dat->getHero()->getPosY() < dat->getMap()->getHeight() - 1)
		{
			if (dat->getMap()->getLayerWalls()[(int)(dat->getHero()->getPosY()) + 1][(int)(dat->getHero()->getPosX())] == 0)
			{
				dat->getHero()->setPosY(dat->getHero()->getPosY() + (float)(0.125));
				if (dat->getHero()->getPosY() >= dat->getMap()->getHeight() - 15)
					dat->getHero()->setPosYScreen(30 - dat->getMap()->getHeight() + dat->getHero()->getPosY());
				if (dat->getHero()->getPosY() <= 15)
					dat->getHero()->setPosYScreen(dat->getHero()->getPosY());
			}
		}
		if (dat->getHero()->getPosYScreen() == actualPosScreenY && dat->getHero()->getPosXScreen() == actualPosScreenX)
			dat->setDrawAll(true);

		dat->getHero()->setActualImage(dat->getHero()->getActualImage() + 1);
		if (dat->getHero()->getActualImage() > 10)
			dat->getHero()->setActualImage(0);
		dat->getHero()->setActualPos(0);
	}
	if (!(keystate[SDL_SCANCODE_LEFT]) && !(keystate[SDL_SCANCODE_RIGHT]) && !(keystate[SDL_SCANCODE_UP]) && !(keystate[SDL_SCANCODE_DOWN]))
		dat->getHero()->setActualImage(0);
	DrawMap(data, dat->getHero()->getActualImage(), dat->getHero()->getActualPos());
	switch (event.type)
	{
	case SDL_QUIT:
		closeWindow(dat->getWindow());
		return (true);
		break;
	case SDL_KEYUP:
		dat->getHero()->setActualImage(0);
	default:
		break;
	}
	return (false);
}