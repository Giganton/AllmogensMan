#pragma once
#include<list>
#include<vector>
#include "Terrain.h"
#include "Squad.h"
#include "bStageVisualData.h"
#include "FightResults.h"


class BattleStage
{
private:
	Terrain atkTerrain;
	Terrain defTerrain;
	Squad* atkSquad = nullptr;
	Squad* defSquad = nullptr;


	BattleVisualData visuals;

	bool battleDone = false;
public:
	BattleStage() {};
	BattleStage(Terrain atkTerr, Terrain defTerr, Squad* attacker, Squad* defender);
	//std::list<FightResults> doBattle();
	void prepareForBattle();
	void doBattle();
	bool isBattleDone() { return battleDone; };
	//void printStage();
	Squad* getAtkSquad() { return atkSquad; };
	Squad* getDefSquad() { return defSquad; };
	int getAttackerXP();
	int getDefenderXP();

	BattleVisualData getVisuals();
	std::list<ActionResults> getResults() { return visuals.getResults(); };
};