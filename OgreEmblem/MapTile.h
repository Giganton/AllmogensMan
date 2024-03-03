#pragma once
#include "Terrain.h"
#include "Squad.h"
#include "Direction.h"

class MapTileVisualData
{
public:
	Terrain terrain;
	std::vector<Direction> riverSides;
};

class MapTile
{
private:
	bool tileExists = false;
	Terrain terrain;

	bool riverNorth = false;
	bool riverEast = false;
	bool riverSouth = false;
	bool riverWest = false;

	bool passable = false;
	bool standable = false;

public:
	MapTile();
	MapTile(Terrain terrainValue);
	MapTile(Terrain terrainValue, std::vector<Direction> riverSides);
	void addRiver(Direction side);
	bool isRiver(Direction side);
	bool isPassable() { return passable; };
	bool isStandable() { return (standable); };
	Terrain getTerrain() { return terrain; };
	bool exists() { return tileExists; };

	MapTileVisualData getVisuals();
};