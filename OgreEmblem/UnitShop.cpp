#include "UnitShop.h"


Unit UnitShop::buyUnit(int unitID)
{
	unsigned int i;
	for (i = 0; i < inventory.size(); i++)
	{
		if (inventory.at(i).getID() == unitID)
		{
			Unit temp = inventory.at(i);
			inventory.erase(inventory.begin() + i);
			return temp;
		}
	}
	throw new std::exception();
	return Unit();
}

Unit UnitShop::getUnit(int unitID)
{
	unsigned int i;
	for (i = 0; i < inventory.size(); i++)
	{
		if (inventory.at(i).getID() == unitID)
		{
			Unit temp = inventory.at(i);
			return temp;
		}
	}
	throw new std::exception();
	return Unit();
}