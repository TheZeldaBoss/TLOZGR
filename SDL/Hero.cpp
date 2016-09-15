#include "Hero.h"
#include <iostream>
Hero::Hero(int posX, int posY, map actualMap)
{
	this->posX = posX;
	this->posY = posY;
	this->actualMap = actualMap;
	if (actualMap.getLayerWalls()[posX][posY] != 0)
	{
		std::cerr << "bad position : character is in a wall" << std::endl;
		exit(1);
	}
	if (this->posX < 20)
		this->posXScreen = this->posX;
	else if ((this->actualMap.getWidth() - this->posX) < 20)
		this->posXScreen = 40 - (actualMap.getWidth() - this->posX);
	else
		this->posXScreen = 20;
	if (this->posY < 20)
		this->posYScreen = this->posY;
	else if ((this->actualMap.getHeight() - this->posY) < 20)
		this->posYScreen = 40 - (actualMap.getHeight() - this->posY);
	else
		this->posYScreen = 20;
}

int Hero::getPosX()
{
	return (this->posX);
}

void Hero::setPosX(int posX)
{
	this->posX = posX;
}

int Hero::getPosY()
{
	return (this->posY);
}

void Hero::setPosY(int posY)
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

int Hero::getPosXScreen()
{
	return (this->posXScreen);
}

void Hero::setPosXScreen(int posXScreen)
{
	this->posXScreen = posXScreen;
}

int Hero::getPosYScreen()
{
	return (this->posYScreen);
}

void Hero::setPosYScreen(int posYScreen)
{
	this->posYScreen = posYScreen;
}