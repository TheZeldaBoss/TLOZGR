#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <string>
#include <SDL2\SDL.h>


class map
{
private:
	int width;
	int height;
	std::string tilesetName;
	int tilesetNumber;

	std::vector< std::vector<int> >layerFloor;
	std::vector< std::vector<int> >layerWalls;
	std::vector< std::vector<int> >layerCeiling;
public:
	void setWidth(int);
	void setHeight(int);
	void setTilesetName(std::string);
	void setTilesetValue(int);
	int getWidth();
	int getHeight();
	std::string getTilesetName();
	int getTilesetValue();
	void addLineFloor(std::vector<int>);
	void addLineWall(std::vector<int>);
	void addLineCeiling(std::vector<int>);
	std::vector< std::vector<int> >getLayerFloor();
	std::vector< std::vector<int> >getLayerWalls();
	std::vector< std::vector<int> >getLayerCeiling();
	map(std::string filename);
	map();
};
#endif /*MAP_H_*/