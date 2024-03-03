#pragma once
#include<vector>
#include "Squad.h"
#include<list>
#include "FightResults.h"

class BattleVisualData
{
private:
	int attackerID = -1;
	int defenderID = -1;
	std::vector<UnitInSquadData> preBattleAtkers;
	std::vector<UnitInSquadData> preBattleDefers;
	std::list<ActionResults> results;
	bool battleIsWon = false;

	bool attackingPlayer = false;
	bool defendingPlayer = false;
	int xpPostBattle = -1;

public:
	BattleVisualData() {};
	BattleVisualData(Squad atker, Squad defer) { attackerID = atker.getID(); defenderID = defer.getID(); preBattleAtkers = atker.getUnitList(); preBattleDefers = defer.getUnitList(); };
	void setResults(std::list<ActionResults> res) { results = res; battleIsWon = true; };

	std::vector<UnitInSquadData> getAtkers() { return preBattleAtkers; };
	std::vector<UnitInSquadData> getDefers() { return preBattleDefers; };

	int getAtkID() { return attackerID; };
	int getDefID() { return defenderID; };

	std::list<ActionResults> getResults() { return results; };

	bool isBattleDone() { return battleIsWon; };
	void setBattleDone(bool tf) { battleIsWon = tf; };

	void playerIsAttacking() { attackingPlayer = true; };
	void playerIsDefending() { defendingPlayer = true; };

	bool isPlayerAttacking() { return attackingPlayer; };
	bool isPlayerDefending() { return defendingPlayer; };

	void setPostBattleXP(int xp) { xpPostBattle = xp; };
	int getXP() { return xpPostBattle; };
};