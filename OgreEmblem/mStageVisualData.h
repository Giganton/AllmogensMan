#pragma once
#include "MapCoord.h"
#include<vector>

class mStageVisualData
{
private:
	std::vector<MapCoord> movementList = {};
	long int squadID = -2;
	bool moveIsDone = false;
	bool disconnected = false;

public:
	mStageVisualData() { };
	mStageVisualData(std::vector<MapCoord> mList, long int sqdId, bool mDone, bool dsc) { movementList = mList; moveIsDone = mDone; squadID = sqdId; disconnected = dsc; };

	std::vector<MapCoord> getMoveList() { return movementList; };
	void setMoveDone() { moveIsDone = true; };
	bool isMoveDone() { return moveIsDone; };
	long int getSquadID() { return squadID; };
	bool isDisconnected() { return disconnected; };
};