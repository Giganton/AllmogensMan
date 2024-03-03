#pragma once
#include "Action.h"

class Fight;

class Riposte : public ReAction
{
private:
	int maxxNrOfUses = 1;
	
public:
	Riposte();

	ReAction* clone() const override { return new Riposte(*this); };
	ReAction* allocateNew() const override { return new Riposte(); };

	bool reactToUnitAboutToBeAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults) override;
	bool reactToUnitHavingBeenAttacked(Fight* activeFight, FightPos ownPos, int ownID, AttackStage* aStage, ActionResults* reactionResults) override;

	//bool reactToSelfBeingAttacked(Fight* activeFight, FightPos attackingPos, FightPos defendingPos, FightPos ownPos, ActionResults* reactionResults, AttackStage* stagedAttack) override;
	//bool reactToSelfHavingBeenAttacked(Fight* activeFight, FightPos attackingPos, FightPos defendingPos, FightPos ownPos, ActionResults* reactionResults) override;
	//bool isTriggingAttackBlocked() override;

	//FightResults execute(Unit* attacker, SquadPos atkPos, std::vector<std::pair<std::vector<SquadPos>, std::vector<SquadPos>>> targets, Squad* defenders) override;
};