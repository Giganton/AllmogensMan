#include "MovementDotAnimation.h"
#include "GraphicsUtils.h"
#include "GraphicsAssets.h"
#include "CameraController.h"


MovementDotAnimation::MovementDotAnimation(MapPackage* mapPackage, CameraController* dBucket)
{
	dotTexture = &mapPackage->dotTexture;
	xTexture = &mapPackage->xTexture;

	dotSprite.setTexture(*dotTexture);
	xSprite.setTexture(*xTexture);

	drawBucket = dBucket;
}

void MovementDotAnimation::draw()
{
	drawDots();
	drawCross();
}


void MovementDotAnimation::drawCross()
{
	if (crossVisible)
	{
		float xOffsetX = float(-xSprite.getTextureRect().width / 2);
		float xOffsetY = float(-xSprite.getTextureRect().height / 2);
		float tileOffsetX = TILE_W / 2;
		float tileOffsetY = TILE_H / 2;

		UTIL::ScreenCoord mapPos = UTIL::mapCoordToScreenCoord(crossPos.getX(), crossPos.getY());
		float xPos = mapPos.x + tileOffsetX + xOffsetX;
		float yPos = mapPos.y + tileOffsetY + xOffsetY;
		xSprite.setPosition(xPos, yPos);
		//window->draw(xSprite);
		drawBucket->addToBucket(xSprite);
		//drawOnMap(xSprite);
	}
}

void MovementDotAnimation::drawDots()
{
	unsigned int i;
	int j;
	float tileOffsetX = TILE_W / 2;
	float tileOffsetY = TILE_H / 2;
	float dotOffsetX = float(-dotSprite.getTextureRect().width / 2);
	float dotOffsetY = float(-dotSprite.getTextureRect().height / 2);

	int dotsPerTile = 3;
	int dotRandMax = 3;

	float startX, startY, endX, endY;

	if (dotPath.size() > 1)
	{
		for (i = 0; i < dotPath.size() - 1; i++)
		{
			MapCoord start = dotPath.at(i);
			MapCoord stop = dotPath.at(i + 1);
			srand(start.getX() + start.getY());


			UTIL::ScreenCoord startPos = UTIL::mapCoordToScreenCoord(start.getX(), start.getY());
			startX = startPos.x + tileOffsetX;
			startY = startPos.y + tileOffsetY;
			UTIL::ScreenCoord endPos = UTIL::mapCoordToScreenCoord(stop.getX(), stop.getY());
			endX = endPos.x + tileOffsetX;
			endY = endPos.y + tileOffsetY;

			float distX = endX - startX;
			float distY = endY - startY;

			for (j = 0; j < dotsPerTile; j++)
			{
				float posX = startX;
				float posY = startY;

				if (abs(distX) > 0)
				{
					posX = startX + distX * j / dotsPerTile;
				}
				if (abs(distY) > 0)
				{
					posY = startY + distY * j / dotsPerTile;
				}

				posX = posX + (rand() % dotRandMax) + dotOffsetX;
				posY = posY + (rand() % dotRandMax) + dotOffsetY;

				dotSprite.setPosition(posX, posY);
				drawBucket->addToBucket(dotSprite);
			}
		}
	}
	srand(time(0));
}

void MovementDotAnimation::startDotAnimation(std::vector<MapCoord> path)
{
	setDotPath(path);
}

void MovementDotAnimation::setDotPath(std::vector<MapCoord> path)
{
	dotPath = path;
}

void MovementDotAnimation::startMovementCrossAnimation(MapCoord coord)
{
	setMovementCross(coord);
}

void MovementDotAnimation::setMovementCross(MapCoord coord)
{
	crossVisible = true;
	crossPos = coord;
}

void MovementDotAnimation::startMovementCrossRemovalAnimation()
{
	crossVisible = false;
}

void MovementDotAnimation::eatOffTile()
{
	if (dotPath.size() > 1)
	{
		dotPath.erase(dotPath.begin());
	}
	else if (dotPath.size() == 1)
	{
		dotPath.erase(dotPath.begin());
		startMovementCrossRemovalAnimation();
	}
	else
	{
		throw new std::exception();
	}
}