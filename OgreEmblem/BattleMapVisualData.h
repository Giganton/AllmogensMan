#pragma once
#include<vector>
#include "MapTile.h"
#include "SquadData.h"
#include "Cursor.h"

class BattleMapVisualData
{
	int mapWidth = -1;
	int mapHeight = -1;
	std::vector<std::vector<MapTileVisualData>> grid = { };

	std::vector<std::vector<std::pair<MapCoord, MapCoord>>> riverList;

	//CursorPos cursorPos;
public:
	BattleMapVisualData() {};
	BattleMapVisualData(std::vector<std::vector<MapTileVisualData>> grd, std::vector<std::vector<std::pair<MapCoord, MapCoord>>> rivers, int width, int height);

	std::vector<std::vector<MapTileVisualData>> getGrid() { return grid; };
	int getMapWidth() { return mapWidth; };
	int getMapHeight() { return mapHeight; };
	std::vector<std::vector<std::pair<MapCoord, MapCoord>>> getRivers() { return riverList; };
};