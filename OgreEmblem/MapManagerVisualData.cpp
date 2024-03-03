#include "MapManagerVisualData.h"

MapManagerVisualData::MapManagerVisualData(int idNr, BattleMapVisualData mpVis)
{
	ID = idNr;
	mapData = mpVis;
}

Menu MapManagerVisualData::getActiveMenu()
{
	if (!menuIsActive)
	{
		throw new std::exception();
	}
	return activeMenu;
}