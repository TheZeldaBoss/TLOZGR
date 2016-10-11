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
				dat->arrow.setPosY(dat->arrow.getPosY() + .125);
				Sleep(5);
			}
			dat->arrow.arrowExists = false;
		}
		else if (dat->getHero()->getActualPos() % 4 == 1)//gauche
		{
			while (dat->arrow.getPosX() > 0)
			{
				dat->needDraw = true;
				dat->arrow.setPosX(dat->arrow.getPosX() - .125);
				Sleep(5);
			}
			dat->arrow.arrowExists = false;
		}
		else if (dat->getHero()->getActualPos() % 4 == 2)//haut
		{
			while (dat->arrow.getPosY() > 0)
			{
				dat->needDraw = true;
				dat->arrow.setPosY(dat->arrow.getPosY() - .125);
				Sleep(5);
			}
			dat->arrow.arrowExists = false;
		}
		else//droite
		{
			while (dat->arrow.getPosX() < dat->getMap()->getWidth())
			{
				dat->needDraw = true;
				dat->arrow.setPosX(dat->arrow.getPosX() + .125);
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
	return (0);
}

int use_slingshot(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	return (0);
}

int use_hookshot(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	return (0);
}

int use_lantern(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
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
	return (0);
}

int use_lightBow(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
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
		thread = SDL_CreateThread(use_bottle1, "bottle", data);
		break;
	case 11:
		thread = SDL_CreateThread(use_bottle2, "bottle", data);
		break;
	case 12:
		thread = SDL_CreateThread(use_ocarina, "ocarina", data);
		break;
	}
}