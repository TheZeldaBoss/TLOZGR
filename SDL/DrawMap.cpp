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

seedToDraw::seedToDraw()
{
	this->posX = -1;
	this->posY = -1;
	this->seedExists = 0;
}

bombToDraw::bombToDraw()
{
	this->posX = -1;
	this->posY = -1;
	this->actualImage = -1;
}

arrowToDraw::arrowToDraw()
{
	this->posX = -1;
	this->posY = -1;
	this->actualImage = -1;
	this->actualPos = 0;
	drawIt = false;
}

hookToDraw::hookToDraw()
{
	this->posX = -1;
	this->posY = -1;
	this->actualImage = -1;
	this->hookshotExists = false;
}

int arrowToDraw::getActualPos()
{
	return actualPos;
}

void arrowToDraw::setActualPos(int i)
{
	this->actualPos = i;
}

float arrowToDraw::getPosX()
{
	return (this->posX);
}

void arrowToDraw::setPosX(float x)
{
	this->posX = x;
}

float arrowToDraw::getPosY()
{
	return (posY);
}

void  arrowToDraw::setPosY(float y)
{
	posY = y;
}

int   arrowToDraw::getActualImage()
{
	return (actualImage);
}

void  arrowToDraw::setActualImage(int newImage)
{
	actualImage = newImage;
}

fireSeedToDraw::fireSeedToDraw()
{
	actualImage = 0;
	posX = 0;
	posY = 0;
	fireSeedExists = false;
}

DataToDraw::DataToDraw()
{
	this->actualMap = NULL;
	this->window = NULL;
	this->hero = NULL;
	this->drawAll = false;
	this->needDraw = true;
	this->doTransition = 0;
	useObject = false;
}

DataToDraw::DataToDraw(map *newMap, SDL_Window *win, Hero *hero, bool drawAll)
{
	this->actualMap = newMap;
	this->window = win;
	this->hero = hero;
	this->drawAll = drawAll;
	this->needDraw = true;
	useObject = false;
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

SDL_Texture *DataToDraw::getTextureArrow()
{
	return (this->pTextureArrow);
}

void DataToDraw::setTextureArrow(SDL_Texture *texture)
{
	this->pTextureArrow = texture;
}

SDL_Texture *DataToDraw::getTextureBomb()
{
	return (this->pTextureBomb);
}

void DataToDraw::setTextureBomb(SDL_Texture *texture)
{
	this->pTextureBomb = texture;
}

SDL_Texture *DataToDraw::getTextureExplosion()
{
	return (this->pTextureExplosion);
}

void DataToDraw::setTextureExplosion(SDL_Texture *texture)
{
	this->pTextureExplosion = texture;
}

SDL_Texture *DataToDraw::getTextureSeed()
{
	return pTextureSeed;
}

void DataToDraw::setTextureSeed(SDL_Texture *texture)
{
	pTextureSeed = texture;
}

SDL_Texture *DataToDraw::getTextureHookshot()
{
	return pTextureHookshot;
}
void DataToDraw::setTextureHookshot(SDL_Texture *texture)
{
	this->pTextureHookshot = texture;
}

void DataToDraw::setTextureFireSeed(SDL_Texture *texture)
{
	pTextureFireSeed = texture;
}

SDL_Texture *DataToDraw::getTextureFireSeed()
{
	return pTextureFireSeed;
}

SDL_Window *initWindow()
{
	SDL_Window *window(0);
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL init error" << std::endl;
		exit(1);
	}
	window = SDL_CreateWindow("Legend of Zelda : Ganon's Revenge", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

	return (window);
}

int closeWindow(SDL_Window *window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}

void init_renderer(DataToDraw *dat)
{
	dat->setRenderer(SDL_CreateRenderer(dat->getWindow(), -1, SDL_RENDERER_ACCELERATED));
	if (!dat->getRenderer())
	{
		std::cerr << "renderer creation failed" << std::endl;
		exit(-1);
	}
}

void init(DataToDraw *dat)
{
	if (dat->getRenderer() == NULL)
		init_renderer(dat);
	dat->setFond(IMG_Load(dat->getMap()->getTilesetName().c_str()));
	if (!dat->getFond())
	{
		std::cerr << "sprite creation failed" << std::endl;
		exit(-1);
	}
	dat->setLink(IMG_Load("./data/images/Link/Link_walk.png"));
	dat->setTextureLink(SDL_CreateTextureFromSurface(dat->getRenderer(), dat->getLink()));
	dat->setTextureArrow(SDL_CreateTextureFromSurface(dat->getRenderer(), IMG_Load("./data/images/equipement/arrows.png")));
	dat->setTextureBomb(SDL_CreateTextureFromSurface(dat->getRenderer(), IMG_Load("./data/images/equipement/bombs.png")));
	dat->setTextureExplosion(SDL_CreateTextureFromSurface(dat->getRenderer(), IMG_Load("./data/images/equipement/explosion.png")));
	dat->setTextureSeed(SDL_CreateTextureFromSurface(dat->getRenderer(), IMG_Load("./data/images/equipement/seed.png")));
	dat->setTextureHookshot(SDL_CreateTextureFromSurface(dat->getRenderer(), IMG_Load("./data/images/equipement/hookshot.png")));
	dat->setTextureFireSeed(SDL_CreateTextureFromSurface(dat->getRenderer(), IMG_Load("./data/images/equipement/fireSeed.png")));
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
	Uint32 time = SDL_GetTicks();
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
	SDL_Rect srcArrow, dstArrow;
	SDL_Rect srcSeed, dstSeed;
	SDL_Rect srcBomb, dstBomb;
	SDL_Rect srcExplo, dstExplo;
	SDL_Rect srcHook, srcChain, dstHook, dstChain1, dstChain2, dstChain3;
	SDL_Rect srcFireSeed, dstFireSeed;
	srcSeed.x = srcSeed.y = 0;
	srcSeed.w = srcSeed.h = 16;
	srcRect.x = (int)(xOrig * 8);
	srcRect.y = (int)(yOrig * 8);
	srcRect.w = 320;
	srcRect.h = 240;
	dstRect.x = dstRect.y = 0;
	dstRect.w = 640;
	dstRect.h = 480;
	//deplacements simples
	if (dat->getHero()->getActualPos() < 4)
		srcHero.w = 24;
	//utilisation arc
	else if (4 <= dat->getHero()->getActualPos() && dat->getHero()->getActualPos() < 8 && dat->getHero()->getActualPos() % 2 == 1)
		srcHero.w = 32;
	//utilisation lance pierres
	else if (8 <= dat->getHero()->getActualPos() && dat->getHero()->getActualPos() < 12 && dat->getHero()->getActualPos() % 2 == 1)
		srcHero.w = 37;
	else
		srcHero.w = 24;
	srcHero.h = 37;
	if (dat->getHero())
	srcHero.x = pictureHeroX * srcHero.w;
	srcHero.y = pictureHeroY * srcHero.h;
	srcArrow.x = dat->arrow.getActualImage() * 16;
	srcArrow.y = dat->arrow.getActualPos() * 16;
	srcArrow.w = srcArrow.h = 16;
	srcBomb.x = dat->bomb.actualImage * 15;
	srcBomb.y = 0;
	srcBomb.w = 15;
	srcBomb.h = 21;
	srcExplo.x = dat->explosion.actualImage * 47;
	srcExplo.y = 0;
	srcExplo.w = 47;
	srcExplo.h = 51;
	srcHook.w = 16;
	srcHook.h = 16;
	srcHook.x = dat->hookshot.actualImage * srcHook.w;
	srcHook.y = (dat->getHero()->getActualPos() % 4) * srcHook.h;
	srcChain.x = srcChain.y = 0;
	srcChain.w = srcChain.h = 16;
	//partie gauche map
	if (dat->getHero()->getPosX() <= 20)
		dstHero.x = (int)(((dat->getHero()->getPosX()) * 16) - 24);
	//partie droite map
	else if (dat->getHero()->getPosX() > dat->getMap()->getWidth() - 20)
		dstHero.x = (int)(((40 - (((dat->getMap()->getWidth()) - (dat->getHero()->getPosX())))) * 16) - 24);
	//milieu map
	else
		dstHero.x = 320 - 24;
	if (dat->useObject == true && (dat->getHero()->getActualPos() % 4) == 1)
		dstHero.x -= 24;
	//partie haute map
	if (dat->getHero()->getPosY() <= 15)
		dstHero.y = (int)(((dat->getHero()->getPosY()) * 16) - 72);
	//partie basse map
	else if (dat->getHero()->getPosY() > dat->getMap()->getHeight() - 15)
		dstHero.y = (int)(((30 - (((dat->getMap()->getHeight()) - (dat->getHero()->getPosY())))) * 16) - 72);
	//milieu map
	else
		dstHero.y = 240 - 72;
	//utilisation arc vers le bas
	if (dat->useObject == true && dat->getHero()->getActualPos() == 4)
		dstHero.y += 18;
	//utilisation lance pierres vers le bas
	if (dat->useObject == true && dat->getHero()->getActualPos() == 8)
		dstHero.y += 24;
	//utilisation grappin vers la gauche
	if (dat->useObject == true && dat->getHero()->getActualPos() == 13)
		dstHero.x += 24;
	dstHero.w = srcHero.w * 2;
	dstHero.h = 74;
	dstSeed.w = dstSeed.h = 32;
	//gestion position graine
	if ((dat->seed.posX >= dat->getHero()->getPosX() - 20) && dat->seed.posX <= dat->getHero()->getPosX() + 20)
		dstSeed.x = dstHero.x - (int)((dat->getHero()->getPosX() - dat->seed.posX) * 16);
	if ((dat->seed.posY >= dat->getHero()->getPosY() - 20) && dat->seed.posY <= dat->getHero()->getPosY() + 20)
		dstSeed.y = dstHero.y - (int)((dat->getHero()->getPosY() - dat->seed.posY) * 16);
	//gestion position flèche
	if ((dat->arrow.getPosX() >= dat->getHero()->getPosX() - 20) && dat->arrow.getPosX() <= dat->getHero()->getPosX() + 20)
		dstArrow.x = dstHero.x - (int)((dat->getHero()->getPosX() - dat->arrow.getPosX()) * 16);
	if ((dat->arrow.getPosY() >= dat->getHero()->getPosY() - 20) && dat->arrow.getPosY() <= dat->getHero()->getPosY() + 15)
		dstArrow.y = dstHero.y - (int)((dat->getHero()->getPosY() - dat->arrow.getPosY()) * 16);
	dstArrow.w = 32;
	dstArrow.h = 32;
	//gestion position bombe;
	if ((dat->bomb.posX >= dat->getHero()->getPosX() - 20) && dat->bomb.posX <= dat->getHero()->getPosX() + 20)
		dstBomb.x = dstHero.x - (int)((dat->getHero()->getPosX() - dat->bomb.posX) * 16) + 12;
	if ((dat->bomb.posY >= dat->getHero()->getPosY() - 15) && dat->bomb.posY <= dat->getHero()->getPosY() + 15)
		dstBomb.y = dstHero.y - (int)((dat->getHero()->getPosY() - dat->bomb.posY) * 16) + 32;
	dstBomb.w = 30;
	dstBomb.h = 42;
	//gestion position explosion
	if ((dat->bomb.posX >= dat->getHero()->getPosX() - 20) && dat->bomb.posX <= dat->getHero()->getPosX() + 20)
		dstExplo.x = dstBomb.x - 32;
	if ((dat->bomb.posY >= dat->getHero()->getPosY() - 15) && dat->bomb.posY <= dat->getHero()->getPosY() + 15)
		dstExplo.y = dstBomb.y - 32;
	dstExplo.w = 94;
	dstExplo.h = 102;
	//gestion position grappin
	dstHook.w = 32;
	dstHook.h = 32;
	dstChain1.w = 16;
	dstChain1.h = 16;
	dstChain2.w = 16;
	dstChain2.h = 16;
	dstChain3.w = 16;
	dstChain3.h = 16;
	if (dat->getHero()->getActualPos() % 4 == 0)//bas
	{
		int originHook = dstHero.y + 66;
		dstHook.x = dstHero.x + 12;
		dstHook.y = dstHero.y + (int)((dat->hookshot.posY - (dat->getHero()->getPosY() - 3.5)) * 16);
		dstChain1.x = dstChain2.x = dstChain3.x = dstHook.x + 8;
		dstChain1.y = dstHook.y - ((dstHook.y - originHook) / 4);
		dstChain2.y = dstHook.y - ((dstHook.y - originHook) / 2);
		dstChain3.y = dstHook.y - (3 * ((dstHook.y - originHook) / 4));
	}
	if (dat->getHero()->getActualPos() % 4 == 1)//gauche
	{
		int originHook = dstHero.x +4;
		dstHook.y = dstHero.y + 40;
		dstHook.x = dstHero.x - (int)((dat->getHero()->getPosX() - dat->hookshot.posX) * 16) - 48;
		dstChain1.y = dstChain2.y = dstChain3.y = dstHook.y + 8;
		dstChain1.x = originHook - ((originHook - dstHook.x) / 4);
		dstChain2.x = originHook - ((originHook - dstHook.x) / 2);
		dstChain3.x = originHook - (3 * ((originHook - dstHook.x) / 4));
	}
	if (dat->getHero()->getActualPos() % 4 == 2)//haut
	{
		int originHook = dstHero.y ;
		dstHook.x = dstHero.x + 12;
		dstHook.y = dstHero.y - (int)(((dat->getHero()->getPosY()) - dat->hookshot.posY) * 16);
		dstChain1.x = dstChain2.x = dstChain3.x = dstHook.x + 8;
		dstChain1.y = dstHook.y + ((originHook - dstHook.y) / 4) + 16;
		dstChain2.y = dstHook.y + ((originHook - dstHook.y) / 2) + 16;
		dstChain3.y = dstHook.y + (3 * ((originHook - dstHook.y) / 4)) + 16;
	}
	if (dat->getHero()->getActualPos() % 4 == 3)//droite
	{
		int originHook = dstHero.x + 20;
		dstHook.y = dstHero.y + 40;
		dstHook.x = dstHero.x + (int)((dat->hookshot.posX - dat->getHero()->getPosX()) * 16) +32;
		dstChain1.y = dstChain2.y = dstChain3.y = dstHook.y + 8;
		dstChain1.x = dstHook.x - ((dstHook.x - originHook) / 4);
		dstChain2.x = dstHook.x - ((dstHook.x - originHook) / 2);
		dstChain3.x = dstHook.x - (3 * ((dstHook.x - originHook) / 4));
	}
	//gestion position fireSeed
	srcFireSeed.x = dat->fireSeed.actualImage * 16;
	srcFireSeed.y = 0;
	srcFireSeed.w = 16;
	srcFireSeed.h = 32;
	dstFireSeed.w = 32;
	dstFireSeed.h = 64;
	if ((dat->fireSeed.posX >= dat->getHero()->getPosX() - 20) && dat->fireSeed.posX <= dat->getHero()->getPosX() + 20)
		dstFireSeed.x = dstHero.x - (int)((dat->getHero()->getPosX() - dat->fireSeed.posX) * 16) + 12;
	if ((dat->fireSeed.posY >= dat->getHero()->getPosY() - 15) && dat->fireSeed.posY <= dat->getHero()->getPosY() + 15)
		dstFireSeed.y = dstHero.y - (int)((dat->getHero()->getPosY() - dat->fireSeed.posY) * 16) + 16;
	if (dat->fireSeed.fireSeedExists == true && dat->getHero()->getActualPos() % 4 == 1)
	{
		dstHero.x += 16;
	}

	SDL_RenderCopy(dat->getRenderer(), dat->getTextureFloor(), &srcRect, &dstRect);
	if (dat->fireSeed.fireSeedExists == true)
	{
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureFireSeed(), &srcFireSeed, &dstFireSeed);
	}
	SDL_RenderCopy(dat->getRenderer(), dat->getTextureLink(), &srcHero, &dstHero);
	if (dat->arrow.getActualImage() >= 0)
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureArrow(), &srcArrow, &dstArrow);
	if (dat->seed.seedExists)
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureSeed(), &srcSeed, &dstSeed);
	if (dat->bomb.bombExists)
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureBomb(), &srcBomb, &dstBomb);
	if (dat->explosion.bombExists)
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureExplosion(), &srcExplo, &dstExplo);
	if (dat->hookshot.hookshotExists)
	{
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureHookshot(), &srcHook, &dstHook);
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureHookshot(), &srcChain, &dstChain1);
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureHookshot(), &srcChain, &dstChain2);
		SDL_RenderCopy(dat->getRenderer(), dat->getTextureHookshot(), &srcChain, &dstChain3);
	}
	
	SDL_RenderCopy(dat->getRenderer(), dat->getTextureCeiling(), &srcRect, &dstRect);
	dat->setDrawAll(false);
	time = SDL_GetTicks() - time;
	return (0);
}

