#include "MovementAnimation2.h"

MovementAnimation2::MovementAnimation2(SquadRepresentation* sqd, std::vector<MapCoord> mList, float tWidth, float tHeight)
{
	squad = sqd;
	movementList = mList;

	tileWidth = tWidth;
	tileHeight = tHeight;

	currIndex = 0;
	currentX = xCoordToScreen(movementList.at(0).getX());
	currentY = yCoordToScreen(movementList.at(0).getY());
}

bool MovementAnimation2::progressAction()
{
	if (startTime == 0)
	{
		startTime = std::clock();
		animationFinished = false;
	}
	else
	{
		MapCoord destination = movementList.at(currIndex + 1);

		float destX = xCoordToScreen(destination.getX());
		float destY = yCoordToScreen(destination.getY());

		float distX = destX - currentX;
		float distY = destY - currentY;
		float movedDist;

		std::clock_t startTime = std::clock();
		double timePassed = ((double)startTime - (double)startTime) / (double)CLOCKS_PER_SEC;
		startTime = startTime;

		bool tileDone = true;
		if (abs(distX) > 0)
		{
			movedDist = moveSpeed * (float)timePassed * distX / abs(distX);
			if (abs(distX) > abs(movedDist))
			{
				currentX = currentX + movedDist;
				tileDone = false;
			}
			else
			{
				currentX = destX;
				tileDone = true;
			}
		}
		if (abs(distY) > 0)
		{
			movedDist = moveSpeed * (float)timePassed * distY / abs(distY);
			if (abs(distY) > abs(movedDist))
			{
				currentY = currentY + movedDist;
				tileDone = false;
			}
			else
			{
				currentY = destY;
				tileDone = true;
			}
		}

		if (tileDone)
		{
			currIndex = currIndex + 1;
			if (currIndex >= movementList.size() - 1)
			{
				animationFinished = true;
				startTime = 0;
			}
		}
	}
	squad->frontRowUnits.at(0).position = UTIL::ScreenCoord(currentX, currentY);

	return animationFinished;
}