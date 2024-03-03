#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include<vector>
#include "FightPos.h"
#include<ctime>

enum class enumSpriteAnimType { none , move , incomingDamage, unresolved, block};
class BattleAnimation;
class FightSpriteAnimation;

class FightSpriteAnimationContainer
{
private:
	std::vector<FightSpriteAnimation*> vector;
public:
	FightSpriteAnimationContainer() {};

	FightSpriteAnimationContainer(const FightSpriteAnimationContainer& cpEQ);
	FightSpriteAnimationContainer& operator=(const FightSpriteAnimationContainer asEQ);
	~FightSpriteAnimationContainer();

	void push_back(FightSpriteAnimation* newAnim) { vector.push_back(newAnim); };
	FightSpriteAnimation* at(unsigned int i) { return vector.at(i); };
	FightSpriteAnimation* at(int i) { return vector.at(i); };
	unsigned int size() { return vector.size(); };
	void erase(unsigned int i) { delete vector.at(i); vector.erase(vector.begin() + i); };
};

class SpriteAnimation
{
private:
	int step = -1;
	float memory = -1;
	bool trigger1 = false;
	std::clock_t startTime = 0;

	bool animationFinished = true;

	std::vector<enumSpriteAnimType> queue;
	FightSpriteAnimationContainer spriteAnimations;
	std::vector<int> doneTags;

	enumSpriteAnimType currentAnim = enumSpriteAnimType::none;
	//FightPos spritePosition;
	sf::Vector2f targetPosition = sf::Vector2f(-1, -1);
	int spriteID = -1;
	bool attackingSide = false;
	BattleAnimation* currentBattle = nullptr;

	bool fading = false;
	int fadeSpeed = -1;

	void progressMove();
	void progressBlock();
	void progressDamage();
	void pickNextInLine();
	void cleanUp();
public:
	SpriteAnimation() {};
	SpriteAnimation(BattleAnimation* bAnim, int sprtID, bool attacking) { currentBattle = bAnim; spriteID = sprtID; startTime = std::clock(); attackingSide = attacking; };

	void progress();
	void addToQueue(enumSpriteAnimType movementType) { queue.push_back(movementType); };
	bool hasTriggered1() { return trigger1; };
	bool isFinished();
	bool isTagFinished(int tagNr);

	void startFadeAnimation(int tagNr, double fadeTime, bool fadingOut);
	void startMovementAnimation(int tagNr, sf::Vector2f defenderPos, double moveDuration);
	void startRelativeMovementAnimation(int tagNr, sf::Vector2f moveVector, double moveDuration);

	sf::Vector2f getSpritePos();

	void setSpritePos(sf::Vector2f newPos);
	void moveToFightPos(FightPos pos);
};