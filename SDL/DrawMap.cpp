#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "DrawMap.h"
#include "Map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Hero.h"
extern std::vector<std::string> tilesetNames;
extern std::vector<int> tilesetWidths;
extern std::vector<int> tilesetHeights;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
uint32 rmask = 0xff000000, gmask = 0x00ff0000, bmask = 0x0000ff00, amask = 0x000000ff;
#else
Uint32 rmask = 0x000000ff, gmask = 0x0000ff00, bmask = 0x00ff0000, amask = 0xff000000;
#endif

DataToDraw::DataToDraw()
{
	this->actualMap = NULL;
	this->window = NULL;
	this->hero = NULL;
	this->drawAll = false;
}

DataToDraw::DataToDraw(map *newMap, SDL_Window *win, Hero *hero, bool drawAll)
{
	this->actualMap = newMap;
	this->window = win;
	this->hero = hero;
	this->drawAll = drawAll;
}

map *DataToDraw::getMap()
{
	return(this->actualMap);
}

void DataToDraw::setMap(map *newMap)
{
	this->actualMap = newMap;
}

SDL_Window *DataToDraw::getWindow()
{
	return (this->window);
}

void DataToDraw::setWindow(SDL_Window *win)
{
	this->window = win;
}

Hero *DataToDraw::getHero()
{
	return (this->hero);
}

void DataToDraw::setHero(Hero *hero)
{
	this->hero = hero;
}

bool DataToDraw::getDrawAll()
{
	return (this->drawAll);
}

void DataToDraw::setDrawAll(bool drawAll)
{
	this->drawAll = drawAll;
}

SDL_Renderer *DataToDraw::getRenderer()
{
	return (pRenderer);
}

void DataToDraw::setRenderer(SDL_Renderer *render)
{
	this->pRenderer = render;
}

SDL_Surface *DataToDraw::getFond()
{
	return (this->pFond);
}

void DataToDraw::setFond(SDL_Surface *fond)
{
	this->pFond = fond;
}

SDL_Surface *DataToDraw::getLink()
{
	return (pLink);
}

void DataToDraw::setLink(SDL_Surface *link)
{
	this->pLink = link;
}

SDL_Texture *DataToDraw::getTextureFloor()
{
	return (this->pTextureFloor);
}

void DataToDraw::setTextureFloor(SDL_Texture *texture)
{
	this->pTextureFloor = texture;
}

SDL_Texture *DataToDraw::getTextureCeiling()
{
	return (this->pTextureCeiling);
}

void DataToDraw::setTextureCeiling(SDL_Texture *texture)
{
	this->pTextureCeiling = texture;
}

SDL_Texture *DataToDraw::getTextureLink()
{
	return (this->pTextureLink);
}

void DataToDraw::setTextureLink(SDL_Texture *texture)
{
	this->pTextureLink = texture;
}

SDL_Surface *DataToDraw::getMapFloor()
{
	return (this->pMapFloor);
}

void DataToDraw::setMapFloor(SDL_Surface *mapFloor)
{
	this->pMapFloor = mapFloor;
}

SDL_Surface *DataToDraw::getMapCeiling()
{
	return (this->pMapCeiling);
}

void DataToDraw::setMapCeiling(SDL_Surface *mapCeiling)
{
	this->pMapCeiling = mapCeiling;
}

DataToDraw *DataToDraw::operator=(DataToDraw data)
{
	this->actualMap = data.getMap();
	this->window = data.getWindow();
	this->hero = data.getHero();
	this->drawAll = data.getDrawAll();
	return (this);
}

SDL_Window *initWindow()
{
	SDL_Window *window(0);
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL init error" << std::endl;
		exit(1);
	}
	window = SDL_CreateWindow("LOZ Ganon's Revenge", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

	return (window);
}

int closeWindow(SDL_Window *window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}

void init(DataToDraw *dat)
{
	dat->setRenderer(SDL_CreateRenderer(dat->getWindow(), -1, SDL_RENDERER_ACCELERATED));
	if (!dat->getRenderer())
	{
		std::cerr << "renderer creation failed" << std::endl;
		exit(-1);
	}
	dat->setFond(IMG_Load(dat->getMap()->getTilesetName().c_str()));
	if (!dat->getFond())
	{
		std::cerr << "sprite creation failed" << std::endl;
		exit(-1);
	}
	dat->setLink(IMG_Load("./data/images/Link/Link_walk.png"));
	dat->setTextureLink(SDL_CreateTextureFromSurface(dat->getRenderer(), dat->getLink()));
	dat->setMapCeiling(SDL_CreateRGBSurface(0, dat->getMap()->getWidth() * 8, dat->getMap()->getHeight() * 8, 32, rmask, gmask, bmask, amask));
	dat->setMapFloor(SDL_CreateRGBSurface(0, dat->getMap()->getWidth() * 8, dat->getMap()->getHeight() * 8, 32, rmask, gmask, bmask, amask));
	for (int i = 0; i < dat->getMap()->getWidth(); i++)
	{
		for (int j = 0; j < dat->getMap()->getHeight(); j++)
		{
			SDL_Rect srcPos;
			SDL_Rect dstPos;
			srcPos.w = 8;
			srcPos.h = 8;
			dstPos.x = i * 8;
			dstPos.y = j * 8;
			dstPos.w = dstPos.h = 8;
			//floor
			srcPos.x = ((dat->getMap()->getLayerFloor()[j][i] - 1) % tilesetWidths[dat->getMap()->getTilesetValue()]) * 8;
			srcPos.y = ((dat->getMap()->getLayerFloor()[j][i] - 1) / tilesetWidths[dat->getMap()->getTilesetValue()]) * 8;
			SDL_BlitSurface(dat->getFond(), &srcPos, dat->getMapFloor(), &dstPos);
			srcPos.x = ((dat->getMap()->getLayerWalls()[j][i] - 1) % tilesetWidths[dat->getMap()->getTilesetValue()])*8;
			srcPos.y = ((dat->getMap()->getLayerWalls()[j][i] - 1) / tilesetWidths[dat->getMap()->getTilesetValue()])*8;
			SDL_BlitSurface(dat->getFond(), &srcPos, dat->getMapFloor(), &dstPos);
		}
	}
	dat->setTextureFloor(SDL_CreateTextureFromSurface(dat->getRenderer(), dat->getMapFloor()));
	//ceiling
	for (int i = 0; i < dat->getMap()->getWidth(); i++)
	{
		for (int j = 0; j < dat->getMap()->getHeight(); j++)
		{
			SDL_Rect srcPos;
			SDL_Rect dstPos;
			srcPos.w = 8;
			srcPos.h = 8;
			dstPos.x = i * 8;
			dstPos.y = j * 8;
			dstPos.w = dstPos.h = 8;
			//ceiling
			srcPos.x = ((dat->getMap()->getLayerCeiling()[j][i] - 1) % tilesetWidths[dat->getMap()->getTilesetValue()]) * 8;
			srcPos.y = ((dat->getMap()->getLayerCeiling()[j][i] - 1) / tilesetWidths[dat->getMap()->getTilesetValue()]) * 8;
			SDL_BlitSurface(dat->getFond(), &srcPos, dat->getMapCeiling(), &dstPos);
		}
	}
	dat->setTextureCeiling(SDL_CreateTextureFromSurface(dat->getRenderer(), dat->getMapCeiling()));
}

void destroy(DataToDraw *dat)
{
	SDL_DestroyTexture(dat->getTextureFloor());
	SDL_DestroyTexture(dat->getTextureCeiling());
	SDL_FreeSurface(dat->getFond());
	SDL_DestroyRenderer(dat->getRenderer());
}

int DrawMap(void *data, int pictureHeroX, int pictureHeroY)
{
	DataToDraw *dat;
	dat = (DataToDraw *)data;

	int tilesetWidth = tilesetWidths[dat->getMap()->getTilesetValue()];
	int tilesetHeight = tilesetHeights[dat->getMap()->getTilesetValue()];
	float xOrig;//coord x de l'affichage de la map
	float yOrig;//coord y de l'affichage de la map
	if (dat->getHero()->getPosX() <= 20)//partie gauche
		xOrig = 0;
	else if (dat->getHero()->getPosX() > (dat->getMap()->getWidth() - 20))//partie droite
		xOrig = (float)dat->getMap()->getWidth() - 40;
	else//milieu
		xOrig = (float)(dat->getHero()->getPosX()) - 20;

	if (dat->getHero()->getPosY() <= 15)
		yOrig = 0;
	else if (dat->getHero()->getPosY() > (dat->getMap()->getHeight() - 15))
		yOrig = (float)dat->getMap()->getHeight() - 30;
	else
		yOrig = (float)(dat->getHero()->getPosY()) - 15;
	SDL_Rect srcRect, dstRect;
	SDL_Rect srcHero, dstHero;
	srcRect.x = (int)(xOrig * 8);
	srcRect.y = (int)(yOrig * 8);
	srcRect.w = 320;
	srcRect.h = 240;
	dstRect.x = dstRect.y = 0;
	dstRect.w = 640;
	dstRect.h = 480;
	srcHero.x = pictureHeroX * 24;
	srcHero.y = pictureHeroY * 32;
	srcHero.w = 24;
	srcHero.h = 32;
	//partie gauche map
	if (dat->getHero()->getPosX() <= 20)
		dstHero.x = (int)(((dat->getHero()->getPosX()) * 16) - 24);
	//partie droite map
	else if (dat->getHero()->getPosX() > dat->getMap()->getWidth() - 20)
		dstHero.x = (int)(((40 - (((dat->getMap()->getWidth()) - (dat->getHero()->getPosX())))) * 16) - 24);
	//milieu map
	else
		dstHero.x = 320 - 24;
	//partie haute map
	if (dat->getHero()->getPosY() <= 15)
		dstHero.y = (int)(((dat->getHero()->getPosY()) * 16) - 48);
	//partie basse map
	else if (dat->getHero()->getPosY() > dat->getMap()->getHeight() - 15)
		dstHero.y = (int)(((30 - (((dat->getMap()->getHeight()) - (dat->getHero()->getPosY())))) * 16) - 48);
	//milieu map
	else
		dstHero.y = 240 - 48;
	dstHero.w = 48;
	dstHero.h = 64;
	SDL_RenderCopy(dat->getRenderer(), dat->getTextureFloor(), &srcRect, &dstRect);
	SDL_RenderCopy(dat->getRenderer(), dat->getTextureLink(), &srcHero, &dstHero);
	SDL_RenderCopy(dat->getRenderer(), dat->getTextureCeiling(), &srcRect, &dstRect);
	SDL_RenderPresent(dat->getRenderer());
	/*SDL_Surface *screen = SDL_GetWindowSurface(dat->getWindow());
	SDL_BlitSurface(dat->getMapFloor(), NULL, screen, NULL);
	SDL_UpdateWindowSurface(dat->getWindow());*/
	dat->setDrawAll(false);
	return (0);
}

