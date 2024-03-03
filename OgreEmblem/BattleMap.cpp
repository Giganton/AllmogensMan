#include "BattleMap.h"
#include<exception>
#include <numeric>     
#include <algorithm>  
#include "json.hpp"
#include<fstream>

using json = nlohmann::json;

BattleMap::BattleMap(std::string imagePath, std::map<std::string, TerrainTypes> terrainMap)
{
	initStartingPositions();
	stringToTerrainTypeMap = terrainMap;

	readMap(imagePath);
}

void BattleMap::readMap(std::string path)
{
	std::vector<std::vector<MapTileVisualData>> visualGrid;
	std::ifstream file(path);
	json jSon, j2;
	file >> jSon;
	unsigned int i, j;
	height = jSon["height"];
	width = jSon["width"];
	cursorStartingPoint = CursorPos(jSon["cursor_starting_tile"]["x"], jSon["cursor_starting_tile"]["y"]);

	//initiera kartnät och dess visuella version
	for (i = 0; i < width; i++)
	{
		std::vector<MapTile> kolonn;
		for (j = 0; j < height; j++)
		{
			MapTile temp = MapTile();
			kolonn.push_back(temp);
		}
		grid.push_back(kolonn);
	}

	//peta in data från json-fil i rutnät
	for (i = 0; i < jSon["tiles"].size(); i++)
	{
		json tileInfo = jSon["tiles"][i];
		int xPos = tileInfo["x"];
		int yPos = tileInfo["y"];
		std::string terrainName = tileInfo["terrain"];
		MapTile tile = MapTile(stringToTerrainTypeMap.find(terrainName)->second);
		grid.at(xPos).at(yPos) = tile;
	}

	for (i = 0; i < jSon["player_starting_tiles"].size(); i++)
	{
		json info = jSon["player_starting_tiles"][i];
		int xPos = info["x"];
		int yPos = info["y"];
		addStartingPos(tagID::player, MapCoord(xPos, yPos));
	}
	for (i = 0; i < jSon["enemy_starting_tiles"].size(); i++)
	{
		json info = jSon["enemy_starting_tiles"][i];
		int xPos = info["x"];
		int yPos = info["y"];
		addStartingPos(tagID::redEnemy, MapCoord(xPos, yPos));
	}
	std::vector<MapCoord> riverDots;
	std::vector<std::pair<MapCoord, MapCoord>> riverPairs; //river unit defined as pair of map tiles that river crosses
	for (i = 0; i < jSon["rivers"].size(); i++)
	{
		riverPairs.clear();
		json river = jSon["rivers"][i];
		for (j = 0; j < river.size() - 1; j++)
		{
			MapCoord gridPoint1 = MapCoord(river[j][0], river[j][1]);
			MapCoord gridPoint2 = MapCoord(river[j + 1][0], river[j + 1][1]);
			std::pair<MapCoord, MapCoord> pair = createRiver(gridPoint1, gridPoint2);
			addRiverToMap(pair);
			riverPairs.push_back(pair);
		}
		riversOnMap.push_back(riverPairs);
	}

	std::vector<MapTileVisualData> visualKolonn;
	for (i = 0; i < width; i++)
	{
		std::vector<MapTileVisualData> visualKolonn;
		for (j = 0; j < height; j++)
		{
			visualKolonn.push_back(grid.at(i).at(j).getVisuals());
		}
		visualGrid.push_back(visualKolonn);
	}
	
	mapVisuals = BattleMapVisualData(visualGrid, riversOnMap, width, height);
}

void BattleMap::addRiverToMap(std::pair<MapCoord, MapCoord> river)
{
	MapCoord a = river.first;
	MapCoord b = river.second;
	Direction nbDir = neighbourDirection(a, b);
	grid.at(a.getX()).at(a.getY()).addRiver(nbDir);
	grid.at(b.getX()).at(b.getY()).addRiver(DIR::oppositeDirection(nbDir));
}

std::pair<MapCoord, MapCoord> BattleMap::createRiver(MapCoord gridpoint1, MapCoord gridpoint2)
{
	if (!neighbouringTiles(gridpoint1, gridpoint2))
	{
		throw new std::exception();
	}
	MapCoord pos1, pos2;
	Direction riverDir = neighbourDirection(gridpoint1, gridpoint2);
	switch (riverDir)
	{
	case Direction::up:
		pos1 = gridpoint1 + MapCoord(-1, -1);
		pos2 = gridpoint1 + MapCoord(0, -1);
		break;
	case Direction::right:
		pos1 = gridpoint1 + MapCoord(0,-1);
		pos2 = gridpoint1;
		break;
	case Direction::down:
		pos1 = gridpoint1;
		pos2 = gridpoint1 + MapCoord(-1, 0);
		break;
	case Direction::left:
		pos1 = gridpoint1 + MapCoord(-1, 0);
		pos2 = gridpoint1 + MapCoord(-1, -1);
		break;
	}
	return std::make_pair(pos1, pos2);
}

MapTile BattleMap::handleRedPixel(sf::Uint8 pixelVal, MapCoord tileCoord)
{
	MapTile retVal;
	if (pixelVal > 0)
	{
		if (pixelVal & MAPGRASS)
		{
			retVal = MapTile(Terrain(TerrainTypes::field));
		}
		if (pixelVal & MAPRIVERN)
		{
			retVal.addRiver(Direction::up);
			riverCoords.push_back(std::make_pair(tileCoord + MapCoord(1, 0) , tileCoord + MapCoord(1, 1)));
		}
		if (pixelVal & MAPRIVERE)
		{
			retVal.addRiver(Direction::right);
			riverCoords.push_back(std::make_pair(tileCoord + MapCoord(1, 1), tileCoord + MapCoord(0, 1)));
		}
		if (pixelVal & MAPRIVERS)
		{
			retVal.addRiver(Direction::down);
			riverCoords.push_back(std::make_pair(tileCoord + MapCoord(0, 0), tileCoord + MapCoord(0, 1)));
		}
		if (pixelVal & MAPRIVERW)
		{
			retVal.addRiver(Direction::left);
			riverCoords.push_back(std::make_pair(tileCoord + MapCoord(0, 0), tileCoord + MapCoord(1, 0)));
		}
	}
	return retVal;
}

void BattleMap::handleBluePixel(sf::Uint8 pixelVal, MapCoord coord)
{
	if (pixelVal & MAPPSTART)
	{
		addStartingPos(tagID::player, coord);
	}
	if (pixelVal & MAPE1START)
	{
		addStartingPos(tagID::redEnemy, coord);
	}
	if (pixelVal & MAPE2START)
	{
		addStartingPos(tagID::greenEnemy, coord);
	}
	if (pixelVal & MAPCSTART)
	{
		cursorStartingPoint = CursorPos(coord.getX(), coord.getY());
	}
}

/*BattleMap::~BattleMap()
{
	delete grid;
}

BattleMap::BattleMap(const BattleMap& cpMap)
{
	grid = new std::vector<std::vector<MapTile>>;
	if (cpMap.grid == nullptr)
	{
		grid = nullptr;
	}
	else
	{
		*grid = *cpMap.grid;
	}

	mapVisuals = cpMap.mapVisuals;
	startingPositions = cpMap.startingPositions;

	height = cpMap.height;
	width = cpMap.width;
	cursorStartingPoint = cpMap.cursorStartingPoint;
}

BattleMap& BattleMap::operator=(const BattleMap asMap)
{
	grid = new std::vector<std::vector<MapTile>>;
	if (asMap.grid == nullptr)
	{
		grid = nullptr;
	}
	else
	{
		*grid = *asMap.grid;
	}

	mapVisuals = asMap.mapVisuals;
	startingPositions = asMap.startingPositions;

	height = asMap.height;
	width = asMap.width;
	cursorStartingPoint = asMap.cursorStartingPoint;
	
	return *this;
}*/

void BattleMap::initStartingPositions()
{
	//add players to startinglocation list
	std::vector<MapCoord> temp;
	startingPositions.insert({ tagID::player, temp });
	startingPositions.insert({ tagID::redEnemy, temp });
	startingPositions.insert({ tagID::greenEnemy, temp });
}

BattleMapVisualData BattleMap::getVisuals()
{
	return mapVisuals;
}

/*std::vector<SquadData> BattleMap::getSquadList()
{
	std::vector<SquadData> retVal;
	for (std::map<Squad*, MapCoord>::iterator it = squadMap.begin(); it != squadMap.end(); ++it) {
		retVal.push_back(SquadData(*it->first, it->second));
	}
	return retVal;
}*/

MapTile* BattleMap::getTile(int x, int y)
{
	return &grid.at(x).at(y);
}

MapTile* BattleMap::getTile(MapCoord coord)
{
	return &grid.at(coord.getX()).at(coord.getY());
}

bool BattleMap::doesTileExist(MapCoord coord)
{
	if (!withinBounds(coord))
	{
		throw new std::exception();
	}
	if (getTile(coord)->exists())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BattleMap::withinBounds(int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return false;
	}
	return true;
}

bool BattleMap::withinBounds(MapCoord mapPos)
{
	if (mapPos.getX() < 0 || mapPos.getX() >= width || mapPos.getY() < 0 || mapPos.getY() >= height)
	{
		return false;
	}
	return true;
}


bool BattleMap::isCoordPassable(MapCoord coord)
{
	return (withinBounds(coord) && getTile(coord.getX(), coord.getY())->isPassable());
}
bool BattleMap::isCoordStandable(MapCoord coord)
{
	return (withinBounds(coord) && getTile(coord.getX(), coord.getY())->isStandable());
}

Cursor BattleMap::setCursorPos(Cursor crsor, int posX, int posY)
{
	crsor.setPos(posX, posY);
	return crsor;
}

std::vector<int> BattleMap::sortIndices(std::vector<int> vector)
{
	std::vector<int> retVal(vector.size());
	std::iota(retVal.begin(), retVal.end(), 0); //initierar indexvektorn 0,1,2,...

	std::sort(retVal.begin(), retVal.end(), [&vector](int i1, int i2) {return vector[i1] < vector[i2]; });
	return retVal;
}


MapTile* BattleMap::getHoveredTile(Cursor crsor)
{
	return getTile(crsor.getX(), crsor.getY());
}

Terrain BattleMap::getHoveredTerrain(Cursor crsor)
{
	return getHoveredTile(crsor)->getTerrain();
}

bool BattleMap::isHoveredPassable(Cursor crsor)
{
	return getTile(crsor.getX(), crsor.getY())->isPassable();
}

bool BattleMap::doesHoveredExist(Cursor crsor)
{
	return getTile(crsor.getX(), crsor.getY())->exists();
}

Cursor BattleMap::moveCursorUp(Cursor crsor)
{
	int x = crsor.getX();
	int y = crsor.getY();
	if (!getTile(x, y)->exists())
	{
		throw new std::exception();
	}

	if (y > 0 && getTile(x, y - 1)->exists())
	{
		CursorPos newPos = CursorPos(x, y - 1);
		crsor.move(newPos);
		return crsor;
	}
	else
	{
		return crsor;
	}
}

Cursor BattleMap::moveCursorDown(Cursor crsor)
{
	int x = crsor.getX();
	int y = crsor.getY();

	if (!getTile(x, y)->exists())
	{
		throw new std::exception();
	}

	if (y < height - 1 && getTile(x, y + 1)->exists())
	{
		CursorPos newPos = CursorPos(x, y + 1);
		crsor.move(newPos);
		return crsor;
	}
	else
	{
		return crsor;
	}
}
Cursor BattleMap::moveCursorLeft(Cursor crsor)
{
	int x = crsor.getX();
	int y = crsor.getY();

	if (!getTile(x, y)->exists())
	{
		throw new std::exception();
	}

	if (x > 0 && getTile(x - 1, y)->exists())
	{
		CursorPos newPos = CursorPos(x - 1, y);
		crsor.move(newPos);
		return crsor;
	}
	else
	{
		return crsor;
	}
}
Cursor BattleMap::moveCursorRight(Cursor crsor)
{
	int x = crsor.getX();
	int y = crsor.getY();

	if (!getTile(x, y)->exists())
	{
		throw new std::exception();
	}

	if (x < width - 1 && getTile(x + 1, y)->exists())
	{
		CursorPos newPos = CursorPos(x + 1, y);
		crsor.move(newPos);
		return crsor;
	}
	else
	{
		return crsor;
	}
}

void BattleMap::addStartingPos(tagID tag, MapCoord mapPos)
{
	std::vector<MapCoord> temp = startingPositions.find(tag)->second;
	temp.push_back(mapPos);
	startingPositions.find(tag)->second = temp;
}

bool BattleMap::riverConnection(MapCoord tile1, MapCoord tile2)
{
	return getTile(tile1)->isRiver(neighbourDirection(tile1, tile2));
}

bool BattleMap::neighbouringTiles(MapCoord tile1, MapCoord tile2)
{
	if (tile1 + MapCoord(1, 0) == tile2)
	{
		return true;
	}
	else if (tile1 + MapCoord(-1, 0) == tile2)
	{
		return true;
	}
	else if (tile1 + MapCoord(0, 1) == tile2)
	{
		return true;
	}
	else if (tile1 + MapCoord(0, -1) == tile2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Direction BattleMap::neighbourDirection(MapCoord tile1, MapCoord tile2)
{
	if (tile1 + MapCoord(1, 0) == tile2)
	{
		return Direction::right;
	}
	else if (tile1 + MapCoord(-1, 0) == tile2)
	{
		return Direction::left;
	}
	else if (tile1 + MapCoord(0, 1) == tile2)
	{
		return Direction::down;
	}
	else if (tile1 + MapCoord(0, -1) == tile2)
	{
		return Direction::up;
	}
	else
	{
		throw new std::exception();
	}
}