#pragma once
#include<vector>
#include "Squad.h"
#include "tagID.h"
#include "IdCreator.h"
#include "BattleMap.h"

class Flag
{
private:
	tagID tag = tagID::noID;
	std::vector<Squad> squads = {};
	std::vector<Unit> bench = {};
	IdCreator* idCreator = nullptr;
public:
	Flag() {};
	Flag(tagID tagNr, IdCreator* idCrtor) { tag = tagNr; idCreator = idCrtor; };


	tagID getTag() { return tag; };

	void addUnit(Unit unit) { bench.push_back(unit); };
	void addUnits(std::vector<Unit> units);
	std::vector<Unit> getBench() { return bench; };
	Unit getUnit(int id);
	Unit* getUnitPtr(int id);
	void removeUnit(int id);

	void addSquad(Squad sqd);
	void addSquadOverwrite(Squad sqd);
	void addSquads(std::vector<Squad> squads);
	void addSquadsOverwrite(std::vector<Squad> squads);
	void removeSquad(int squadID);
	void disbandSquad(int squadID);
	void emptySquad(int squadID);
	//void formNewSquad(std::vector<std::pair<bool, int>> frontRow, std::vector<std::pair<bool, int>> backRow, int leaderID);
	void fillSquad(int squadID, std::vector<std::pair<bool, int>> frontRow, std::vector<std::pair<bool, int>> backRow, int leaderID);
	std::vector<Squad> getSquads() { return squads; };
	Squad getSquad(int ID);
	Squad* getSquadPointer(int ID);
	std::vector<Squad*> getSquadPointers();
};