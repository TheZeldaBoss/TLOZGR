#include "Map.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

extern std::vector<std::string> tilesetNames;
extern std::vector<int> tilesetWidths;
extern std::vector<int> tilesetHeights;

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