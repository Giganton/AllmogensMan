#include "BattleMapVisualData.h"

BattleMapVisualData::BattleMapVisualData(std::vector<std::vector<MapTileVisualData>> grd, std::vector<std::vector<std::pair<MapCoord, MapCoord>>> rivers, int width, int height)
{
	grid = grd;
	mapWidth = width;
	mapHeight = height;
	riverList = rivers;
}