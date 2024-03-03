#pragma once
#include "MapTile.h"
#include<string>
#include<map>
#include<vector>
#include "Cursor.h"
#include<list>
#include "Squad.h"
#include "SquadData.h"
#include "MapCoord.h"
#include "BattleMapVisualData.h"
#include "tagID.h"
#include <SFML/Graphics/Image.hpp>

#define MAX_MAP_X 30
#define MAX_MAP_Y 30
//red
#define MAPGRASS 0b10000000
#define MAPRIVERN 0b00000001
#define MAPRIVERE 0b00000010
#define MAPRIVERS 0b00000100
#define MAPRIVERW 0b00001000
//blue
#define MAPCSTART 0b00001000
#define MAPPSTART 0b00000100
#define MAPE1START 0b00000010
#define MAPE2START 0b00000001

class BattleMap
{
private:
	std::vector<std::vector<MapTile>> grid;
	//std::map<Squad*, MapCoord> squadMap;
	//std::map<int, MapCoord> squadIDMap;
	std::map<tagID, std::vector<MapCoord>> startingPositions;
	std::map<std::string, TerrainTypes> stringToTerrainTypeMap;

	std::vector<std::pair<MapCoord, MapCoord>> riverCoords;

	BattleMapVisualData mapVisuals;

	int height = 0;
	int width = 0;

	std::vector<std::vector<std::pair<MapCoord, MapCoord>>> riversOnMap;

	//Cursor cursor;
	CursorPos cursorStartingPoint;

	std::vector<int> sortIndices(std::vector<int> vector);
	void initStartingPositions();
	MapTile handleRedPixel(sf::Uint8 pixelVal, MapCoord tileCoord);
	void handleBluePixel(sf::Uint8 pixelVal, MapCoord coord);

	Direction neighbourDirection(MapCoord tile1, MapCoord tile2);
	void readMap(std::string path);
	std::pair<MapCoord, MapCoord> createRiver(MapCoord gridpoint1, MapCoord gridpoint2);
	void addRiverToMap(std::pair<MapCoord, MapCoord> river);
	
public:
	BattleMap() {};
	BattleMap(std::string imagePath, std::map<std::string, TerrainTypes> terrainMap);
	//~BattleMap();
	//BattleMap(const BattleMap& cpMap);
	//BattleMap& operator=(const BattleMap asMap);

	bool withinBounds(int x, int y);
	bool withinBounds(MapCoord mapPos);
	bool neighbouringTiles(MapCoord tile1, MapCoord tile2);

	BattleMapVisualData getVisuals();

	int getHeight() { return height; };
	int getWidth() { return width; };

	MapTile* getTile(int x, int y);
	MapTile* getTile(MapCoord coord);
	bool doesTileExist(MapCoord coord);

	bool riverConnection(MapCoord tile1, MapCoord tile2);

	bool isCoordPassable(MapCoord coord);
	bool isCoordStandable(MapCoord coord);

	MapTile* getHoveredTile(Cursor cursor);
	Terrain getHoveredTerrain(Cursor cursor);
	bool isHoveredPassable(Cursor cursor);
	bool doesHoveredExist(Cursor cursor);

	CursorPos getCursorStartingPos() { return cursorStartingPoint; };

	Cursor setCursorPos(Cursor cursor, int posX, int posY);

	Cursor moveCursorUp(Cursor cursor);
	Cursor moveCursorDown(Cursor cursor);
	Cursor moveCursorLeft(Cursor cursor);
	Cursor moveCursorRight(Cursor cursor);

	void addStartingPos(tagID tag, MapCoord coord);
	std::vector<MapCoord> getStartingPositions(tagID tag) { return startingPositions.find(tag)->second; };

	std::map<tagID, std::vector<MapCoord>> getStartingPosMap() { return startingPositions; };
};