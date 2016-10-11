#ifndef DRAWMAP
#define DRAWMAP
#include <vector>
#include "Map.h"
#include <SDL2/SDL.h>
#include "Hero.h"

class arrowToDraw
{
private:
	int actualImage;
	int actualPos;
	float posX;
	float posY;
public:
	arrowToDraw();
	bool arrowExists;
	float getPosX();
	void setPosX(float);
	float getPosY();
	void setPosY(float);
	int getActualImage();
	void setActualImage(int);
	int getActualPos();
	void setActualPos(int);
	bool drawIt;
};

class DataToDraw
{
private:
	map *actualMap;
	SDL_Window *window;
	Hero *hero;
	SDL_Renderer *pRenderer;
	SDL_Surface *pFond;
	SDL_Surface *pLink;
	SDL_Texture *pTextureFloor;
	SDL_Texture *pTextureCeiling;
	SDL_Texture *pTextureArrow;
	SDL_Texture *pTextureLink;
	SDL_Surface *pMapFloor;
	SDL_Surface *pMapCeiling;
	
	bool drawAll;//0 : draw all, 1 : draw only 
public:
	DataToDraw();
	DataToDraw(map *, SDL_Window *, Hero *, bool);
	map *getMap();
	void setMap(map *);
	SDL_Window *getWindow();
	void setWindow(SDL_Window *);
	Hero *getHero();
	void setHero(Hero *);
	bool getDrawAll();
	void setDrawAll(bool);
	SDL_Renderer *getRenderer();
	void setRenderer(SDL_Renderer *);
	SDL_Surface *getFond();
	void setFond(SDL_Surface *);
	SDL_Surface *getLink();
	void setLink(SDL_Surface *);
	SDL_Texture *getTextureFloor();
	void setTextureFloor(SDL_Texture *);
	SDL_Texture *getTextureCeiling();
	void setTextureCeiling(SDL_Texture *);
	SDL_Texture *getTextureArrow();
	void setTextureArrow(SDL_Texture *);
	SDL_Texture *getTextureLink();
	void setTextureLink(SDL_Texture *);
	SDL_Surface *getMapFloor();
	void setMapFloor(SDL_Surface *);
	SDL_Surface *getMapCeiling();
	void setMapCeiling(SDL_Surface *);
	arrowToDraw arrow;
	bool useObject;
	bool needDraw;
	//DataToDraw *operator=(DataToDraw *);
};

int DrawMap(void *data, int, int);
SDL_Window *initWindow();
int closeWindow(SDL_Window *);
void init(DataToDraw *);
void destroy(DataToDraw *);

#endif /*DRAWMAP*/