#include "ReactionStage.h"


std::vector<PositionalRelation> drawPosRelFromAttack_defender(AttackStage* aStage)
{
	return aStage->defenderPos.getRelations(aStage->attackerPos);
}

std::vector<PositionalRelation> drawPosRelFromAttack_attacker(AttackStage* aStage)
{
	return aStage->attackerPos.getRelations(aStage->defenderPos);
}

AttackStage::AttackStage()
{
	containsPosRelation = true;
}

StagedAttackResults::StagedAttackResults()
{
	
}

void StagedAttackResults::clean()
{
	initiated = false;
	stagedAttack.clean();
	//stagedEffect = FightEffect();
}

void ModifyFormationBoonStage::clean()
{
	initiated = false;
	FormationActivatorID = -1;
	activatorPos = FightPos();

	triggers = 0;
}

DealDamageStage::DealDamageStage()
{
	containsPosRelation = true;
}

void AttackStage::clean()
{
	initiated = false;

	attackerID = -1;
	defenderID = -1;

	defenderPos;
	attackerPos;

	attackBlocked = false;

	attackValueChange = 0;
	defenseValueChange = 0;
	attackerWepProfLevel = 0;
	defenderWepProfLevel = 0;

	instanceNr = -1;
}

void DealDamageStage::clean()
{
	initiated = false;

	dealerID = -1;
	takerID = -1;
	takerPos;

	incomingDamage = -1;
	damageReduction = -1;
}

DeathStage::DeathStage()
{
	containsPosRelation = true;
}

void DeathStage::clean()
{
	initiated = false;

	dyingUnitID = -1;
	dyingUnitPos = FightPos();
}