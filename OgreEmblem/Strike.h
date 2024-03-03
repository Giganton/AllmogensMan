#pragma once
#include "Action.h"


class Strike : public Action
{
private:
	ActionResults performAction(int userID, std::vector<Targets> targets, Fight* activeFight, ActionResults resultsFrame) override;
public:
	Strike();
	Action* clone() const override { return new Strike(*this); };
	Action* allocateNew() const override { return new Strike(); };

	//FightResults execute(Unit* attacker, SquadPos atkPos, std::vector<std::pair<std::vector<SquadPos>, std::vector<SquadPos>>> targets, Squad* defenders) override;
};