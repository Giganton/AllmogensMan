#include "DeathAnimation.h"
#include "CameraController.h"

DeathAnimation::DeathAnimation(std::map < ProfessionTag, sf::Texture>* txtMap, CameraController* dBucket)
{
	animationClock.restart();
	unitTextureMap = txtMap;
	drawBucket = dBucket;
	spriteAnim = SpriteAnimator(UTIL::ScreenCoord(MAP_SPRITE_W, MAP_SPRITE_H), SPRITE_ANIM_STEP_TIME, SPRITE_ANIM_STEP_NR);
}

void DeathAnimation::addDeath(UnitRepresentation deadUnit)
{
	deadUnits.push_back(std::make_pair(deadUnit, -animationClock.getElapsedTime().asSeconds()));
}

void DeathAnimation::update()
{
	float timePassed = animationClock.getElapsedTime().asSeconds();
	unsigned int i;
	std::vector<unsigned int> deletedIndices;
	for (i = 0; i < deadUnits.size(); i++)
	{
		deadUnits.at(i).second = deadUnits.at(i).second + timePassed;
		if (deadUnits.at(i).second > fadeTime)
		{
			deletedIndices.push_back(i);
		}
	}
	for (i = deletedIndices.size(); i-- > 0;)
	{
		deadUnits.erase(deadUnits.begin() + deletedIndices.at(i));
	}
	animationClock.restart();
}

void DeathAnimation::draw()
{
	update();
	unsigned int i;
	for (i = 0; i < deadUnits.size(); i++)
	{
		sf::Sprite temp = sf::Sprite();
		UnitRepresentation unit = deadUnits.at(i).first;
		float time = deadUnits.at(i).second;
		if (time < fadeTime)
		{
			temp.setTexture(unitTextureMap->find(unit.profession)->second);
			temp.setPosition(unit.position.x, unit.position.y);
			temp.setTextureRect(spriteAnim.getFirstFrame());
			temp.setColor(sf::Color(255, 255, 255, (255 - (255 * time * 1/fadeTime))));
			drawBucket->addToBucket(temp);
		}
		else
		{
			throw new std::exception();
		}
	}
}

bool DeathAnimation::ongoingAnimation() 
{ 
	return deadUnits.size() > 0; 
};