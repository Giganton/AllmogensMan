#include "SquadDrawer.h"
#include "GraphicsAssets.h"

SquadDrawer::SquadDrawer(std::map < ProfessionTag, sf::Texture>* squadTextures)
{
	squadTextureMap = squadTextures;
	spriteAnim = SpriteAnimator(squadSpriteSize, animStepTime, nrOfAnimSteps);
	//unitAssets = &assets->unitPackage;
}

std::vector<sf::Sprite> SquadDrawer::drawMapSquad(SquadRepresentation squadRep)
{
	unsigned int i;
	std::vector<sf::Sprite> retVal;
	sf::IntRect textureRect;

	if (squadRep.animated)
	{
		textureRect = spriteAnim.getTextureRectangle();
	}
	else
	{
		textureRect = spriteAnim.getFirstFrame();
	}

	for (i = 0; i < squadRep.backRowUnits.size(); i++)
	{
		UnitRepresentation unit = squadRep.backRowUnits.at(i);
		if (!unit.isDead)
		{
			sf::Sprite temp = sf::Sprite();
			temp.setTexture(squadTextureMap->find(unit.profession)->second);
			temp.setPosition(unit.position.x, unit.position.y);

			temp.setTextureRect(textureRect);
			retVal.push_back(temp);
		}
	}
	for (i = 0; i < squadRep.frontRowUnits.size(); i++)
	{
		UnitRepresentation unit = squadRep.frontRowUnits.at(i);
		if (!unit.isDead)
		{
			sf::Sprite temp = sf::Sprite();
			temp.setTexture(squadTextureMap->find(unit.profession)->second);
			temp.setPosition(unit.position.x, unit.position.y);

			temp.setTextureRect(textureRect);
			retVal.push_back(temp);
		}
	}
	return retVal;
}

void SquadDrawer::resetAnimationCycle()
{
	spriteAnim.resetAnimation();
}