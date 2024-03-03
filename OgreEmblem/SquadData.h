#pragma once
#include "Squad.h"
#include "MapCoord.h"


class SquadData
{
public:
	Squad squad;
	MapCoord mapPos;
	SquadData(Squad sqd, MapCoord coord) { squad = sqd; mapPos = coord; };
	SquadData() {};
};