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

	map *mapNorth;
	map *mapSouth;
	map *mapEast;
	map *mapWest;

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

	map *getMapSouth();
	void setMapSouth(map *);
	map *getMapNorth();
	void setMapNorth(map *);
	map *getMapEast();
	void setMapEast(map *);
	map *getMapWest();
	void setMapWest(map *);

};

std::vector<map> init_maps_out();
#endif /*MAP_H_*/