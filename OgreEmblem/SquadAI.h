#pragma once
#include<vector>
#include<list>
#include "FightResults.h"
#include "AnimationQueue.h"
#include "MovementStage.h"
#include "BattleStage.h"
#include "BattleField.h"
#include "GraphicalEvent.h"

class Squad;
class BattleMap;
class MapCoord;
class Node;
class MapManagerVisualEventData;

class StagePair
{
public:
	StagePair() {};
	StagePair(MovementStage mStage, BattleStage bStage) { movementStage = mStage; battleStage = bStage; };
	MovementStage movementStage;
	BattleStage battleStage;

	bool moved = false;
	bool attacked = false;
};

class SquadAI
{
private:
	//BattleMap* bMap = nullptr;
	BattleField* bField = nullptr;
	//std::vector<std::list<FightResults>> battleResults;
	//std::vector<mStageVisualData> moveResults;


	MovePath aStar(MapCoord start, MapCoord objective, std::vector<MapCoord> goalTiles, Squad squad);
	MovePath constructPath(Node goalNode, std::vector<Node> nodeList);
	int calculateH(MapCoord mapPos, MapCoord goal, Squad sqd);
	std::vector<MapCoord> standableTilesInRange(MapCoord mapPos, Squad sqd);
	MapCoord closestCoordInList(MapCoord sqdCoord, std::vector<MapCoord> coordList);
	int findLowestF(std::vector<int> subset, std::vector<Node> nodeList); //find lowest F among subset of nodes in nodeList
	int isNodeInSubset(Node node, std::vector<int> subset, std::vector<Node> nodeList);
	std::vector<MapCoord> getSurroundingCoords(MapCoord coord);
	int findAttackTarget(MapCoord sqdPos, Squad attacker, BattleField bf);
	bool isAttackTargetViable(Squad atker, Squad defer);
	MapCoord findClosestLandableTileWithinRange(Squad squad, MapCoord start, int range, MapCoord goal);
	//Squad* siftThroughSquads(Squad* self, std::vector<Squad*> sortedList);
	StructuredEventQueue handleBattleEvents(BattleVisualData vData);

public:
	SquadAI() {};
	SquadAI(BattleField* battleField) { bField = battleField; };
	StructuredEventQueue controlSquad(int squadID);
	void setBattleFieldPointer(BattleField* battleField) { bField = battleField; };
	std::vector<MapCoord> findPath(Squad sqd);
};