#include "Objets.h"
#include "DrawMap.h"
#include <Windows.h>

objets::objets(void *dat)
{
	DataToDraw *data = (DataToDraw *)dat;
	for (int i = arc; i <= ocarina; i++)
	{
		this->objetEquipablePossede[i] = false;
		this->munitionsPossedees[i] = 0;
	}
	for (int i = palmes; i <= triforceCourage; i++)
	{
		this->objetNonEquipablePossede[i] = false;
	}
	this->imagesObjetsEquipables = SDL_CreateTextureFromSurface(data->getRenderer(), IMG_Load("objetsEquipables.png"));
	this->imagesObjetsNonEquipables = SDL_CreateTextureFromSurface(data->getRenderer(), IMG_Load("objetsMenu.png"));
}

objets::objets()
{
	for (int i = arc; i <= ocarina; i++)
	{
		this->objetEquipablePossede.push_back(false);
		this->munitionsPossedees.push_back(0);
	}
	for (int i = palmes; i <= triforceCourage; i++)
	{
		this->objetNonEquipablePossede.push_back(false);
	}
	this->imagesObjetsEquipables = NULL;
	this->imagesObjetsNonEquipables = NULL;
}

bool objets::getObjetEquipablePossede(int objet)
{
	if (this->objetEquipablePossede[objet] != false)
		return true;
	else
		return false;
}

void objets::setObjetEquipablePossedes(int objet, bool possede)
{
	this->objetEquipablePossede[objet] = possede;
}

bool objets::getObjetNonEquipablePossede(int objet)
{
	return this->objetNonEquipablePossede[objet];
}

void objets::setObjetNonEquipablePossede(int objet, bool possede)
{
	this->objetNonEquipablePossede[objet] = possede;
}

int objets::getMunitionsPossedees(int objet)
{
	return this->munitionsPossedees[objet];
}

void objets::setMunitionsPossedees(int objet, int munitions)
{
	this->munitionsPossedees[objet] = munitions;
}

SDL_Texture *objets::getImagesObjetsEquipables()
{
	return this->imagesObjetsEquipables;
}

void objets::setImageObjetsEquipables(SDL_Texture *image)
{
	this->imagesObjetsEquipables = image;
}

SDL_Texture *objets::getImageObjetsNonEquipables()
{
	return this->imagesObjetsNonEquipables;
}

void objets::setImageObjetsNonEquipables(SDL_Texture *image)
{
	this->imagesObjetsNonEquipables = image;
}

static bool dejala = false;

int use_bow(void *Data)
{
	DataToDraw *dat = (DataToDraw *)Data;
	if (dejala) return 0;
	
	dejala = true;
	
	int curPos = 4+dat->getHero()->getActualPos();
	dat->useObject = true;
	unsigned int anim = 0;
	while (anim < 8)
	{
		dat->getHero()->setActualPos(curPos);
		dat->getHero()->setActualImage(anim);
		dat->needDraw = true;
		Sleep(40);
		anim++;
	}
	dat->useObject = false;
	dat->getHero()->setActualImage(0);
	dat->getHero()->setActualPos(curPos-4);
	dejala = false;
	dat->arrow.setActualImage(0);
	if (dat->arrow.arrowExists == false)
	{
		dat->arrow.setPosX((float)(dat->getHero()->getPosX() + 1));
		dat->arrow.setPosY((float)(dat->getHero()->getPosY() + 2));
		dat->arrow.setActualPos(dat->getHero()->getActualPos());
	}
	if (dat->arrow.arrowExists == false)
	{
		dat->arrow.arrowExists = true;
		if (dat->getHero()->getActualPos() % 4 == 0)//bas
		{
			while (dat->arrow.getPosY() < dat->getMap()->getHeight())
			{
				dat->needDraw = true;
				dat->arrow.setPosY((float)(dat->arrow.getPosY() + .125));
				Sleep(5);
			}
			dat->arrow.arrowExists = false;
		}
		else if (dat->getHero()->getActualPos() % 4 == 1)//gauche
		{
			while (dat->arrow.getPosX() > 0)
			{
				dat->needDraw = true;
				dat->arrow.setPosX((float)(dat->arrow.getPosX() - .125));
				Sleep(5);
			}
			dat->arrow.arrowExists = false;
		}
		else if (dat->getHero()->getActualPos() % 4 == 2)//haut
		{
			while (dat->arrow.getPosY() > 0)
			{
				dat->needDraw = true;
				dat->arrow.setPosY((float)(dat->arrow.getPosY() - .125));
				Sleep(5);
			}
			dat->arrow.arrowExists = false;
		}
		else//droite
		{
			while (dat->arrow.getPosX() < dat->getMap()->getWidth())
			{
				dat->needDraw = true;
				dat->arrow.setPosX((float)(dat->arrow.getPosX() + .125));
				Sleep(5);
			}
			dat->arrow.arrowExists = false;
		}
		
	}
	return (0);
}

int use_bombs(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	dat->explosion.actualImage = -1;
	dat->bomb.posX = dat->getHero()->getPosX();
	dat->bomb.posY = dat->getHero()->getPosY() + 1;
	if (dat->bomb.bombExists == false)
	{
		dat->bomb.bombExists = true;
		for (int i = 0; i < 53; i++)
		{
			dat->needDraw = true;
			dat->bomb.actualImage = (i + 1) % 2;
			Sleep(50);
		}
		for (int i = 0; i < 32; i++)
		{
			dat->needDraw = true;
			dat->bomb.actualImage = (((i / 4) % 2) * 2) + (i % 2);
			Sleep(50);
		}
		for (int i = 0; i < 16; i++)
		{
			dat->needDraw = true;
			dat->bomb.actualImage = i % 4;
			Sleep(50);
		}
		dat->bomb.actualImage = -1;
		dat->bomb.bombExists = false;
	}
	if (dat->explosion.bombExists == false)
	{
		dat->explosion.bombExists = true;
		for (int i = 0; i < 11; i++)
		{
			dat->needDraw = true;
			dat->explosion.actualImage = i;
			Sleep(50);
		}
		dat->explosion.bombExists = false;
	}
	dat->explosion.actualImage = -1;
	dat->needDraw = true;
	return (0);
}

int use_slingshot(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	if (dejala) return 0;

	dejala = true;

	int curPos = 8 + dat->getHero()->getActualPos();
	dat->useObject = true;
	unsigned int anim = 0;
	while (anim < 4)
	{
		dat->getHero()->setActualPos(curPos);
		dat->getHero()->setActualImage(anim);
		dat->needDraw = true;
		Sleep(80);
		anim++;
	}
	dat->useObject = false;
	dat->getHero()->setActualImage(0);
	dat->getHero()->setActualPos(curPos - 8);
	dat->needDraw = true;
	if (dat->seed1.seedExists == false)
	{
		dat->seed1.seedExists = true;
		dat->seed1.posX = (float)(dat->getHero()->getPosX() + .5);
		dat->seed1.posY = dat->getHero()->getPosY() + 2;
		if (dat->getHero()->getActualPos() % 4 == 0)//bas
		{
			while (dat->seed1.posY < (float)(dat->getMap()->getHeight() - 1) && dat->getMap()->getLayerWalls()[(int)dat->seed1.posY][(int)dat->seed1.posX] == 0)
			{
				dat->needDraw = true;
				dat->seed1.posY += .125;
				Sleep(2);
			}
			dat->seed1.seedExists = false;
		}
		if (dat->getHero()->getActualPos() % 4 == 1)//gauche
		{
			while (dat->seed1.posX > 0 && dat->getMap()->getLayerWalls()[(int)(dat->seed1.posY)][(int)(dat->seed1.posX)] == 0)
			{
				dat->needDraw = true;
				dat->seed1.posX -= .125;
				Sleep(2);
			}
			dat->seed1.seedExists = false;
		}
		if (dat->getHero()->getActualPos() % 4 == 2)//haut
		{
			while (dat->seed1.posY > 0 && dat->getMap()->getLayerWalls()[(int)(dat->seed1.posY)][(int)(dat->seed1.posX)] == 0)
			{
				dat->needDraw = true;
				dat->seed1.posY -= .125;
				Sleep(2);
			}
			dat->seed1.seedExists = false;
		}
		if (dat->getHero()->getActualPos() % 4 == 3)//droite
		{
			while (dat->seed1.posX < dat->getMap()->getWidth() && dat->getMap()->getLayerWalls()[(int)(dat->seed1.posY)][(int)(dat->seed1.posX)] == 0)
			{
				dat->needDraw = true;
				dat->seed1.posX += .125;
				Sleep(2);
			}
			dat->seed1.seedExists = false;
		}
	}
	dejala = false;
	return (0);
}

int use_hookshot(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	int i = 0;
	if (dejala)
		return (0);

	int curPos = 12 + dat->getHero()->getActualPos();
	dejala = true;
	dat->useObject = true;
	unsigned int anim = 0;
	while (anim < 4)
	{
		dat->getHero()->setActualPos(curPos);
		dat->getHero()->setActualImage(anim);
		dat->needDraw = true;
		Sleep(80);
		anim++;
	}
	dat->hookshot.posX = (float)(dat->getHero()->getPosX() + .5);
	dat->hookshot.posY = (float)(dat->getHero()->getPosY() + .5);
	dat->hookshot.hookshotExists = true;
	if (dat->getHero()->getActualPos() % 4 == 0)//bas
	{
		while (dat->hookshot.posY < (float)(dat->getMap()->getHeight() - 1) && dat->getMap()->getLayerWalls()[(int)dat->hookshot.posY][(int)dat->hookshot.posX] == 0 && dat->hookshot.posY < dat->getHero()->getPosY() + 30)
		{

			dat->needDraw = true;
			dat->hookshot.posY += .125;
			if (i < 32)
				dat->hookshot.actualImage = 1;
			else
				dat->hookshot.actualImage = 2;
			i++;
			if (i == 64)
				i = 0;
			Sleep(2);
		}
		while (dat->hookshot.posY >(float)(dat->getHero()->getPosY()))
		{
			dat->needDraw = true;
			dat->hookshot.posY -= .125;
			if (i < 32)
				dat->hookshot.actualImage = 1;
			else
				dat->hookshot.actualImage = 2;
			i++;
			if (i == 64)
				i = 0;
			Sleep(2);
		}
	}
	if (dat->getHero()->getActualPos() % 4 == 1)//gauche
	{
		while (dat->hookshot.posX > 0 && dat->getMap()->getLayerWalls()[(int)(dat->hookshot.posY)][(int)(dat->hookshot.posX)] == 0 && dat->hookshot.posX > dat->getHero()->getPosX() - 30)
		{
			dat->needDraw = true;
			dat->hookshot.posX -= .125;
			if (i < 32)
				dat->hookshot.actualImage = 1;
			else
				dat->hookshot.actualImage = 2;
			i++;
			if (i == 64)
				i = 0;
			Sleep(2);
		}
		while (dat->hookshot.posX <(float)(dat->getHero()->getPosX()))
		{
			dat->needDraw = true;
			dat->hookshot.posX += .125;
			if (i < 32)
				dat->hookshot.actualImage = 1;
			else
				dat->hookshot.actualImage = 2;
			i++;
			if (i == 64)
				i = 0;
			Sleep(2);
		}
	}
	if (dat->getHero()->getActualPos() % 4 == 2)//haut
	{
		while (dat->hookshot.posY > 0 && dat->getMap()->getLayerWalls()[(int)(dat->hookshot.posY)][(int)(dat->hookshot.posX)] == 0 && dat->hookshot.posY > dat->getHero()->getPosY() - 30)
		{
			if (i < 32)
				dat->hookshot.actualImage = 1;
			else
				dat->hookshot.actualImage = 2;
			i++;
			if (i == 64)
				i = 0;
			dat->needDraw = true;
			dat->hookshot.posY -= .125;
			Sleep(2);
		}
		while (dat->hookshot.posY < dat->getHero()->getPosY())
		{
				 if (i < 32)
				dat->hookshot.actualImage = 1;
			else
				dat->hookshot.actualImage = 2;
			i++;
			if (i == 64)
				i = 0;
			dat->needDraw = true;
			dat->hookshot.posY += .125;
			Sleep(2);
		}
	}
	if (dat->getHero()->getActualPos() % 4 == 3)//droite
	{
		while (dat->hookshot.posX < dat->getMap()->getWidth() && dat->getMap()->getLayerWalls()[(int)(dat->hookshot.posY)][(int)(dat->hookshot.posX)] == 0 && dat->hookshot.posX < dat->getHero()->getPosX() + 30)
		{
			if (i < 32)
				dat->hookshot.actualImage = 1;
			else
				dat->hookshot.actualImage = 2;
			i++;
			if (i == 64)
				i = 0;
			dat->needDraw = true;
			dat->hookshot.posX += .125;
			Sleep(2);
		}
		while (dat->hookshot.posX > dat->getHero()->getPosX())
		{
			if (i < 32)
				dat->hookshot.actualImage = 1;
			else
				dat->hookshot.actualImage = 2;
			i++;
			if (i == 64)
				i = 0;
			dat->needDraw = true;
			dat->hookshot.posX -= .125;
			Sleep(2);
		}
	}
	dejala = false;
	dat->getHero()->setActualImage(0);
	dat->getHero()->setActualPos(dat->getHero()->getActualPos() - 12);
	
	dat->hookshot.hookshotExists = false;
	dat->useObject = false;
	dat->needDraw = true;
	return (0);
}

int use_lantern(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	if (dejala)
		return (0);
	dat->fireSeed.fireSeedExists = true;
	int curpos = dat->getHero()->getActualPos() + 16;
	dejala = true;
	dat->useObject = true;
	dat->getHero()->setActualPos(curpos);
	dat->getHero()->setActualImage(0);
	//animation lancer graime : 8 frames
	if (dat->getHero()->getActualPos() % 4 == 0)//bas
	{
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() - .125);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + 1);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + 1.25);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + 1.5);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + 1.75);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + 2);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + 2.25);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + 2.5);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + 2.75);
		Sleep(20);
		dat->needDraw = true;
	}
	else if (dat->getHero()->getActualPos() % 4 == 1)//gauche
	{
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() - .625);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .375);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() - .750);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .375);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() - .875);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .5);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() - 1);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .5);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() - 1.125);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .625);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() - 1.25);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .625);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() - 1.375);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .75);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() - 1.5);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .75);
		Sleep(20);
		dat->needDraw = true;
	}
	else if (dat->getHero()->getActualPos() % 4 == 2)//haut
	{
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() - .125);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() - .25);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() - .5);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() - .75);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() - 1);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() - 1.25);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() - 1.5);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() - 1.75);
		Sleep(20);
		dat->needDraw = true;
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() - 2);
		Sleep(20);
	}
	else//droite
	{
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() + 2.125);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .375);
		dat->needDraw = true;
		Sleep(20);
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() + 2.25);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .375);
		dat->needDraw = true;
		Sleep(20);
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() + 2.375);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .5);
		dat->needDraw = true;
		Sleep(20);
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() + 2.5);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .5);
		dat->needDraw = true;
		Sleep(20);
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() + 2.625);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .625);
		dat->needDraw = true;
		Sleep(20);
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() + 2.750);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .625);
		dat->needDraw = true;
		Sleep(20);
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() + 2.875);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .750);
		dat->needDraw = true;
		Sleep(20);
		dat->fireSeed.posX = (float)(dat->getHero()->getPosX() + 3);
		dat->fireSeed.posY = (float)(dat->getHero()->getPosY() + .750);
		dat->needDraw = true;
		Sleep(20);
	}
	dat->useObject = false; 
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			dat->fireSeed.actualImage = j + 1;
			dat->needDraw = true;
			Sleep(20);
		}
	}
	dat->fireSeed.actualImage = 0;
	dat->fireSeed.fireSeedExists = false;
	dat->getHero()->setActualPos(curpos - 16);
	dat->needDraw = true;
	dejala = false;
	return (0);
}

int use_boomerang(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	return (0);
}

int use_hammer(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	if (dejala) return 0;

	dejala = true;

	int curpos = 20 + dat->getHero()->getActualPos();
	dat->useObject = true;
	unsigned int anim = 0;
	while (anim < 4)
	{
		dat->getHero()->setActualPos(curpos);
		dat->getHero()->setActualImage(anim);
		dat->needDraw = true;
		anim++;
		Sleep(80);
	}
	while (anim > 0)
	{
		anim--;
		dat->getHero()->setActualPos(curpos);
		dat->getHero()->setActualImage(anim);
		dat->needDraw = true;
		Sleep(80);
	}
	dat->getHero()->setActualImage(4);
	dat->needDraw = true;
	Sleep(160);
	dat->useObject = false;
	dat->getHero()->setActualImage(0);
	dat->getHero()->setActualPos(curpos - 20);
	dat->needDraw = true;
	dejala = false;
	return (0);
}

int use_lightBow(void *data)
{
	//DataToDraw *dat = (DataToDraw *)data;
	use_bow(data);
	return (0);
}

int use_boots(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	return (0);
}

int use_superSlingshot(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	if (dejala) return 0;

	dejala = true;

	int curPos = 8 + dat->getHero()->getActualPos();
	dat->useObject = true;
	unsigned int anim = 0;
	while (anim < 4)
	{
		dat->getHero()->setActualPos(curPos);
		dat->getHero()->setActualImage(anim);
		dat->needDraw = true;
		Sleep(80);
		anim++;
	}
	dat->useObject = false;
	dat->getHero()->setActualImage(0);
	dat->getHero()->setActualPos(curPos - 8);
	dat->needDraw = true;
	if (dat->seed1.seedExists == false && dat->seed2.seedExists == false && dat->seed3.seedExists == false)
	{
		dat->seed1.seedExists = true;
		dat->seed2.seedExists = true;
		dat->seed3.seedExists = true;
		dat->seed1.posX = (float)(dat->getHero()->getPosX() + .5);
		dat->seed1.posY = dat->getHero()->getPosY() + 2;
		dat->seed2.posX = (float)(dat->getHero()->getPosX() + .5);
		dat->seed2.posY = dat->getHero()->getPosY() + 2;
		dat->seed3.posX = (float)(dat->getHero()->getPosX() + .5);
		dat->seed3.posY = dat->getHero()->getPosY() + 2;
		if (dat->getHero()->getActualPos() % 4 == 0)//bas
		{
			while (dat->seed1.seedExists || dat->seed2.seedExists || dat->seed3.seedExists)
			{
				//seed1 : vertical
				if (dat->seed1.posY <= (float)(dat->getMap()->getHeight() - 1) && dat->getMap()->getLayerWalls()[(int)dat->seed1.posY][(int)dat->seed1.posX] == 0)
				{
					dat->needDraw = true;
					dat->seed1.posY += .125;
					Sleep(2);
				}
				else
					dat->seed1.seedExists = false;
				//seed2 : diag bas gauche
				if (dat->seed2.posY <= (float)(dat->getMap()->getHeight() - 1)&& dat->seed2.posX > 0.0 && dat->getMap()->getLayerWalls()[(int)dat->seed2.posY][(int)dat->seed2.posX] == 0)
				{
					dat->needDraw = true;
					dat->seed2.posY += .125;
					dat->seed2.posX -= (float)0.081;
					Sleep(2);
				}
				else
					dat->seed2.seedExists = false;
				//seed3 : bas droite
				if (dat->seed3.posY <= (float)(dat->getMap()->getHeight() - 1) && dat->seed3.posX <= dat->getMap()->getWidth() - 1 && dat->getMap()->getLayerWalls()[(int)dat->seed3.posY][(int)dat->seed3.posX] == 0)
				{
					dat->needDraw = true;
					dat->seed3.posY += .125;
					dat->seed3.posX += (float).081;
					Sleep(2);
				}
				else
					dat->seed3.seedExists = false;
			}
		}
		if (dat->getHero()->getActualPos() % 4 == 1)//gauche
		{
			while (dat->seed1.seedExists || dat->seed2.seedExists || dat->seed3.seedExists)
			{
				//seed1 : horizontale
				if (dat->seed1.posX > 0 && dat->getMap()->getLayerWalls()[(int)(dat->seed1.posY)][(int)(dat->seed1.posX)] == 0)
				{
					dat->needDraw = true;
					dat->seed1.posX -= .125;
					Sleep(2);
				}
				else
					dat->seed1.seedExists = false;
				//seed2 : haut gauche
				if (dat->seed2.posX > 0.0 && dat->seed2.posY > 0.0 && dat->getMap()->getLayerWalls()[(int)(dat->seed2.posY)][(int)(dat->seed2.posX)] == 0)
				{
					dat->needDraw = true;
					dat->seed2.posX -= .125;
					dat->seed2.posY -= (float).081;
					Sleep(2);
				}
				else
					dat->seed2.seedExists = false;
				//seed3 : haut droite
				if (dat->seed3.posX > 0.0 && dat->seed3.posY <= dat->getMap()->getHeight() && dat->getMap()->getLayerWalls()[(int)(dat->seed3.posY)][(int)(dat->seed3.posX)] == 0)
				{
					dat->needDraw = true;
					dat->seed3.posX -= .125;
					dat->seed3.posY += (float).081;
					Sleep(2);
				}
				else
					dat->seed3.seedExists = false;
			}
		}
		if (dat->getHero()->getActualPos() % 4 == 2)//haut
		{
			while (dat->seed1.seedExists || dat->seed2.seedExists || dat->seed3.seedExists)
			{
				if (dat->seed1.posY > 0.0 && dat->getMap()->getLayerWalls()[(int)(dat->seed1.posY)][(int)(dat->seed1.posX)] == 0)
				{
					dat->needDraw = true;
					dat->seed1.posY -= .125;
					Sleep(2);
				}
				else
					dat->seed1.seedExists = false;
				//haut gauche
				if (dat->seed2.posY > 0.0 && dat->seed2.posX > 0.0 && dat->getMap()->getLayerWalls()[(int)(dat->seed2.posY)][(int)(dat->seed2.posX)] == 0)
				{
					dat->needDraw = true;
					dat->seed2.posX -= (float).081;
					dat->seed2.posY -= .125;
					Sleep(2);
				}
				else
					dat->seed2.seedExists = false;
				if (dat->seed3.posY > 0.0 && dat->seed3.posX <= dat->getMap()->getWidth() && dat->getMap()->getLayerWalls()[(int)(dat->seed3.posY)][(int)(dat->seed3.posX)] == 0)
				{
					dat->needDraw = true;
					dat->seed3.posX += (float).081;
					dat->seed3.posY -= .125;
					Sleep(2);
				}
				else
					dat->seed3.seedExists = false;
			}
		}
		if (dat->getHero()->getActualPos() % 4 == 3)//droite
		{
			while (dat->seed1.seedExists || dat->seed2.seedExists || dat->seed3.seedExists)
			{
				if (dat->seed1.posX <= dat->getMap()->getWidth() && dat->getMap()->getLayerWalls()[(int)(dat->seed1.posY)][(int)(dat->seed1.posX)] == 0)
				{
					dat->needDraw = true;
					dat->seed1.posX += .125;
					Sleep(2);
				}
				else
					dat->seed1.seedExists = false;
				//haut
				if (dat->seed2.posX <= dat->getMap()->getWidth() && dat->seed2.posY > 0.0 && dat->getMap()->getLayerWalls()[(int)(dat->seed2.posY)][(int)(dat->seed2.posX)] == 0)
				{
					dat->needDraw = true;
					dat->seed2.posY -= (float).081;
					dat->seed2.posX += .125;
					Sleep(2);
				}
				else
					dat->seed2.seedExists = false;
				if (dat->seed3.posX <= dat->getMap()->getWidth() && dat->seed3.posY <= dat->getMap()->getHeight() && dat->getMap()->getLayerWalls()[(int)(dat->seed3.posY)][(int)(dat->seed3.posX)] == 0)
				{
					dat->needDraw = true;
					dat->seed3.posX += .125;
					dat->seed3.posY += (float).081;
					Sleep(2);
				}
				else
					dat->seed3.seedExists = false;
			}
		}
	}
	dejala = false;
	return (0);
}

int use_bottle1(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	return (0);
}

int use_bottle2(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	return (0);
}

int use_ocarina(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	return (0);
}

void use_objet(int objet, void *data)
{
	SDL_Thread *thread;
	switch (objet)
	{
	case 1:
		thread = SDL_CreateThread(use_bow, "bow", data);
		break;
	case 2:
		thread = SDL_CreateThread(use_bombs, "bombs", data);
		break;
	case 3:
		thread = SDL_CreateThread(use_slingshot, "slingshot", data);
		break;
	case 4:
		thread = SDL_CreateThread(use_hookshot, "hookshot", data);
		break;
	case 5:
		thread = SDL_CreateThread(use_lantern, "lantern", data);
		break;
	case 6:
		thread = SDL_CreateThread(use_boomerang, "boomerang", data);
		break;
	case 7:
		thread = SDL_CreateThread(use_hammer, "hammer", data);
		break;
	case 8:
		thread = SDL_CreateThread(use_lightBow, "lightBow", data);
		break;
	case 9:
		thread = SDL_CreateThread(use_boots, "boots", data);
		break;
	case 10:
		thread = SDL_CreateThread(use_superSlingshot, "slingshot", data);
		break;
	case 11:
		thread = SDL_CreateThread(use_bottle1, "bottle", data);
		break;
	case 12:
		thread = SDL_CreateThread(use_bottle2, "bottle", data);
		break;
	case 13:
		thread = SDL_CreateThread(use_ocarina, "ocarina", data);
		break;
	}
}