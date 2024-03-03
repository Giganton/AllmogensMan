#include "SquadAnimation.h"
#include "SquadData.h"
#include "MovementStage.h"
#include "GraphicsUtils.h"
#include "CameraController.h"

SquadAnimation::SquadAnimation(std::map < ProfessionTag, sf::Texture>* sqdTMap, CameraController* dBucket)
{
	squadTextureMap = sqdTMap;
	drawBucket = dBucket;

	deathAnim = DeathAnimation(sqdTMap, dBucket);
	spriteAnim = SpriteAnimator(squadSpriteSize, animStepTime, nrOfAnimSteps);

	squadDrawer = SquadDrawer(sqdTMap);
}

void SquadAnimation::drawMapSquad(SquadRepresentation sqd)
{
	/*unsigned int i;
	sf::IntRect textureRect = spriteAnim.getTextureRectangle();

	for (i = 0; i < sqd.backRowUnits.size(); i++)
	{
		UnitRepresentation unit = sqd.backRowUnits.at(i);
		if (!unit.isDead)
		{
			sf::Sprite temp = sf::Sprite();
			temp.setTexture(squadTextureMap->find(unit.profession)->second);
			temp.setPosition(unit.position.x, unit.position.y);

			temp.setTextureRect(textureRect);
			drawBucket->addToBucket(temp);
		}
	}
	for (i = 0; i < sqd.frontRowUnits.size(); i++)
	{
		UnitRepresentation unit = sqd.frontRowUnits.at(i);
		if (!unit.isDead)
		{
			sf::Sprite temp = sf::Sprite();
			temp.setTexture(squadTextureMap->find(unit.profession)->second);
			temp.setPosition(unit.position.x, unit.position.y);

			temp.setTextureRect(textureRect);
			drawBucket->addToBucket(temp);
		}
	}*/
	std::vector<sf::Sprite> sprites = squadDrawer.drawMapSquad(sqd);
	unsigned int i;
	for (i = 0; i < sprites.size(); i++)
	{
		drawBucket->addToBucket(sprites.at(i));
	}
}

void SquadAnimation::draw()
{
	sf::IntRect textureRect = spriteAnim.getTextureRectangle();

	std::map<int, SquadRepresentation>::iterator it;
	for (it = squadSpriteMap.begin(); it != squadSpriteMap.end(); it++)
	{
		drawMapSquad(it->second);
	}
	if (moveAnim.isActive())
	{
		moveAnim.draw();
		if (moveAnim.isAnimationFinished())
		{
			squadSpriteMap.insert({ moveAnim.getSquadRep().squadID , moveAnim.getSquadRep() });
			squadSpriteMap.find(moveAnim.getSquadRep().squadID)->second.mapPos = moveAnim.getDestination();
			moveAnimDoneToggle = true;
		}
	}
	deathAnim.draw();
}


void SquadAnimation::init(std::vector<SquadData> sqdData)
{
	unsigned int i;
	squadSpriteMap.clear();
	for (i = 0; i < sqdData.size(); i++)
	{
		//std::string prof = sqdData.at(i).squad.getLeadProfName();
		//sf::Texture* texturePointer = &squadTextureMap->find(prof)->second;
		SquadRepresentation temp = SquadRepresentation(sqdData.at(i).squad, squadSpriteSize, sqdData.at(i).squad.getFlagTag(), sqdData.at(i).mapPos, !sqdData.at(i).squad.isDefeated());

		tagID squadTag = temp.tag;
		/*switch (squadTag)
		{
		case tagID::player:
			temp.sprite.setColor(sf::Color(255, 255, 255));
			break;
		case tagID::redEnemy:
			temp.sprite.setColor(sf::Color(255, 0, 0));
			break;
		case tagID::greenEnemy:
			temp.sprite.setColor(sf::Color(0, 255, 0));
			break;
		}*/

		squadSpriteMap.insert({ sqdData.at(i).squad.getID() , temp });
	}
}

/*std::vector<sf::Sprite> SquadAnimation::placeUnitSprites(SquadRepresentation squadRep)
{
	std::vector<sf::Sprite> retVal;
	int i;
	UTIL::ScreenCoord sqdPos = UTIL::mapCoordToScreenCoord(squadRep.pos.getX(), squadRep.pos.getY());

	std::vector<UTIL::ScreenCoord> frontOffsets = { UTIL::ScreenCoord(20,50) , UTIL::ScreenCoord(20,0) ,UTIL::ScreenCoord(20,-50) };
	std::vector<UTIL::ScreenCoord> backOffsets = { UTIL::ScreenCoord(0,50) , UTIL::ScreenCoord(0,0) ,UTIL::ScreenCoord(0,-50) };

	for (i = 0; i < squadRep.frontRow.size(); i++)
	{
		if (squadRep.frontRow.at(i) != nullptr)
		{
			sf::Sprite temp = sf::Sprite(squadTextureMap->find(squadRep.frontRow.at(i)->getName())->second);
			temp.setPosition((sqdPos + frontOffsets.at(i)).x, (sqdPos + frontOffsets.at(i)).y);
			retVal.push_back(temp);
		}
		if (squadRep.backRow.at(i) != nullptr)
		{
			sf::Sprite temp = sf::Sprite(squadTextureMap->find(squadRep.backRow.at(i)->getName())->second);
			temp.setPosition((sqdPos + backOffsets.at(i)).x, (sqdPos + backOffsets.at(i)).y);
			retVal.push_back(temp);
		}
	}
	return retVal;
}*/

void SquadAnimation::startMovementAnimation(MoveData mData)
{
	SquadRepresentation temp = squadSpriteMap.find(mData.movedSquadID)->second;
	squadSpriteMap.erase(mData.movedSquadID);
	moveAnim = MovementAnimation(squadTextureMap, temp, mData.path, TILE_W, TILE_H, drawBucket);
}


bool SquadAnimation::isMoveAnimationDone()
{
	return moveAnimDoneToggle;
}


void SquadAnimation::animationEndingHandled()
{
	if (!moveAnimDoneToggle)
	{
		throw new std::exception();
	}
	moveAnimDoneToggle = false;
}

MapCoord SquadAnimation::getSquadCoord(int ID)
{
	return squadSpriteMap.find(ID)->second.mapPos;
}

tagID SquadAnimation::getSquadTag(int id)
{ 
	return squadSpriteMap.find(id)->second.tag; 
}

void SquadAnimation::killUnit(int squadID, int unitID)
{
	squadSpriteMap.find(squadID)->second.killUnit(unitID);
	deathAnim.addDeath(squadSpriteMap.find(squadID)->second.getUnit(unitID));
}