#pragma once
#include "BattleMap.h"
#include "Squad.h"
#include "MapCoord.h"

enum class VictoryCondition { none, route };

class Battle
{
private:
	BattleMap map;
	std::vector<VictoryCondition> victoryConditions;
	std::vector < std::pair < Squad, MapCoord > > enemySpawns;
public:
	Battle() {};
	Battle(std::string imagePath, std::map<std::string, TerrainTypes> terrainMap, std::vector<VictoryCondition> vc);

	BattleMap getMap() { return map; };
	std::vector < std::pair < Squad, MapCoord > > getEnemySpawns() { return enemySpawns; };
	std::vector<Squad> getEnemySquads();
	std::vector<VictoryCondition> getVictoryConditions() { return victoryConditions; };

	void addSquad(Squad squad, MapCoord mapPos) { enemySpawns.push_back(std::make_pair(squad, mapPos)); };
};