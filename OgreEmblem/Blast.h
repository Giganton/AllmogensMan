#pragma once
#include "Action.h"

class Blast : public Action
{
private:
	int primaryDamage = 5;
	float areaFraction = 0.5;

	ActionResults performAction(int userID, std::vector<Targets> targets, Fight* activeFight, ActionResults resultsFrame) override;
public:
	Blast();
	Action* clone() const override { return new Blast(*this); };
	Action* allocateNew() const override { return new Blast(); };

	//FightResults execute(Unit* attacker, SquadPos atkPos, std::vector<std::pair<std::vector<SquadPos>, std::vector<SquadPos>>> targets, Squad* defenders) override;
	virtual std::vector<FightPos> getSecondaryTargets(FightPos defenderPos, Fight* activeFight) override;
};