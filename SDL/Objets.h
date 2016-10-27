#ifndef OBJETS_H_
#define OBJETS_H_

#include <SDL2\SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

enum valeurObjetsEquipables { arc = 1, bombes, lancePierres, grappin, lanterne, boomerang, marteau, arcLumiere, superLancePierres, flacon1, flacon2, ocarina };
enum valeurObjetsNonEquipable { palmes = 1, gants1, gants2,  medaillonForce, medaillonSagesse, medaillonCourage, triforceForce, triforceSagesse, triforceCourage};
enum bottleContent{ empty = 0, redPotion, greenPotion, bluePotion, fairy };

class objets
{
private:
	std::vector<bool> objetEquipablePossede;
	std::vector<bool> objetNonEquipablePossede;
	std::vector<int> munitionsPossedees;
	SDL_Texture *imagesObjetsEquipables;
	SDL_Texture *imagesObjetsNonEquipables;
public:
	objets();
	objets(void *);
	bool getObjetEquipablePossede(int objetConcerne);
	void setObjetEquipablePossedes(int objetConcerne, bool possedeOuPas);
	bool getObjetNonEquipablePossede(int objetConcerne);
	void setObjetNonEquipablePossede(int objetConcerne, bool possedeOuPas);
	int getMunitionsPossedees(int objetConcerne);
	void setMunitionsPossedees(int objetConcerne, int nouvelleValeurMunitions);
	SDL_Texture *getImagesObjetsEquipables();
	void setImageObjetsEquipables(SDL_Texture *);
	SDL_Texture *getImageObjetsNonEquipables();
	void setImageObjetsNonEquipables(SDL_Texture *);
};

void use_objet(int, void *);

#endif /*OBJETS_H_*/