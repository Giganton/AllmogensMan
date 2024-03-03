#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "FightResults.h"
#include "SpriteAnimation.h"
#include "TextDrawer.h"
#include "LifeBarAnimation.h"

class BattleAnimation;

class DamageNumberAnimation
{
private:
	BattleAnimation* currentBattle = nullptr;

	int damagedUnitID = -1;

	bool finished = false;
	bool initiated = false;
	bool nrVisible = false;

	sf::Vector2f startPos;
	sf::Vector2f textPos;

	bool blocked = false;
	int incomingDamage = -1;

	std::clock_t startTime = 0;
	std::clock_t lastTime = 0;

	TextDrawer textDrawer;
public:
	DamageNumberAnimation() {};
	DamageNumberAnimation(BattleAnimation* bAnim, int dmgedUnitID, int dmg, GraphicsAssets* assets);
	DamageNumberAnimation(BattleAnimation* bAnim, int dmgedUnitID, GraphicsAssets* assets);

	void start();
	void progress();
	void draw(sf::RenderWindow* window);

	bool isFinished() { return finished; };
};

/*class EffectAnimation
{
private:
	FightEffect effectToDraw;
	SpriteAnimation currentSprite;
	DamageNumberAnimation damageNumberAnim;
	LifeBarAnimation lifeBarAnim;

	bool deathAnimStarted = false;
	bool finished = false;
	bool started = false;

	std::clock_t startTime = 0;
	std::clock_t startTime_dmgNr = 0;

	//void lifeBarStart();
	//void lifeBarProgress();
public:
	EffectAnimation() {};
	EffectAnimation(FightEffect effect, BattleAnimation* bAnim, GraphicsAssets* assets);

	void draw(sf::RenderWindow* window);
	void start();
	void progress();
	bool isFinished() { return finished; }
};*/