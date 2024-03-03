#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "MapCoord.h"
#include "tagID.h"
#include "Squad.h"
#include "GraphicsUtils.h"
#include "UnitRepresentation.h"

class SquadRepresentation
{
private:
	void setupUnitSprites(Squad sqd);
public:
	SquadRepresentation() {};
	SquadRepresentation(Squad sqd, UTIL::ScreenCoord sqdSpriteSize, tagID flagTag, MapCoord position, bool living);
	SquadRepresentation(Squad sqd, UTIL::ScreenCoord sqdSpriteSize, tagID flagTag, UTIL::ScreenCoord position); //for menu drawing

	int squadID = -1;
	std::vector<UnitRepresentation> frontRowUnits;
	std::vector<UnitRepresentation> backRowUnits;

	
	UTIL::ScreenCoord squadSpriteSize;

	std::string squadName;

	bool animated = true;
	bool onMap = false;
	MapCoord mapPos;
	UTIL::ScreenCoord menuPos;

	tagID tag = tagID::noID;
	bool alive = false;

	void killUnit(int unitID);
	UnitRepresentation getUnit(int unitID);
};