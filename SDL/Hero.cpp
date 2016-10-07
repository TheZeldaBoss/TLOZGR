#include "Hero.h"
#include <iostream>
Hero::Hero(float posX, float posY, map actualMap)
{
	this->posX = posX;
	this->posY = posY;
	this->actualMap = actualMap;
	/*if (actualMap.getLayerWalls()[(int)(posX)][(int)(posY)] != 0)
	{
		std::cerr << "bad position : character is in a wall" << std::endl;
		exit(1);
	}*/
	if (this->posX < 20.0)
		this->posXScreen = this->posX;
	else if ((this->actualMap.getWidth() - this->posX) < 20.0)
		this->posXScreen = (float)(40.0 - (actualMap.getWidth() - this->posX));
	else
		this->posXScreen = 20.0;
	if (this->posY < 20.0)
		this->posYScreen = this->posY;
	else if ((this->actualMap.getHeight() - this->posY) < 20.0)
		this->posYScreen = (float)(40.0 - (actualMap.getHeight() - this->posY));
	else
		this->posYScreen = 20.0;
	this->actualImage = 0;
	this->actualPos = 0;
	this->count = 0;
}

float Hero::getPosX()
{
	return (this->posX);
}

void Hero::setPosX(float posX)
{
	this->posX = posX;
}

float Hero::getPosY()
{
	return (this->posY);
}

void Hero::setPosY(float posY)
{
	this->posY = posY;
}

map Hero::getActualMap()
{
	return (this->actualMap);
}

void Hero::setActualMap(map actualMap)
{
	this->actualMap = actualMap;
}

float Hero::getPosXScreen()
{
	return (this->posXScreen);
}

void Hero::setPosXScreen(float posXScreen)
{
	this->posXScreen = posXScreen;
}

float Hero::getPosYScreen()
{
	return (this->posYScreen);
}

void Hero::setPosYScreen(float posYScreen)
{
	this->posYScreen = posYScreen;
}

int Hero::getActualImage()
{
	return (this->actualImage);
}

void Hero::setActualImage(int actu)
{
	this->actualImage = actu;
}

int Hero::getActualPos()
{
	return (this->actualPos);
}

void Hero::setActualPos(int pos)
{
	this->actualPos = pos;
}

int Hero::getCount()
{
	return this->count;
}

void Hero::setCount(int count)
{
	this->count = count;
}

int Hero::getObj1()
{
	return (this->obj1);
}

int Hero::getObj2()
{
	return (this->obj2);
}

void Hero::setObj1(int obj)
{
	this->obj1 = obj;
}

void Hero::setObj2(int obj)
{
	this->obj2 = obj;
}