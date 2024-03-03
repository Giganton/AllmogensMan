#include "FighterFormation.h"
#include<stdexcept>
#include "Unit.h"
#include "SquadPos.h"

bool FighterFormation::isSpotEmpty(SpotPosition mapPos)
{
	return getSpot(mapPos).empty;
}

Unit* FighterFormation::getFighter(SpotPosition mapPos)
{
	if (isSpotEmpty(mapPos))
	{
		throw new std::exception();
	}
	return getSpot(mapPos).fighter;
}

Spot* FighterFormation::getSpotPointer(SpotPosition mapPos)
{
	switch (mapPos)
	{
	case SpotPosition::frontTop:
		return &frontTop;
		break;
	case SpotPosition::frontMid:
		return &frontMid;
		break;
	case SpotPosition::frontBot:
		return &frontBot;
		break;
	case SpotPosition::backTop:
		return &backTop;
		break;
	case SpotPosition::backMid:
		return &backMid;
		break;
	case SpotPosition::backBot:
		return &backBot;
		break;
	}
}

Spot FighterFormation::getSpot(SpotPosition mapPos)
{
	return *getSpotPointer(mapPos);
}

void FighterFormation::setFighter(Unit* fighter, SpotPosition mapPos)
{
	if (!isSpotEmpty(mapPos))
	{
		throw new std::exception();
	}
	getSpotPointer(mapPos)->fighter = fighter;
	getSpotPointer(mapPos)->empty = false;
}

void FighterFormation::setFighter(Unit* fighter, int x, int y)
{
	setFighter(fighter, transformCoord(x, y));
}

SpotPosition transformCoord(int x, int y)
{
	switch (x)
	{
	case 0:
		switch (y)
		{
		case 0:
			return SpotPosition::backTop;
		case 1:
			return SpotPosition::backMid;
		case 2:
			return SpotPosition::backBot;
		}
		break;
	case 1:
		switch (y)
		{
		case 0:
			return SpotPosition::frontTop;
		case 1:
			return SpotPosition::frontMid;
		case 2:
			return SpotPosition::frontBot;
		}
		break;
	}
}

int transformCoordX(SpotPosition mapPos)
{
	switch (mapPos)
	{
	case SpotPosition::frontTop:
	case SpotPosition::frontMid:
	case SpotPosition::frontBot:
		return 1;
		break;
	case SpotPosition::backTop:
	case SpotPosition::backMid:
	case SpotPosition::backBot:
		return 0;
		break;
	default:
		throw new std::exception();
		return -1;
	}
}
int transformCoordY(SpotPosition mapPos)
{
	switch (mapPos)
	{
	case SpotPosition::frontTop:
	case SpotPosition::backTop:
		return 0;
		break;
	case SpotPosition::frontMid:
	case SpotPosition::backMid:
		return 1;
		break;
	case SpotPosition::frontBot:
	case SpotPosition::backBot:
		return 2;
		break;
	default:
		throw new std::exception();
		return -1;
	}
}