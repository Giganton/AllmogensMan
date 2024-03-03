#include "MapCursorAnimation.h"

MapCursorAnimation::MapCursorAnimation(UTIL::ScreenCoord offset, UTIL::ScreenCoord spacing, sf::Texture* texture, CameraController* dBucket) : CursorAnimation(offset, spacing, texture)
{
	drawBucket = dBucket;
}

void MapCursorAnimation::moveCursor(CursorPos newPos)
{
	currentPos = newPos;
	UTIL::ScreenCoord mapPos = UTIL::mapCoordToScreenCoord(newPos.x, newPos.y);
	sprite.setPosition(mapPos.x + offsetX, mapPos.y + offsetY);
	//sprite.setPosition(UTIL::xCoordToScreen(newPos.x), UTIL::yCoordToScreen(newPos.y));
}


void MapCursorAnimation::moveCursor(CursorMove moveData) 
{ 
	moveCursor(moveData.end); 
};

void MapCursorAnimation::draw()
{
	if (active)
	{
		drawBucket->addToBucket(sprite);
	}
}