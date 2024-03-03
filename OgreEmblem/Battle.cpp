#include "Battle.h"


Battle::Battle(std::string imagePath, std::map<std::string, TerrainTypes> terrainMap, std::vector<VictoryCondition> vc)
{
	map = BattleMap(imagePath, terrainMap);
	victoryConditions = vc;
}

std::vector<Squad> Battle::getEnemySquads()
{
	unsigned int i;
	std::vector<Squad> retVal;

	for (i = 0; i < enemySpawns.size(); i++)
	{
		retVal.push_back(enemySpawns.at(i).first);
	}
	return retVal;
}