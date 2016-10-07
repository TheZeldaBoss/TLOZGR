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

int use_bow(void *data)
{
	DataToDraw *dat = (DataToDraw *)data;
	SDL_Texture *arrow = SDL_CreateTextureFromSurface(dat->getRenderer(), IMG_Load("data/images/equipement/arrows.png"));
	float arrowX = (float)(dat->getHero()->getPosX()), arrowXScreen;
	if (arrowX <= 20)
		arrowXScreen = arrowX * 16;
	else if (arrowX >= dat->getMap()->getWidth() - 20)
		arrowXScreen = (dat->getMap()->getWidth() - arrowX) * 16;
	else
		arrowXScreen = 320;
	float arrowY = (float)(dat->getHero()->getPosY()), arrowYScreen;
	if (arrowY <= 15)
		arrowYScreen = arrowY * 16;
	else if (arrowY >= dat->getMap()->getHeight() - 15)
		arrowYScreen = 480 - ((dat->getMap()->getHeight() - arrowY) * 16);
	else
		arrowYScreen = 240;
	int arrowDir = dat->getHero()->getActualPos();
	SDL_Rect src;
	SDL_Rect dst;
	src.x = 0;
	src.y = (arrowDir - 1) * 16;
	src.w = 16;
	src.h = 16;
	if (arrowDir == 1)//left
	{

		while (arrowX >= (float)(0) && dat->getMap()->getLayerWalls()[(int)(arrowY -.125)][(int)arrowX] == 0)
		{
			Uint32 time;

			time = SDL_GetTicks();
			dst.x = (int)(arrowXScreen - 32);
			dst.y = (int)((arrowYScreen - 32));
			dst.w = 32;
			dst.h = 32;
			DrawMap(data, dat->getHero()->getActualImage(), dat->getHero()->getActualPos());
			SDL_RenderCopy(dat->getRenderer(), arrow, &src, &dst);
			SDL_RenderPresent(dat->getRenderer());
			arrowX -= .125;
			arrowXScreen -= 1;
			time = SDL_GetTicks() - time;
			if (time < 3)
			{
				Sleep(2 - time);
			}
			
		}
	}
	else if (arrowDir == 2)//up
	{
		while (arrowY > (float)(0) && dat->getMap()->getLayerWalls()[(int)(arrowY)][(int)(arrowX - .125)] == 0)
		{
			Uint32 time;

			time = SDL_GetTicks();
			dst.x = (int)(arrowXScreen - 16);
			dst.y = (int)((arrowYScreen - 32));
			dst.w = 32;
			dst.h = 32;
			DrawMap(data, dat->getHero()->getActualImage(), dat->getHero()->getActualPos());
			SDL_RenderCopy(dat->getRenderer(), arrow, &src, &dst);
			SDL_RenderPresent(dat->getRenderer());
			arrowY -= .125;
			arrowYScreen -= 1;
			time = SDL_GetTicks() - time;
			if (time < 3)
			{
				Sleep(2 - time);
			}
		}
	}
	else if (arrowDir == 3)//right
	{
		while (arrowY <= dat->getMap()->getWidth() - 1 && dat->getMap()->getLayerWalls()[(int)(arrowY + .125)][(int)(arrowX)] == 0)
		{
			Uint32 time;

			time = SDL_GetTicks();
			dst.x = (int)(arrowXScreen - 32);
			dst.y = (int)((arrowYScreen - 32));
			dst.w = 32;
			dst.h = 32;
			DrawMap(data, dat->getHero()->getActualImage(), dat->getHero()->getActualPos());
			SDL_RenderCopy(dat->getRenderer(), arrow, &src, &dst);
			SDL_RenderPresent(dat->getRenderer());
			arrowX += .125;
			arrowXScreen += 1;
			time = SDL_GetTicks() - time;
			if (time < 3)
			{
				Sleep(2 - time);
			}
		}
	}
	else
	{
		while (arrowY <= dat->getMap()->getHeight() - 1 && dat->getMap()->getLayerWalls()[(int)(arrowY)][(int)(arrowX + .125)] == 0)
		{
			Uint32 time;

			time = SDL_GetTicks();
			src.x = 0;
			src.y = 48;
			dst.x = (int)(arrowXScreen - 16);
			dst.y = (int)((arrowYScreen - 32));
			dst.w = 32;
			dst.h = 32;
			DrawMap(data, dat->getHero()->getActualImage(), dat->getHero()->getActualPos());
			SDL_RenderCopy(dat->getRenderer(), arrow, &src, &dst);
			SDL_RenderPresent(dat->getRenderer());
			arrowY += .125;
			arrowYScreen += 1;
			time = SDL_GetTicks() - time;
			if (time < 3)
			{
				Sleep(2 - time);
			}
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
		//use_bow(data);
		thread = SDL_CreateThread(use_bow, "bow", data);
		SDL_WaitThread(thread, 0);
		//SDL_DetachThread(thread);
		break;
	case 2:
		thread = SDL_CreateThread(use_bombs, "bombs", data);
		SDL_DetachThread(thread);
		break;
	case 3:
		thread = SDL_CreateThread(use_slingshot, "slingshot", data);
		SDL_DetachThread(thread);
		break;
	case 4:
		thread = SDL_CreateThread(use_hookshot, "hookshot", data);
		SDL_DetachThread(thread);
		break;
	case 5:
		thread = SDL_CreateThread(use_lantern, "lantern", data);
		SDL_DetachThread(thread);
		break;
	case 6:
		thread = SDL_CreateThread(use_boomerang, "boomerang", data);
		SDL_DetachThread(thread);
		break;
	case 7:
		thread = SDL_CreateThread(use_hammer, "hammer", data);
		SDL_DetachThread(thread);
		break;
	case 8:
		thread = SDL_CreateThread(use_lightBow, "lightBow", data);
		SDL_DetachThread(thread);
		break;
	case 9:
		thread = SDL_CreateThread(use_boots, "boots", data);
		SDL_DetachThread(thread);
		break;
	case 10:
		thread = SDL_CreateThread(use_bottle1, "bottle", data);
		SDL_DetachThread(thread);
		break;
	case 11:
		thread = SDL_CreateThread(use_bottle2, "bottle", data);
		SDL_DetachThread(thread);
		break;
	case 12:
		thread = SDL_CreateThread(use_ocarina, "ocarina", data);
		SDL_DetachThread(thread);
		break;
	}
}