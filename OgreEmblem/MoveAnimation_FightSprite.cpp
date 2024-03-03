#pragma once
#include "MoveAnimation_FightSprite.h"
#include "GraphicsUtils.h"

MoveAnimation_FightSprite::MoveAnimation_FightSprite(sf::Sprite* spritePtr, int tagNumber, sf::Vector2f defenderPos, double movementDuration) : FightSpriteAnimation(spritePtr, tagNumber)
{
	targetPosition = defenderPos;
	moveDuration = movementDuration;
}

void MoveAnimation_FightSprite::setupStart()
{
	startPosition = animatedSprite->getPosition();
}

void MoveAnimation_FightSprite::progressInternal()
{
	double percentage;
	sf::Vector2f travelVec = targetPosition - startPosition;
	UTIL::ScreenCoord help;

	switch (step)
	{
	case 0:

		if (currentTime < moveDuration)
		{
			percentage = currentTime / moveDuration;
			help = UTIL::vector2ScreenCoord(travelVec)* percentage;
			animatedSprite->setPosition(startPosition + sf::Vector2f(help.x, help.y));
		}
		else
		{
			animatedSprite->setPosition(targetPosition);
			step = 1;
		}
		break;
	case 1:
		finished = true;
	}
}