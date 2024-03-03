#include "MapTile.h"
#include<exception>
#include "Squad.h"

MapTile::MapTile()
{
	tileExists = false;
	passable = false;

}

MapTile::MapTile(Terrain terrainValue)
{
	terrain = terrainValue;
	if (terrainValue.getType() != TerrainTypes::noTerrain)
	{
		tileExists = true;
		passable = true;
		standable = true;
	}
}
MapTile::MapTile(Terrain terrainValue, std::vector<Direction> riverSides) : MapTile(terrainValue)
{
	int i;
	for (i = 0; i < riverSides.size(); i++)
	{
		addRiver(riverSides.at(i));
	}
}
void MapTile::addRiver(Direction side)
{
	switch (side)
	{
	case Direction::up:
		riverNorth = true;
		break;
	case Direction::right:
		riverEast = true;
		break;
	case Direction::down:
		riverSouth = true;
		break;
	case Direction::left:
		riverWest = true;
		break;
	}
}

bool MapTile::isRiver(Direction side)
{
	switch (side)
	{
	case Direction::up:
		return riverNorth;
		break;
	case Direction::right:
		return riverEast;
		break;
	case Direction::down:
		return riverSouth;
		break;
	case Direction::left:
		return riverWest;
		break;
	}
}

MapTileVisualData MapTile::getVisuals()
{
	MapTileVisualData retVal;
	retVal.terrain = terrain;
	if (riverNorth)
	{
		retVal.riverSides.push_back(Direction::up);
	}
	if (riverEast)
	{
		retVal.riverSides.push_back(Direction::right);
	}
	if (riverSouth)
	{
		retVal.riverSides.push_back(Direction::down);
	}
	if (riverWest)
	{
		retVal.riverSides.push_back(Direction::left);
	}
	return retVal;
}