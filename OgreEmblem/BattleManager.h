#pragma once
#include "MapBrowser.h"
#include "Flag.h"
//#include "Action.h"
#include "idCreator.h"
#include "BattleField.h"


class StringHandler;

class If_BattleManager
{
public:
	virtual bool isSquadActive(int id) = 0;
	virtual BattleMap getMap() = 0;
	virtual BattleField getBattleField() = 0;
	virtual BattleField* getBattleFieldPtr() = 0;
	virtual StructuredEventQueue endTurn() = 0;
	virtual void putToRest(int squadID) = 0;
	virtual MoveData moveSquad(MoveData data) = 0;
	virtual std::pair<BattleVisualData, std::vector<LevelUpData>> doBattle(int attackerID, int defenderID) = 0;
	virtual MoveData peekMoveSquad(MoveData moveData) = 0;
	virtual StructuredEventQueue runAI() = 0;
	virtual bool checkForVictory() = 0;
	virtual void winBattle() = 0;
	virtual bool isBattleWon() = 0;
};

class BattleManager : public If_BattleManager
{
private:
	bool battleIsWon = false;

	IdCreator* idCreator = nullptr;
	StringHandler* stringHandler = nullptr;

	bool battleIsActive = false;

	BattleField bField;
	std::vector<VictoryCondition> victoryConditions;

	TurnKeeper turnKeeper;
	std::vector<tagID> participatingTags = {};
	std::map<tagID, Flag*> flagMap;

	SquadAI squadAI;

	//std::map<std::string, TerrainTypes> stringToTerrainMap;

	Flag* player = nullptr;
	Flag enemy;

	//void addSquadsToMap(std::vector<Squad> squadList, tagID tag);
	StructuredEventQueue AIAction();
	bool checkForRouteVictory();
	void endBattle();
public:
	BattleManager() {};
	BattleManager(IdCreator* idCr, StringHandler* strHand);

	void initiateBattlefield(Flag* player, Battle nextBattle);
	//void initiateFlags(std::vector<Flag*> flags);

	BattleMap getMap() override { return bField.getBattleMap(); };
	BattleField getBattleField() override { return bField; };
	BattleField* getBattleFieldPtr() override { return &bField; };
	//bool isActive() { return battleIsActive; };

	MoveData moveSquad(MoveData moveData) override;
	MoveData peekMoveSquad(MoveData moveData) override;

	std::pair<BattleVisualData, std::vector<LevelUpData>> doBattle(int attackerID, int defenderID) override;

	StructuredEventQueue runAI() { return AIAction(); };
	StructuredEventQueue endTurn() override;
	bool isSquadActive(int id) override;
	void putToRest(int squadID) override;

	bool checkForVictory();
	void winBattle();
	bool isBattleWon() { return battleIsWon; };
	void deActivateBattle() { battleIsActive = false; };
	bool isActive() { return battleIsActive; };
};