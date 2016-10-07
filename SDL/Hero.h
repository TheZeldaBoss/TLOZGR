#ifndef HERO_H_
#define HERO_H_

#include "Map.h"
#include "Objets.h"
class Hero
{
private:
	float posX;
	float posY;
	map actualMap;
	float posXScreen;
	float posYScreen;
	int actualImage;
	int actualPos;
	int count;
	objets equipement;
	int obj1;
	int obj2;
public:
	Hero(float posX, float posY, map actualMap);
	float getPosX();
	void setPosX(float);
	float getPosY();
	void setPosY(float);
	map getActualMap();
	void setActualMap(map);
	float getPosXScreen();
	void setPosXScreen(float);
	float getPosYScreen();
	void setPosYScreen(float);
	int getActualImage();
	void setActualImage(int);
	int getActualPos();
	void setActualPos(int);
	int getCount();
	void setCount(int);
	int getObj1();
	void setObj1(int);
	int getObj2();
	void setObj2(int);
};

#endif /*HERO_H_*/