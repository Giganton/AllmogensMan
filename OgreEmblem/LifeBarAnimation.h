#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "FightPos.h"

class BattleAnimation;
class LifeBar;

class LifeBarAnimation
{
private:
	LifeBar* lifeBar = nullptr;

	int damageToDeal = -1;
	float startGreenLength = -1.0f;
	float goalGreenLength = -1.0f;
	int goalHP = -1;
	float speed = -1;

	bool finished = false;
	bool started = false;
	bool initiated = false;

	std::clock_t startTime = 0;
	std::clock_t lastTime = 0;
public:
	LifeBarAnimation() {};
	LifeBarAnimation(BattleAnimation* bAnim, int unitID, int incomingDamage);

	void start();
	void progress();
	void draw(sf::RenderWindow* window);

	bool isFinished() { return finished; };
};