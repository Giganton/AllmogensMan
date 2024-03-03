#pragma once
#include "MapCoord.h"
#include<vector>
#include "MapTile.h"
#include "GraphicalEvent.h"

class BattleMap;
class Squad;
class mStageVisualData;

class MovePath
{
private:
	std::vector<MapCoord> path;
	std::vector<int> cost;
public:
	MovePath() {};
	MovePath(std::vector<MapCoord> coordPath, std::vector<int> moveCost);
	
	int getTotalCost();
	std::vector<MapCoord> getPath() { return path; };
	std::vector<int> getCostVector() { return cost; };
	std::vector<int> getStepCosts() { return cost; };
	int stepsFromMoveRange(int range);
	MovePath walkPath(int range);
};

struct MoveData
{
	MoveData() {};
	MoveData(int ID, std::vector<MapCoord> pth) { movedSquadID = ID; path = pth; };
	int movedSquadID = -1;
	std::vector<MapCoord> path;
};

class MovementStage
{
private:
	StructuredEventQueue eventQueue;
	std::vector<MapCoord> movementList = { };
	std::vector<bool> standableList = { };
	std::vector<int> costList = { };
	int moveCostTot = 0;

	Squad movingSquad;
	int moveRange = -1;
	//bool moveDone = false;
	//BattleMap* bMap = nullptr;
	bool disconnected = false;

	void sumCost();

public:
	MovementStage() {};
	MovementStage(Squad mvSquad, MapCoord startPos);// , BattleMap* map);
	MovementStage(Squad mvSquad, MapCoord startPos, std::vector<MapCoord> mvPath);//, BattleMap* map);
	void tryCoord(MapCoord coord, bool coordPassable, bool coordStandable, int cost);
	void addCoord(MapCoord coord, bool standable, int cost);
	void backOneStep();
	//void performMove();
	bool isDisconnected() { return disconnected; };
	bool pathAtLimit();

	MapCoord getLastStep();

	mStageVisualData getVisuals();
	std::vector<MapCoord> getPath() { return movementList; };
	StructuredEventQueue pullEvents() { StructuredEventQueue temp = eventQueue; eventQueue.emptyQueue(); return temp; };
	bool isExecutable();
	//bool isMoveDone() { return moveDone; };

	MoveData getMoveData() { return MoveData(movingSquad.getID(), movementList); };
};