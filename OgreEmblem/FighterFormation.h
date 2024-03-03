#pragma once
#include "Fighter.h"
#include<stdexcept>

enum class SpotPosition { none, frontTop, frontMid, frontBot, backTop, backMid, backBot };
class Unit;

class Spot
{
public:
	Spot() {};

	SpotPosition mapPos = SpotPosition::none;
	Unit* fighter = nullptr;
	bool empty = true;
};

class FighterFormation
{
private:
	Spot frontTop;
	Spot frontMid;
	Spot frontBot;

	Spot backTop;
	Spot backMid;
	Spot backBot;

	Spot* getSpotPointer(SpotPosition mapPos);
public:
	FighterFormation() {};

	bool isSpotEmpty(SpotPosition mapPos);
	Spot getSpot(SpotPosition mapPos);
	Unit* getFighter(SpotPosition mapPos);
	void setFighter(Unit* fighter, SpotPosition mapPos);
	void setFighter(Unit* fighter, int x, int y);
};

/*std::pair<int, int> transformCoord(SpotPosition pos)
{
	switch (pos)
	{
	case SpotPosition::frontTop:
		return std::make_pair(1, 0);
		break;
	case SpotPosition::frontMid:
		return std::make_pair(1, 1);
		break;
	case SpotPosition::frontBot:
		return std::make_pair(1, 2);
		break;
	case SpotPosition::backTop:
		return std::make_pair(2, 0);
		break;
	case SpotPosition::backMid:
		return std::make_pair(2, 1);
		break;
	case SpotPosition::backBot:
		return std::make_pair(2, 2);
		break;
	}
}*/
int transformCoordX(SpotPosition mapPos);
int transformCoordY(SpotPosition mapPos);
SpotPosition transformCoord(int x, int y);