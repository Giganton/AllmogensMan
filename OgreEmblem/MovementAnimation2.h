#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "MapCoord.h"
#include<vector>
#include "SquadRepresentation.h"

class MovementAnimation2
{
private:
	SquadRepresentation* squad = nullptr;
	
	std::vector<MapCoord> movementList = { };

	std::clock_t startTime = 0;
	unsigned int currIndex = -1;

	float tileWidth = -1;
	float tileHeight = -1;
	float moveSpeed = 150;

	float currentX = -1;
	float currentY = -1;

	bool animationFinished = false;

	float xCoordToScreen(int x) { return float(x * tileWidth); };
	float yCoordToScreen(int y) { return float(y * tileHeight); };
public:
	MovementAnimation2() {};
	MovementAnimation2(SquadRepresentation* sqd, std::vector<MapCoord> mList, float tWidth, float tHeight);
	bool progressAction();
	std::vector<MapCoord> getMovementList() { return movementList; };
	int getCurrentIndex() { return currIndex; };
	tagID getSquadTag() { return squad->tag; };
};