#include "Map.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <SDL2/SDL.h>

extern std::vector<std::string> tilesetNames;
extern std::vector<int> tilesetWidths;
extern std::vector<int> tilesetHeights;
extern std::vector<map> maps;
enum outMap{ eVillageKokiri = 1, eForet, eLac = 3, eVillageZora, eJardinsChateau, ePlaineNord, eVillageHyrule, eDomaineLink, eSommetMontagne, eVillageGoron, ePlaineEst, eVillageGerudo };


void map::setWidth(int width)
{
	this->width = width;
}

void map::setHeight(int height)
{
	this->height = height;
}

void map::setTilesetName(std::string tilesetName)
{
	this->tilesetName = tilesetName;
}

void map::setTilesetValue(int val)
{
	this->tilesetNumber = val;
}

int map::getWidth()
{
	return (this->width);
}

int map::getHeight()
{
	return this->height;
}

std::string map::getTilesetName()
{
	return (this->tilesetName);
}

int map::getTilesetValue()
{
	return this->tilesetNumber;
}

void map::addLineFloor(std::vector<int> line)
{
	this->layerFloor.push_back(line);
}

void map::addLineWall(std::vector<int> line)
{
	this->layerWalls.push_back(line);
}

void map::addLineCeiling(std::vector<int> line)
{
	this->layerCeiling.push_back(line);
}

map::map(std::string filename)
{
	std::string actualStr;
	std::ifstream textFile(filename);
	getline(textFile, actualStr);
	this->width = atoi(actualStr.c_str());
	getline(textFile, actualStr);
	this->height = atoi(actualStr.c_str());
	getline(textFile, actualStr);
	this->tilesetName = "./data/images/" + actualStr;
	for (unsigned int i = 0; i < tilesetNames.size(); i++)
	{
		if (tilesetNames[i].compare(actualStr) == 0)
		{
			this->tilesetNumber = i;
			break;
		}
	}
	for (int i = 0; i < this->height; i++)
	{
		std::vector<int> actualLine;
		int actualValue = 0;
		getline(textFile, actualStr);
		for (unsigned int j = 0; j < actualStr.size(); j++)
		{
			if (actualStr[j] >= '0' && actualStr[j] <= '9')
			{
				actualValue *= 10;
				actualValue += actualStr[j] - '0';
			}
			else
			{
				actualLine.push_back(actualValue);
				actualValue = 0;
			}
		}
		if (i == (this->height - 1))
		actualLine.push_back(actualValue);
		this->layerFloor.push_back(actualLine);
	}
	for (int i = 0; i < this->height; i++)
	{
		std::vector<int> actualLine;
		int actualValue = 0;
		getline(textFile, actualStr);
		for (unsigned int j = 0; j < actualStr.size(); j++)
		{
			if (actualStr[j] >= '0' && actualStr[j] <= '9')
			{
				actualValue *= 10;
				actualValue += actualStr[j] - '0';
			}
			else
			{
				actualLine.push_back(actualValue);
				actualValue = 0;
			}
		}
		if (i == (this->height - 1))
		actualLine.push_back(actualValue);
		this->layerWalls.push_back(actualLine);
	}
	for (int i = 0; i < this->height; i++)
	{
		std::vector<int> actualLine;
		int actualValue = 0;
		getline(textFile, actualStr);
		for (unsigned int j = 0; j < actualStr.size(); j++)
		{
			if (actualStr[j] >= '0' && actualStr[j] <= '9')
			{
				actualValue *= 10;
				actualValue += actualStr[j] - '0';
			}
			else
			{
				actualLine.push_back(actualValue);
				actualValue = 0;
			}
		}
		if (i == (this->height - 1))
			actualLine.push_back(actualValue);
		this->layerCeiling.push_back(actualLine);
	}
}

map::map()
{
	this->height = 0;
	this->width = 0;
}

std::vector< std::vector<int> >map::getLayerFloor()
{
	return this->layerFloor;
}

std::vector< std::vector<int> >map::getLayerWalls()
{
	return this->layerWalls;
}

std::vector< std::vector<int> >map::getLayerCeiling()
{
	return this->layerCeiling;
}

int map::getMapSouth()
{
	return (this->mapSouth);
}

void map::setMapSouth(int newMap)
{
	this->mapSouth = newMap;
}

int map::getMapNorth()
{
	return this->mapNorth;
}

void map::setMapNorth(int newMap)
{
	this->mapNorth = newMap;
}

int map::getMapEast()
{
	return this->mapEast;
}

void map::setMapEast(int newMap)
{
	this->mapEast = newMap;
}

int map::getMapWest()
{
	return this->mapWest;
}

void map::setMapWest(int newMap)
{
	this->mapWest = newMap;
}

std::vector<map> init_maps_out()
{
	map villageKokiri("./data/maps/text_files/world/villageKokiri.txt");
	map foret("./data/maps/text_files/world/foret.txt");
	map lacHylia("./data/maps/text_files/world/lac.txt");
	map villageZora("./data/maps/text_files/world/villageZora.txt");
	map jardinsChateau("./data/maps/text_files/world/jardinsChateau.txt");
	map plaineNord("./data/maps/text_files/world/plaineNord.txt");
	map villageHyrule("./data/maps/text_files/world/villageHyrule.txt");
	map domaineLink("./data/maps/text_files/world/domaineLink.txt");
	map sommetMontagne("./data/maps/text_files/world/sommetMontagne.txt");
	map villageGoron("./data/maps/text_files/world/villageGoron.txt");
	map plaineEst("./data/maps/text_files/world/plaineEst.txt");
	map villageGerudo("./data/maps/text_files/world/villageGerudo.txt");

	villageKokiri.setMapNorth(NULL);
	villageKokiri.setMapSouth(eForet);
	villageKokiri.setMapEast(NULL);
	villageKokiri.setMapWest(NULL);
	foret.setMapNorth(eVillageKokiri);
	foret.setMapSouth(NULL);
	foret.setMapEast(ePlaineNord);
	foret.setMapWest(NULL);
	lacHylia.setMapNorth(NULL);
	lacHylia.setMapSouth(eVillageZora);
	lacHylia.setMapEast(eVillageHyrule);
	lacHylia.setMapWest(NULL);
	villageZora.setMapNorth(eLac);
	villageZora.setMapSouth(NULL);
	villageZora.setMapEast(NULL);
	villageZora.setMapWest(NULL);
	jardinsChateau.setMapNorth(NULL);
	jardinsChateau.setMapSouth(ePlaineNord);
	jardinsChateau.setMapEast(NULL);
	jardinsChateau.setMapWest(NULL);
	plaineNord.setMapNorth(eJardinsChateau);
	plaineNord.setMapSouth(eVillageHyrule);
	plaineNord.setMapEast(eVillageGoron);
	plaineNord.setMapWest(eForet);
	villageHyrule.setMapNorth(ePlaineNord);
	villageHyrule.setMapSouth(eDomaineLink);
	villageHyrule.setMapEast(ePlaineEst);
	villageHyrule.setMapWest(eLac);
	domaineLink.setMapNorth(eVillageHyrule);
	domaineLink.setMapSouth(NULL);
	domaineLink.setMapEast(NULL);
	domaineLink.setMapWest(NULL);
	sommetMontagne.setMapNorth(NULL);
	sommetMontagne.setMapSouth(eVillageGoron);
	sommetMontagne.setMapEast(NULL);
	sommetMontagne.setMapWest(NULL);
	villageGoron.setMapNorth(eSommetMontagne);
	villageGoron.setMapSouth(NULL);
	villageGoron.setMapEast(NULL);
	villageGoron.setMapWest(ePlaineNord);
	plaineEst.setMapNorth(NULL);
	plaineEst.setMapSouth(eVillageGerudo);
	plaineEst.setMapEast(NULL);
	plaineEst.setMapWest(eVillageHyrule);
	villageGerudo.setMapNorth(ePlaineEst);
	villageGerudo.setMapSouth(NULL);
	villageGerudo.setMapEast(NULL);
	villageGerudo.setMapWest(NULL);
	
	maps.push_back(villageKokiri);
	maps.push_back(foret);
	maps.push_back(lacHylia);
	maps.push_back(villageZora);
	maps.push_back(jardinsChateau);
	maps.push_back(plaineNord);
	maps.push_back(villageHyrule);
	maps.push_back(domaineLink);
	maps.push_back(sommetMontagne);
	maps.push_back(villageGoron);
	maps.push_back(plaineEst);
	maps.push_back(villageGerudo);
	return (maps);
}