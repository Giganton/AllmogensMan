#include "SquadRepresentation.h"
#include "GraphicsUtils.h"

SquadRepresentation::SquadRepresentation(Squad sqd, UTIL::ScreenCoord sqdSpriteSize, tagID flagTag, MapCoord position, bool living)
{
	squadID = sqd.getID();
	onMap = true;
	animated = true;
	
	squadName = sqd.getName();

	mapPos = position;
	squadSpriteSize = sqdSpriteSize;

	setupUnitSprites(sqd);

	tag = flagTag;
	alive = living;
}

SquadRepresentation::SquadRepresentation(Squad sqd, UTIL::ScreenCoord sqdSpriteSize, tagID flagTag, UTIL::ScreenCoord position)
{
	squadID = sqd.getID();
	onMap = false;
	animated = false;

	squadName = sqd.getName();

	menuPos = position;
	squadSpriteSize = sqdSpriteSize;

	setupUnitSprites(sqd);

	tag = flagTag;
	alive = true;
}

void SquadRepresentation::setupUnitSprites(Squad sqd)
{
	int i;
	std::vector<ProfessionTag> frontProfs = sqd.getFrontProfTags();
	std::vector<ProfessionTag> backProfs = sqd.getBackProfTags();
	std::vector<int> frontIDs = sqd.getFrontIDs();
	std::vector<int> backIDs = sqd.getBackIDs();

	UTIL::ScreenCoord sqdPos;
	if (onMap)
	{
		sqdPos = UTIL::mapCoordToScreenCoord(mapPos.getX(), mapPos.getY());
	}
	else
	{
		sqdPos = menuPos;
	}

	UTIL::ScreenCoord spriteOffset = UTIL::ScreenCoord(squadSpriteSize.x / 2, squadSpriteSize.y / 2);
	UTIL::ScreenCoord centerOffset = UTIL::ScreenCoord(TILE_W / 2, TILE_H / 2);
	float backOffset = 40;
	float frontOffset = 45;
	UTIL::ScreenCoord generalOffset = centerOffset - spriteOffset;

	for (i = 0; i < frontIDs.size(); i++)
	{
		if (backIDs.at(i) != -1)
		{
			//sf::Sprite temp = sf::Sprite(sqdTMap->find(backProfs.at(i)->getTag())->second);
			Unit* unit = sqd.findUnitPtr(backIDs.at(i));
			UnitRepresentation temp = UnitRepresentation(backIDs.at(i), backProfs.at(i), unit->isDead());
			float yOffset = -15;
			if (i == 1)
			{
				yOffset = yOffset + 5;
			}
			UTIL::ScreenCoord offset = generalOffset + UTIL::ScreenCoord((i - 1) * backOffset, yOffset);
			temp.position = sqdPos + offset;
			backRowUnits.push_back(temp);

		}
		if (frontIDs.at(i) != -1)
		{
			//sf::Sprite temp = sf::Sprite(sqdTMap->find(frontProfs.at(i)->getTag())->second);
			Unit* unit = sqd.findUnitPtr(frontIDs.at(i));
			UnitRepresentation temp = UnitRepresentation(frontIDs.at(i), frontProfs.at(i), unit->isDead());
			float yOffset = 5;
			if (i == 1)
			{
				yOffset = yOffset + 15;
			}
			UTIL::ScreenCoord offset = generalOffset + UTIL::ScreenCoord((i - 1) * frontOffset, yOffset);
			temp.position = sqdPos + offset;
			frontRowUnits.push_back(temp);
		}
	}
}

void SquadRepresentation::killUnit(int unitID)
{
	unsigned int i;
	bool unitKilled = false;
	for (i = 0; i < backRowUnits.size(); i++)
	{
		if (backRowUnits.at(i).unitID == unitID)
		{
			backRowUnits.at(i).isDead = true;
			unitKilled = true;
			break;
		}
	}
	if (!unitKilled)
	{
		for (i = 0; i < frontRowUnits.size(); i++)
		{
			if (frontRowUnits.at(i).unitID == unitID)
			{
				frontRowUnits.at(i).isDead = true;
				unitKilled = true;
				break;
			}
		}
	}
	if (!unitKilled)
	{
		throw new std::exception();
	}
}

UnitRepresentation SquadRepresentation::getUnit(int unitID)
{
	unsigned int i;
	for (i = 0; i < backRowUnits.size(); i++)
	{
		if (backRowUnits.at(i).unitID == unitID)
		{
			return backRowUnits.at(i);
		}
	}
	for (i = 0; i < frontRowUnits.size(); i++)
	{
		if (frontRowUnits.at(i).unitID == unitID)
		{
			return frontRowUnits.at(i);
		}
	}
	throw new std::exception();
}