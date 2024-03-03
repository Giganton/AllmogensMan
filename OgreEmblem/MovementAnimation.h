#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "MapCoord.h"
#include<vector>
#include "SquadRepresentation.h"
#include "GraphicsUtils.h"
#include "SpriteAnimator.h"

class CameraController;

class CaravanUnit
{
public:
	CaravanUnit() {};
	CaravanUnit(UnitRepresentation unit, MapCoord startCoord, UTIL::ScreenCoord trget, float timeToWait);

	UnitRepresentation unit;
	UTIL::ScreenCoord startingOffset;
	UTIL::ScreenCoord target;
	float timer = -1;
	int currentIndex = 0;
	bool moveDone = false;
};

class MovementAnimation
{
private:
	std::map < ProfessionTag, sf::Texture>* squadTextureMap = nullptr;

	std::vector<MapCoord> movementList = { };
	SquadRepresentation movingSquad;
	CameraController* drawBucket = nullptr;
	bool active = false;

	std::clock_t startTime = 0;
	unsigned int currIndex = -1;

	SpriteAnimator spriteAnim;
	UTIL::ScreenCoord squadSpriteSize = UTIL::ScreenCoord(40, 47);
	float spriteAnimStepTime = 0.5f;
	int nrOfSpriteAnimSteps = 2;

	std::vector<CaravanUnit> caravan;

	sf::Clock animationClock;
	bool initialized = false;

	float tileWidth = -1;
	float tileHeight = -1;
	float moveSpeed = 150;
	UTIL::ScreenCoord unitSpriteSize;

	//float currentX = -1;
	//float currentY = -1;

	UTIL::ScreenCoord currentPos;

	bool animationFinished = false;

	void initializeMovement();
	void drawCaravan();
	void updateSquadRepPos(std::vector<CaravanUnit> crvn);
	UTIL::ScreenCoord getEdgeBetweenCoords(MapCoord pos1, MapCoord pos2);
public:
	MovementAnimation() {};
	MovementAnimation(std::map < ProfessionTag, sf::Texture>* sqdTextureMap, SquadRepresentation mvSquad, std::vector<MapCoord> mList, float tWidth, float tHeight, CameraController* dBucket);
	bool progressAction();
	bool runAnimation2();
	std::vector<MapCoord> getMovementList() { return movementList; };
	int getCurrentIndex() { return currIndex; };

	bool isAnimationFinished() { return animationFinished; };
	bool isActive() { return active; };
	SquadRepresentation getSquadRep() { return movingSquad; };
	void draw();
	MapCoord getDestination() { return movementList.at(movementList.size() - 1); };
};