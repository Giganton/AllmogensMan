#include "CameraPanner.h"

CameraPanner::CameraPanner(sf::RenderWindow* window, float tile_w, float tile_h)
{
	windowHeight = window->getSize().y;
	windowWidth = window->getSize().x;

	buffertSizeX = 2 * tile_w;
	buffertSizeY = 2 * tile_h;
	shiftSizeX = tile_w;
	shiftSizeY = tile_h;
	panStep = UTIL::ScreenCoord(buffertSizeX, buffertSizeY).abs()*1.5;
}

UTIL::ScreenCoord CameraPanner::panCamera(float pixelCoordX, float pixelCoordY)
{
	UTIL::ScreenCoord coord = UTIL::ScreenCoord(pixelCoordX, pixelCoordY);
	UTIL::ScreenCoord closestPoint = findClosestBoundedCoord(coord);
	UTIL::ScreenCoord fullDistance = closestPoint - coord;
	if (fullDistance.abs() != 0)
	{
		UTIL::ScreenCoord direction = fullDistance / fullDistance.abs();
		UTIL::ScreenCoord newPoint = fullDistance + direction*300;
		return moveCamera(newPoint);
	}
	else
	{
		return UTIL::ScreenCoord(offsetX, offsetY);
	}
}

UTIL::ScreenCoord CameraPanner::panCamera(PanDirection dir)
{
	float panLength = 500;
	UTIL::ScreenCoord northVec = UTIL::ScreenCoord(0.906307787036650, 0.422618261740699);
	UTIL::ScreenCoord eastVec = UTIL::ScreenCoord(-0.906307787036650, 0.422618261740699);
	UTIL::ScreenCoord southVec = UTIL::ScreenCoord(-0.906307787036650, -0.422618261740699);
	UTIL::ScreenCoord westVec = UTIL::ScreenCoord(0.906307787036650, -0.422618261740699);
	switch (dir)
	{
	case PanDirection::north:
		return moveCamera(northVec * panLength);
		break;
	case PanDirection::east:
		return moveCamera(eastVec * panLength);
		break;
	case PanDirection::south:
		return moveCamera(southVec * panLength);
		break;
	case PanDirection::west:
		return moveCamera(westVec * panLength);
		break;
	}
	throw new std::exception();
	return northVec;
}

UTIL::ScreenCoord CameraPanner::moveCamera(UTIL::ScreenCoord moveVector)
{
	UTIL::ScreenCoord retVal = UTIL::ScreenCoord(offsetX + moveVector.x, offsetY + moveVector.y);
	offsetX = retVal.x;
	offsetY = retVal.y;
	return retVal;
}

UTIL::ScreenCoord CameraPanner::findClosestBoundedCoord(UTIL::ScreenCoord coord)
{
	bool retVal = true;
	UTIL::ScreenCoord closestCoord;
	if (coord.x < -offsetX + buffertSizeX - TILE_W)
	{
		closestCoord.x = -offsetX + buffertSizeX - TILE_W;
	}
	else if (coord.x>= windowWidth - offsetX - buffertSizeX)
	{
		closestCoord.x = windowWidth - offsetX - buffertSizeX;
	}
	else
	{
		closestCoord.x = coord.x;
	}
	if (coord.y < -offsetY + buffertSizeY - TILE_H)
	{
		closestCoord.y = -offsetY + buffertSizeY - TILE_H;
	}
	else if (coord.y >= windowHeight - offsetY - buffertSizeY)
	{
		closestCoord.y = windowHeight - offsetY - buffertSizeY;
	}
	else
	{
		closestCoord.y = coord.y;
	}
	return closestCoord;
}

bool CameraPanner::coordIsWithinBounds(UTIL::ScreenCoord coord)
{
	bool retVal = true;
	if (coord.x - buffertSizeX < -offsetX - TILE_W)
	{
		retVal = false;
	}
	else if (coord.x + buffertSizeX >= windowWidth - offsetX)
	{
		retVal = false;
	}
	else if (coord.y - buffertSizeY < -offsetY - TILE_H)
	{
		retVal = false;
	}
	else if (coord.y + buffertSizeY >= windowHeight - offsetY)
	{
		retVal = false;
	}
	return retVal;
}

UTIL::ScreenCoord CameraPanner::centerCamera(sf::Sprite centerSprite, UTIL::ScreenCoord coord)
{
	offsetX = -coord.x + windowWidth / 2 + centerSprite.getTextureRect().width / 2;
	offsetY = -coord.y + windowHeight / 2 + centerSprite.getTextureRect().height / 2;

	return UTIL::ScreenCoord(offsetX, offsetY);
}

UTIL::ScreenCoord CameraPanner::centerCamera(MapCoord coord)
{
	UTIL::ScreenCoord screenCoord = UTIL::mapCoordToScreenCoord(coord.getX(), coord.getY());
	offsetX = -screenCoord.x + windowWidth / 2 - TILE_W / 2;
	offsetY = -screenCoord.y + windowHeight / 2 - TILE_H / 2;

	return UTIL::ScreenCoord(offsetX, offsetY);
}

void CameraPanner::centerCameraIfOut(sf::Sprite centerSprite, UTIL::ScreenCoord coord)
{
	float xPos = coord.x;
	float yPos = coord.y;
	if ((xPos - buffertSizeX < -offsetX) ||
		(xPos + buffertSizeX >= windowWidth - offsetX) ||
		(yPos - buffertSizeY < -offsetY) ||
		(yPos + buffertSizeY >= windowHeight - offsetY))
	{
		centerCamera(centerSprite, coord);
	}
}