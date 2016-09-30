#include "Map.h"
#include "transitions.h"
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2/SDL_thread.h>
#include <Windows.h>

DataToDraw *transit(DataToDraw *dat, map *newMap, int direction)//-2 : gauche, -1 : haut, 1 : bas, 2 : droite
{
	SDL_Texture *saveFloor = dat->getTextureFloor();
	SDL_Texture *saveCeiling = dat->getTextureCeiling();
	SDL_FreeSurface(dat->getFond());
	dat->setMap(newMap);
	int time = SDL_GetTicks();
	init(dat);
	//duree de la transition : 750 ms
	Uint32 a = SDL_GetTicks();
	SDL_Rect srcRect, dstRect, newSrcRect, newDstRect;
	srcRect.x = (dat->getHero()->getPosX() <= 20 ? 0 : (dat->getHero()->getPosX() >= (dat->getMap()->getWidth()) - 20 ? (dat->getMap()->getWidth() - 40) * 8 : (int)(dat->getHero()->getPosX() - 20) * 8));
	srcRect.y = (dat->getHero()->getPosY() <= 20 ? 0 : (dat->getHero()->getPosY() >= (dat->getMap()->getHeight()) - 15 ? (dat->getMap()->getHeight() - 30) * 8 : (int)(dat->getHero()->getPosY() - 15) * 8));
	srcRect.w = 320;
	srcRect.h = 240;
	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.w = 640;
	dstRect.h = 480;
	if (abs(direction) == 1)
		newSrcRect.x = (dat->getHero()->getPosX() <= 20 ? 0 : (dat->getHero()->getPosX() >= (dat->getMap()->getWidth()) - 20 ? (dat->getMap()->getWidth() - 40) * 8 : (int)(dat->getHero()->getPosX() - 20) * 8));
	else
		newSrcRect.x = (abs(direction) > 0 ? 0 : dat->getMap()->getWidth() - 40);
	if (abs(direction) == 2)
		newSrcRect.y = (dat->getHero()->getPosY() <= 15 ? 0 : (dat->getHero()->getPosY() >= (dat->getMap()->getWidth()) - 15 ? (dat->getMap()->getWidth() - 30) * 8 : (int)(dat->getHero()->getPosY() - 15) * 8));
	else
		newSrcRect.y = newMap->getHeight() - 30;
	newSrcRect.w = 320;
	newSrcRect.h = 240;
	newDstRect.x = 0;
	newDstRect.y = 0;
	newDstRect.w = 640;
	newDstRect.h = 480;
	if (abs(direction) == 1)
	for (unsigned int i = 0; i < 480; i++)
	{
		if (direction < 0)
		{
			dstRect.y = i;
			newDstRect.y = i - 480;
		}
		else
		{
			dstRect.y = 0 - i;
			newDstRect.y = 480 - i;
		}
		SDL_RenderCopy(dat->getRenderer(), saveFloor, &srcRect, &dstRect);
		SDL_RenderCopy(dat->getRenderer(), saveCeiling, &srcRect, &dstRect);
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureFloor(), &newSrcRect, &newDstRect);
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureCeiling(), &newSrcRect, &newDstRect);
		SDL_RenderPresent(dat->getRenderer());
		time = SDL_GetTicks() - time;
		if (2 - time > 0)
		{
			Sleep(2 - time);
		}
	}
	else
	for (unsigned int i = 0; i < 640; i++)
	{
		if (direction < 0)
		{
			dstRect.x = i;
			newDstRect.x = i - 640;
		}
		else
		{
			dstRect.x = 0 - i;
			newDstRect.x = 640 - i;
		}
		SDL_RenderCopy(dat->getRenderer(), saveFloor, &srcRect, &dstRect);
		SDL_RenderCopy(dat->getRenderer(), saveCeiling, &srcRect, &dstRect);
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureFloor(), &newSrcRect, &newDstRect);
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureCeiling(), &newSrcRect, &newDstRect);
		SDL_RenderPresent(dat->getRenderer());
		time = SDL_GetTicks() - time;
		if (2 - time > 0)
		{
			Sleep(2 - time);
		}
	}
	
	SDL_DestroyTexture(saveFloor);
	SDL_DestroyTexture(saveCeiling);
	dat->getHero()->setPosY((float)newMap->getHeight() - 1);
	return (dat);
}