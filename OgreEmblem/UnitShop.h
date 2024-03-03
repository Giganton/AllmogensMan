#pragma once
#include "Unit.h"

class UnitShop
{
private:
	std::vector<Unit> inventory;
public:
	UnitShop() {};
	UnitShop(std::vector<Unit> units) {	inventory = units; };

	std::vector<Unit> getInventory() { return inventory; };
	Unit buyUnit(int unitID);
	Unit getUnit(int unitID);
};