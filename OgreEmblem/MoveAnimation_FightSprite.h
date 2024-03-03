#pragma once
#include "FightSpriteAnimation.h"

class MoveAnimation_FightSprite : public FightSpriteAnimation
{
private:
	sf::Vector2f targetPosition;
	sf::Vector2f startPosition;
	double moveDuration = -1;

	void setupStart() override;
	void progressInternal() override;
public:
	MoveAnimation_FightSprite() {};
	MoveAnimation_FightSprite(sf::Sprite* spritePtr, int tagNumber, sf::Vector2f defenderPos, double movementDuration);

	FightSpriteAnimation* clone() const override { return new MoveAnimation_FightSprite(*this); };
	FightSpriteAnimation* allocateNew() const override { return new MoveAnimation_FightSprite(); };
};