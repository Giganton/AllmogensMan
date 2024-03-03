#pragma once
#include "BattleMap.h"
#include "MovementStage.h"
#include "LevelUpData.h"
#include "Battle.h"

class BattleVisualData;

class BattleField
{
private:
	BattleMap bMap;
	std::map<MapCoord, int> squadIDByCoords;
	std::map<int, MapCoord> coordsBySquadID;
	std::map<int, Squad> squads;
	std::map<int, Squad> deadSquads;


	std::vector<int> sortIndices(std::vector<int> vector);
public:
	BattleField() {};
	BattleField(BattleMap map, std::vector<Squad> squadList);
	BattleField(Battle battle, std::vector<Squad> playerSquads);

	void addSquadToMap(Squad sqd, MapCoord coord);
	void removeSquadFromMap(Squad sqd);
	MoveData moveSquad(MoveData mData);
	void moveSquadToCoord(int sqdID, MapCoord coord);
	void killSquad(Squad sqd);
	bool isSquadDead(int sqdID);

	bool isCoordOccupied(MapCoord coord);
	bool isSquadOnField(Squad sqd);
	bool isSquadOnField(int sqdID);

	bool anyFlagSquadsLeft(tagID tag);

	std::vector<Squad> getAllLivingFlagSquads(tagID tag);
	std::vector<Squad> getAllDeadFlagSquads(tagID tag);

	MapCoord findSquadPos(Squad sqd);
	MapCoord findSquadPos(int sqdID);
	Squad findSquadAtPos(MapCoord coord);
	bool canIStandHere(MapCoord coord, Squad sqd);
	bool canIPassHere(MapCoord coord, Squad sqd);
	Squad* getSquadPtrByID(int sqdID) { return &squads.find(sqdID)->second; };
	Squad getSquadByID(int sqdID) { return *getSquadPtrByID(sqdID); };

	MapCoord getMapCoord(Cursor cursor) { return MapCoord(cursor.getX(), cursor.getY()); };

	Squad findClosestSquad(Squad squad);
	std::vector<Squad> getSquadsByProximity(MapCoord mapPos);
	std::vector<Squad> allSquadsInRange(int x, int y, int range);
	bool isAnySquadInRange(int x, int y, int range);
	bool isAnyLivingSquadInRange(int x, int y, int range);
	bool isAnyLivingEnemyInRange(int x, int y, int range, tagID tag);
	std::vector<Squad> allLivingEnemiesInRange(int x, int y, int range, tagID tag);

	std::pair<BattleVisualData, std::vector<LevelUpData>> doBattle(int attackerID, int defenderID);

	bool doesHoveredExist(Cursor cursor);
	Squad getHoveredSquad(Cursor cursor);
	bool isHoveredEmpty(Cursor cursor);

	std::vector<SquadData> getSquadData();

	int getMovementCost(MapCoord start, MapCoord dest, Squad sqd);
	std::vector<MapCoord> getStartingPos(tagID tag) { return bMap.getStartingPositions(tag); };
	BattleMap getBattleMap() { return bMap; };
};