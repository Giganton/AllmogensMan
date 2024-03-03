#pragma once

class Squad;
class BattleMap;

class AIController
{
private:

public:
	AIController() {};
	void controlSquad(Squad* sqd, BattleMap* bMap);
	std::vector<MapCoord> findPath(MapCoord start, MapCoord goal, int lengthLimit);
};