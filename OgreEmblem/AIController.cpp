#include "AIController.h"
#include "Squad.h"
#include "BattleMap.h"

void AIController::controlSquad(Squad* squad, BattleMap* bMap)
{
	MapCoord sqdPos = bMap->findSquad(squad);
	std::vector<Squad*> targetsInRange = bMap->allSquadsInRange(sqdPos.getX(), sqdPos.getY(), squad->getMoveRange() + 1);
}

std::vector<MapCoord> AIController::findPath(MapCoord start, MapCoord goal, int lengthLimit)
{

}