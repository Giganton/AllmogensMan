#include "ActionSetup.h"


/*ActionSetup::~ActionSetup()
{
	clear();
}*/

std::vector<ReAction*>* ActionSetup::getReactionsPtr()
{
	return &reactions;
}

std::vector<Boon*> ActionSetup::getBoonsPtr()
{
	return boons;
}

std::vector<Triggerable*> ActionSetup::getAllTriggerables()
{
	unsigned int i;
	std::vector<Triggerable*> retVal;

	for (i = 0; i < reactions.size(); i++)
	{
		retVal.push_back(reactions.at(i));
	}

	for (i = 0; i < boons.size(); i++)
	{
		retVal.push_back(boons.at(i));
	}

	return retVal;
}

/*ActionSetup::ActionSetup(const ActionSetup& cP)
{
	unsigned int i;
	for (i = 0; i < cP.fightActions.size(); i++)
	{
		fightActions.push_back(cP.fightActions.at(i)->clone());
	}
	for (i = 0; i < cP.reactions.size(); i++)
	{
		reactions.push_back(cP.reactions.at(i)->clone());
	}
	for (i = 0; i < cP.boons.size(); i++)
	{
		boons.push_back(cP.boons.at(i)->clone());
	}
}

ActionSetup& ActionSetup::operator=(const ActionSetup aP)
{
	unsigned int i;
	for (i = 0; i < aP.fightActions.size(); i++)
	{
		fightActions.push_back(aP.fightActions.at(i)->clone());
	}
	for (i = 0; i < aP.reactions.size(); i++)
	{
		reactions.push_back(aP.reactions.at(i)->clone());
	}
	for (i = 0; i < aP.boons.size(); i++)
	{
		boons.push_back(aP.boons.at(i)->clone());
	}

	return *this;
}*/

void ActionSetup::clear()
{
	unsigned int i;
	/*for (i = 0; i < fightActions.size(); i++)
	{
		delete fightActions.at(i);
	}
	for (i = 0; i < reactions.size(); i++)
	{
		delete reactions.at(i);
	}
	for (i = 0; i < boons.size(); i++)
	{
		//delete boons.at(i);
	}*/

	fightActions.clear();
	reactions.clear();
	boons.clear();
}


void ActionSetup::addAction(Action* action)
{
	if (action == nullptr)
	{
		throw new std::exception();
	}

	fightActions.push_back(action);
	actionSet = true;
}

void ActionSetup::addBoon(Boon* boon)
{
	if (boon == nullptr)
	{
		throw new std::exception();
	}

	boons.push_back(boon);
}

void ActionSetup::addReAction(ReAction* reaction) 
{ 
	if (reaction == nullptr)
	{
		throw new std::exception();
	}

	reactions.push_back(reaction); 
}