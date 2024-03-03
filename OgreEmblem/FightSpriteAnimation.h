#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

class FightSpriteAnimation
{
protected:
	sf::Sprite* animatedSprite = nullptr;
	double startTime = 0;
	double currentTime = -1;

	int tagNr = -1;

	int step = -1;
	bool started = false;
	bool finished = false;
	virtual void progressInternal() = 0;
	virtual void setupStart() {};
public:
	FightSpriteAnimation() {};
	FightSpriteAnimation(sf::Sprite* spritePointer, int tagNumber) { animatedSprite = spritePointer; tagNr = tagNumber; };

	virtual FightSpriteAnimation* clone() const = 0;
	virtual FightSpriteAnimation* allocateNew() const = 0;

	void progress();
	virtual void start();
	bool isFinished() { return finished; };

	int getTagNr() { return tagNr; };
};