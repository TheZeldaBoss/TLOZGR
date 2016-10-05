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
	map *saveMap = dat->getMap();
	SDL_FreeSurface(dat->getFond());
	dat->setMap(newMap);
	int time = SDL_GetTicks();
	init(dat);
	//duree de la transition : 750 ms
	Uint32 a = SDL_GetTicks();
	SDL_Rect srcRect, dstRect, newSrcRect, newDstRect;
	/*
	**position horizontale
	*/
	if (dat->getHero()->getPosX() <= 20)//heros sur la gauche de l'ecran
		srcRect.x = 0;
	else if (dat->getHero()->getPosX() >= saveMap->getWidth() - 20)//heros sur la droite de l'ecran
		srcRect.x = (saveMap->getWidth() - 40) * 8;
	else//hero au milieu
		srcRect.x = (int)((dat->getHero()->getPosX() - 20) * 8);
	/*
	**Position verticale
	*/
	if (dat->getHero()->getPosY() <= 15)//heros en haut de l'ecran
		srcRect.y = 0;
	else if (dat->getHero()->getPosY() >= saveMap->getHeight() - 15)//heros en bas de l'ecran
		srcRect.y = (saveMap->getHeight() - 30) * 8;
	else//heros au milieu de l'ecran
		srcRect.y = (int)((dat->getHero()->getPosY() - 15) * 8);
	srcRect.w = 320;
	srcRect.h = 240;
	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.w = 640;
	dstRect.h = 480;
	if (abs(direction) == 1)
	{
		if (dat->getHero()->getPosX() <= 20)//gauche
			newSrcRect.x = 0;
		else if (dat->getHero()->getPosX() >= dat->getMap()->getWidth() - 20)//droite
			newSrcRect.x = (dat->getMap()->getWidth() - 40) * 8;
		else
			newSrcRect.x = (int)((dat->getHero()->getPosX() - 20) * 8);//milieu
	}
	else
	{
		if (direction > 0)
			newSrcRect.x = 0;
		else
			newSrcRect.x = (dat->getMap()->getWidth() - 40) * 8;
	}
	if (abs(direction) == 2)
	{
		if (dat->getHero()->getPosY() <= 15)//haut
			newSrcRect.y = 0;
		else if (dat->getHero()->getPosY() >= dat->getMap()->getHeight() - 15)//bas
			newSrcRect.y = ((dat->getMap()->getHeight() - 30) * 8);
		else//milieu
			newSrcRect.y = (int)((dat->getHero()->getPosY() - 15) * 8);
	}
	else
	{
		if (direction > 0)
			newSrcRect.y = 0;
		else
			newSrcRect.y = (dat->getMap()->getHeight() - 30) * 8;
	}
	newSrcRect.w = 320;
	newSrcRect.h = 240;
	newDstRect.x = 0;
	newDstRect.y = 0;
	newDstRect.w = 640;
	newDstRect.h = 480;
	if (abs(direction) == 1)//mouvement vertical
	for (unsigned int i = 0; i < 480; i++)
	{
		if (direction < 0)//vers le haut
		{
			dstRect.y = i;
			newDstRect.y = i - 480;
		}
		else//vers le bas
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
		if (15 - time > 0)
		{
			Sleep(15 - time);
		}
	}
	else//mouvement horizontal
	for (unsigned int i = 0; i < 640; i++)
	{
		if (direction < 0)//vers la gauche
		{
			dstRect.x = i;
			newDstRect.x = i - 640;
		}
		else//vers la droite
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
	if (abs(direction) == 2)
	{
		if (direction > 0)
			dat->getHero()->setPosX(0);
		else
			dat->getHero()->setPosX((float)newMap->getWidth());
	}
	else
	{
		if (direction > 0)
			dat->getHero()->setPosY(3);
		else
			dat->getHero()->setPosY((float)newMap->getHeight());
	}
	return (dat);
}