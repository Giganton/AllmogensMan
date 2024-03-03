#include "SpriteAnimation.h"
#include <ctime>
#include "BattleAnimation.h"

#include "FadeAnimation_FightSprite.h"
#include "MoveAnimation_FightSprite.h"

FightSpriteAnimationContainer::FightSpriteAnimationContainer(const FightSpriteAnimationContainer& cpEQ)
{
	unsigned int i;
	for (i = 0; i < cpEQ.vector.size(); i++)
	{
		vector.push_back((cpEQ.vector.at(i))->clone());
	}
}
FightSpriteAnimationContainer& FightSpriteAnimationContainer::operator=(const FightSpriteAnimationContainer cpEQ)
{
	unsigned int i;
	for (i = 0; i < cpEQ.vector.size(); i++)
	{
		vector.push_back((cpEQ.vector.at(i))->clone());
	}

	return *this;
}
FightSpriteAnimationContainer::~FightSpriteAnimationContainer()
{
	unsigned int i;
	for (i = 0; i < vector.size(); i++)
	{
		delete(vector.at(i));
	}

}

bool SpriteAnimation::isTagFinished(int tagNr)
{
	unsigned int i;
	for (i = 0; i < doneTags.size(); i++)
	{
		if (doneTags.at(i) == tagNr)
		{
			return true;
		}
	}
	return false;
}

bool SpriteAnimation::isFinished()
{ 
	unsigned int i;
	for (i = 0; i < spriteAnimations.size(); i++)
	{
		if (spriteAnimations.at(i)->isFinished())
		{
			doneTags.push_back(spriteAnimations.at(i)->getTagNr());
			spriteAnimations.erase(i);
		}
		else
		{
			return false;
		}
	}
	return animationFinished; 
}

void SpriteAnimation::startFadeAnimation(int tagNr, double fadeTime, bool fadingOut)
{
	spriteAnimations.push_back(new FadeAnimation_FightSprite(currentBattle->getSpritePtr(spriteID), tagNr, fadingOut, fadeTime));
	spriteAnimations.at(spriteAnimations.size() - 1)->start();
}

void SpriteAnimation::startMovementAnimation(int tagNr, sf::Vector2f defenderPos, double moveDuration)
{
	spriteAnimations.push_back(new MoveAnimation_FightSprite(currentBattle->getSpritePtr(spriteID), tagNr, defenderPos, moveDuration));
	spriteAnimations.at(spriteAnimations.size() - 1)->start();
}

void SpriteAnimation::startRelativeMovementAnimation(int tagNr, sf::Vector2f moveVector, double moveDuration)
{
	sf::Vector2f pos = currentBattle->getSpritePtr(spriteID)->getPosition() + moveVector;
	startMovementAnimation(tagNr, pos, moveDuration);
}

sf::Vector2f SpriteAnimation::getSpritePos()
{
	sf::Sprite* sprite = currentBattle->getSpritePtr(spriteID);
	return sprite->getPosition();
}

void SpriteAnimation::setSpritePos(sf::Vector2f newPos)
{
	sf::Sprite* sprite = currentBattle->getSpritePtr(spriteID);
	sprite->setPosition(newPos);
}

void SpriteAnimation::moveToFightPos(FightPos pos)
{
	setSpritePos(currentBattle->getPosCoord(pos));
}

void SpriteAnimation::progress()
{
	unsigned int i;
	for (i = 0; i < spriteAnimations.size(); i++)
	{
		spriteAnimations.at(i)->progress();
		if (spriteAnimations.at(i)->isFinished())
		{
			doneTags.push_back(spriteAnimations.at(i)->getTagNr());
			spriteAnimations.erase(i);
		}
	}

	if (!animationFinished)
	{
		switch (currentAnim)
		{
		case enumSpriteAnimType::move:
			progressMove();
			break;
		case enumSpriteAnimType::incomingDamage:
			progressDamage();
			break;
		case enumSpriteAnimType::block:
			progressBlock();
			break;
		default:
			throw new std::exception();
		}
	}
	else
	{
		pickNextInLine();
	}
}

void SpriteAnimation::pickNextInLine()
{
	cleanUp();

	if (queue.size() > 0)
	{
		step = 0;
		currentAnim = queue.at(0);
		queue.erase(queue.begin());
		animationFinished = false;
	}
}

void SpriteAnimation::cleanUp()
{
	animationFinished = true;
	step = -1;
	memory = -1;
	trigger1 = false;
	startTime = std::clock();
}

void SpriteAnimation::progressMove()
{
	float moveStep;
	double time = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
	sf::Sprite* movingSprite = currentBattle->getSpritePtr(spriteID);
	int multip = 1;
	switch (step)
	{
	case 0:
		step = 1;
		trigger1 = false;
		memory = 0;
		break;
	case 1:
		if (attackingSide)
		{
			multip = 1;
		}
		else
		{
			multip = -1;
		}
		moveStep = (float)time * 150 * multip;
		memory = memory + moveStep;
		if (abs(memory) >= 25)
		{
			moveStep = moveStep - (memory - (25*multip));
			memory = 0;
			step = 2;
		}
		movingSprite->move(moveStep, 0);
		break;
	case 2:
		if (!trigger1)
		{
			trigger1 = true;
		}
		if (attackingSide)
		{
			multip = 1;
		}
		else
		{
			multip = -1;
		}
		moveStep = (float)time * 150 * multip;
		memory = memory + moveStep;

		if (abs(memory) >= 25)
		{
			moveStep = moveStep - (memory - (25*multip));
			memory = 0;
			step = 3;
		}
		movingSprite->move(-moveStep, 0);
		break;
	case 3:
		animationFinished = true;
		break;
	}
	startTime = std::clock();
}

void SpriteAnimation::progressBlock()
{
	float moveStep;
	double time = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
	sf::Sprite* movingSprite = currentBattle->getSpritePtr(spriteID);

	sf::Vector2f targetVector;
	sf::Vector2f newPosition;
	UTIL::ScreenCoord tempCoord;

	switch (step)
	{
	case 0:
		targetPosition = movingSprite->getPosition();
		step = 1;
		trigger1 = false;
		memory = 0;
	case 1: //framåt
		moveStep = (float)time * 150;
		memory = memory + moveStep;
		if (memory >= 10)
		{
			moveStep = moveStep - (memory - 10);
			memory = 0;
			step = 2;
		}
		movingSprite->move(-moveStep, 0);
		break;
	case 2: //neråt
		moveStep = (float)time * 150;
		memory = memory + moveStep;
		if (memory >= 6)
		{
			moveStep = moveStep - (memory - 6);
			memory = 0;
			step = 3;
		}
		movingSprite->move(0, moveStep);
		break;
	case 3: //snett bakåt
		targetVector = targetPosition - movingSprite->getPosition();
		moveStep = (float)time * 150;
		tempCoord = UTIL::vector2ScreenCoord(targetVector);

		if (tempCoord.abs() > moveStep)
		{
			tempCoord = tempCoord / tempCoord.abs();
			tempCoord = tempCoord * (150 * (float)time);
			newPosition = movingSprite->getPosition() + sf::Vector2f(tempCoord.x, tempCoord.y);
			movingSprite->setPosition(newPosition);
		}
		else
		{
			movingSprite->setPosition(targetPosition);
			memory = 0;
			step = 4;
		}
		break;
	case 4: //snett bakåt
		animationFinished = true;
		break;
	}
	startTime = std::clock();
}

void SpriteAnimation::progressDamage()
{
	float moveStep;
	double time = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
	sf::Sprite* movingSprite = currentBattle->getSpritePtr(spriteID);
	
	switch (step)
	{
	case 0:
		step = 1;
		trigger1 = false;
		memory = 0;
		break;
	case 1:
		moveStep = (float)time * 250;
		memory = memory + moveStep;

		if (memory >= 8)
		{
			moveStep = moveStep - (memory - 8);
			memory = 0;
			if (!trigger1)
			{
				step = 2;
				trigger1 = true;
			}
			else
			{
				step = 3;
			}
		}
		
		currentBattle->getSpritePtr(spriteID)->move(0, moveStep);
		

		break;
	case 2:
		moveStep = (float)time * 250;
		memory = memory + moveStep;
		if (memory >= 16)
		{
			moveStep = moveStep - (memory - 16);
			memory = 0;
			step = 1;
		}
		currentBattle->getSpritePtr(spriteID)->move(0, -moveStep);
		
		break;
	case 3:
		animationFinished = true;
		break;
	}
	startTime = std::clock();
}