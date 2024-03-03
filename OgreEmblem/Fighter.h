#pragma once
#include "UnitStatistics.h"

class Fighter
{
private:
	UnitStatistics stats;
	int unitID = -1;
public:
	Fighter() {};
	Fighter(UnitStatistics sts, int id) { stats = sts; unitID = id; };

	UnitStatistics getStats() { return stats; };
	int getID() { return unitID; };
	void setStats(UnitStatistics sts) { stats = sts; };
};