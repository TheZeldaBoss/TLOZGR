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

int DrawMap(map actualMap, SDL_Window *window, Hero hero, bool drawAll)
{
	unsigned int a, b;
	a = SDL_GetTicks();
	SDL_Renderer *pRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	b = SDL_GetTicks();
	if (!pRenderer)
	{
		std::cerr << "renderer creation failed" << std::endl;
		exit(-1);
	}
	SDL_Surface *fond = IMG_Load(actualMap.getTilesetName().c_str());
	if (!fond)
	{
		std::cerr << "sprite creation failed" << std::endl;
		exit(-1);
	}
	SDL_Surface *link = IMG_Load("./data/images/Link/Link_walk.png");
	SDL_Texture *pTexture =  SDL_CreateTextureFromSurface(pRenderer, fond);
	SDL_Texture *pLinkTexture = SDL_CreateTextureFromSurface(pRenderer, link);
	//SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 640,480);

	if (!pTexture)
	{
		std::cerr << "Texture creation failed" << std::endl;
		exit(-1);
	}
	int tilesetWidth = tilesetWidths[actualMap.getTilesetValue()];
	int tilesetHeight = tilesetHeights[actualMap.getTilesetValue()];
	//SDL_LockTexture(pTexture, NULL, &pBuffer, &Pitch);
	int xOrig;
	int yOrig;
	if (hero.getPosX() <= 20)
		xOrig = 0;
	else if (hero.getPosX() > (actualMap.getWidth() - 20))
		xOrig = actualMap.getWidth() - 40 - 1;
	else
		xOrig = hero.getPosX() - 20 - 1;
	if (hero.getPosY() <= 15)
		yOrig = 0;
	else if (hero.getPosY() > (actualMap.getHeight() - 15))
		yOrig = actualMap.getHeight() - 30;
	else
		yOrig = hero.getPosY() - 15 - 1;
	//affichage sol + murs
	for (int i = xOrig, x = 0; (i + x) < xOrig + 40; x++)
	{
		for (int j = yOrig, y = 0; (j + y) < yOrig + 30; y++)
		{
			int posYTile = y * 8;
			int posXTile = x * 8;
			int valAffTileX;
			int valAffTileY;
			SDL_Rect imgPart;
			SDL_Rect pos;
			if (drawAll == true)
			{
				valAffTileX = (actualMap.getLayerFloor()[j + y][i + x] - 1) % tilesetWidth;
				valAffTileY = (actualMap.getLayerFloor()[j + y][i + x] - 1) / tilesetWidth;
				imgPart = { valAffTileX * 8, valAffTileY * 8, 8, 8 };
				pos = { posXTile, posYTile, 8, 8 };
				SDL_RenderCopy(pRenderer, pTexture, &imgPart, &pos);
				valAffTileX = (actualMap.getLayerWalls()[j + y][i + x] - 1) % tilesetWidth;
				valAffTileY = (actualMap.getLayerWalls()[j + y][i + x] - 1) / tilesetWidth;
				imgPart = { valAffTileX * 8, valAffTileY * 8, 8, 8 };
				SDL_RenderCopy(pRenderer, pTexture, &imgPart, &pos);
			}
		}
	}
	//affichage heros
	SDL_Rect heroPart;
	SDL_Rect heroPos;
	heroPart = {0, 0, 24, 32};
	heroPos = { (hero.getPosXScreen() * 8) - 8, (hero.getPosYScreen() * 8) - 24, 24, 32 };
	SDL_RenderCopy(pRenderer, pLinkTexture, &heroPart, &heroPos);
	SDL_RenderPresent(pRenderer);
	//affichage ceiling - au dessus du heros
	for (int i = xOrig, x = 0; i < xOrig + 40; i++, x++)
	{
		for (int j = yOrig, y = 0; j < yOrig + 30; j++, y++)
		{
			int posYTile = y * 8;
			int posXTile = x * 8;
			int valAffTileX;
			int valAffTileY;
			SDL_Rect imgPart;
			SDL_Rect pos;
			valAffTileX = (actualMap.getLayerCeiling()[j][i] - 1) % tilesetWidth;
			valAffTileY = (actualMap.getLayerCeiling()[j][i] - 1) / tilesetWidth;
			imgPart = { valAffTileX * 8, valAffTileY * 8, 8, 8 };
			pos = { posXTile, posYTile, 8, 8 };
			SDL_RenderCopy(pRenderer, pTexture, &imgPart, &pos);
		}
	}
	//SDL_UnlockTexture(pTexture);
	SDL_RenderPresent(pRenderer);
	b = SDL_GetTicks();
	SDL_DestroyTexture(pTexture);
	SDL_FreeSurface(fond);
	SDL_DestroyRenderer(pRenderer);
	return (0);
}