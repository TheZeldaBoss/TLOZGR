#ifndef HERO_H_
#define HERO_H_

#include "Map.h"

class Hero
{
private:
	int posX;
	int posY;
	map actualMap;
	int posXScreen;
	int posYScreen;
public:
	Hero(int posX, int posY, map actualMap);
	int getPosX();
	void setPosX(int);
	int getPosY();
	void setPosY(int);
	map getActualMap();
	void setActualMap(map);
	int getPosXScreen();
	void setPosXScreen(int);
	int getPosYScreen();
	void setPosYScreen(int);
};

#endif /*HERO_H_*/