#pragma once
#include "FightPos.h"
#include<map>

class Squad;
class Unit;


class FightSlot
{
private:
	//FightPos position;
	int occupantID = -1;
	bool empty = true;
public:
	FightSlot() {};
	FightSlot(int occupyingUnitID);

	int getOccupantID();
	bool isEmpty() { return empty; };
	void removeOccupant();
	void setOccupantID(int newOccupantID);

	bool operator<(const FightSlot& rhs) const { return false; };
	bool operator>(const FightSlot& rhs) const { return true; };
};

class FightScene
{
private:
	Squad* atkSquad = nullptr;
	Squad* defSquad = nullptr;

	std::map<FightPos, FightSlot> slotMap;

	std::vector<int> exiledZone;
public:
	FightScene() {};
	FightScene(Squad* attackers, Squad* defenders);

	void moveUnit(FightPos startPos, FightPos endPos);
	void addUnit(FightPos pos, int unitID);
	void removeUnit(FightPos pos);
	void exileUnitOnPos(FightPos exiledPos);
	void returnFromExile(int unitID, FightPos pos);

	std::vector<FightPos> getAllLivingUnitPositions();
	std::vector<FightPos> getAllLivingUnitPositions(bool atkSide);

	bool isPosOccupied(FightPos pos);
	Unit* getUnitOnPos(FightPos pos);
	FightPos FindUnitPosition(int id);
	Unit* getUnitWithID(int id);
	int getUnitID_unsafe(FightPos pos);
	bool isUnitInExile(int id);
};