#pragma once

#include "Unit.h"
#include<vector>
#include "tagID.h"
#include "Browsable.h"
#include "LevelUpData.h"
#include "Fight.h"
#include "SquadPos.h"

#define TACTICAL_X 2
#define TACTICAL_Y 3

class StringHandler;

class UnitInSquadData
{
public:
	UnitInSquadData(UnitData un, SquadPos po) { unit = un; mapPos = po; };
	UnitData unit;
	SquadPos mapPos;
};

class TacticalTile
{
private:
	int occupantID = -1;
	bool empty = true;
	int posX;
	int posY;

public:
	TacticalTile();
	TacticalTile(int x, int y);
	bool isEmpty() { return empty; };
	int getX() { return posX; };
	int getY() { return posY; };

	bool placeUnit(int addee);
	int getOccupantID();
	//Unit getUnit() { return *getUnitPtr(); };
	void removeUnit();
};
/*
class TacticalPiece
{
private:
	Unit combatant;
	UnitPos pos;
};
*/
class Squad : public Browsable
{
protected:
	//list<TacticalPiece> combatants;
	tagID flagTag = tagID::noID;
	TacticalTile tacticalGrid[TACTICAL_X][TACTICAL_Y];

	std::vector<Unit> unitList;
	Unit leader;
	bool leaderPresent = false; 
	int unitCapacity = 6;

	std::string squadName ="inget namn :(";

	//int leaderID = -1;
	bool empty = true;

	int moveRange = -1;
	int movesLeft = -1;
	int atkRange = 1;
	long int ID = -1;

public:
	Squad() {};
	Squad(long int id);
	Squad(long int id, Unit leaderUnit, StringHandler* strHandler);
	Squad(long int id, Unit leaderUnit, SquadPos pos, StringHandler* strHandler);


	TacticalTile* getGrid() { return &tacticalGrid[0][0]; };
	TacticalTile* getTile(int x, int y);
	TacticalTile* getTile(SquadPos mapPos);
	long int getID();
	void tag(tagID tagNr) { flagTag = tagNr; };
	tagID getFlagTag() { return flagTag; };

	std::string getName() { return squadName; };
	void setName(std::string newName) { squadName = newName; };

	std::string getLeaderName();

	std::vector<ProfessionTag> getFrontProfTags();
	std::vector<ProfessionTag> getBackProfTags();
	std::vector<int> getFrontIDs();
	std::vector<int> getBackIDs();

	SquadPos getPosFromIndex(int index);
	Unit* getUnitPtr(int x, int y);
	Unit* getUnitPtr(SquadPos mapPos) { return getUnitPtr(mapPos.getX(), mapPos.getY()); };
	std::vector<Unit> getAllUnits();
	std::vector<Unit*> getAllUnitPtrs();
	std::vector<Unit*> getAllLivingUnitPtrs();
	std::vector<UnitInSquadData> getUnitList();
	Unit findUnit(int id);
	Unit* findUnitPtr(int id);
	SquadPos whereIsThisUnit(int id);
	bool isThisUnitIn(int id);

	bool addUnit(Unit addee, int posX, int posY);
	bool addUnit(Unit addee, int posIndex);
	bool addUnit(Unit addee, SquadPos pos);
	Unit removeUnit(int x, int y);
	Unit removeUnit(SquadPos mapPos);
	Unit removeUnit(int posIndex);
	void removeAllUnits();
	void swapUnits(SquadPos a, SquadPos b);
	Unit insertSwapUnits(int oldUnitID, Unit newUnit);
	void swapUnitPositions(int unit1ID, int unit2ID);

	bool isDefeated();
	int getMovesLeft() { return movesLeft; };
	int getMoveRange() { return moveRange; };
	int getAtkRange() { return atkRange; };
	void subtractMoves(int moves) { movesLeft = movesLeft - moves; };

	void endTurn();
	void levelUpAll();
	std::vector<LevelUpData> distributeExperience(int xp);

	BrowsingData getBrowserData() override;
	FighterFormation getFormation();

	void cleanDeadUnits();
};