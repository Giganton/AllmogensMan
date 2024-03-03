#pragma once
#include "Action.h"
#include "Boon.h"

class ActionSetup
{
	bool actionSet = false;
	std::vector<Action*> fightActions;
	std::vector<ReAction*> reactions;
	std::vector<Boon*> boons;

public:
	ActionSetup() {};

	/*~ActionSetup();
	ActionSetup(const ActionSetup& cP);
	ActionSetup& operator=(const ActionSetup aP);*/

	void addAction(Action* action);
	bool isActionSet() { return actionSet; };
	void addReAction(ReAction* reaction);
	void addBoon(Boon* boon);

	std::vector<Action*>* getFightActionsPtr() { return &fightActions; };
	std::vector<ReAction*>* getReactionsPtr();
	std::vector<Boon*> getBoonsPtr();

	std::vector<Triggerable*> getAllTriggerables();

	void clear();
};