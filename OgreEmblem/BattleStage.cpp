#include "BattleStage.h"
#include "Unit.h"
#include "Action.h"
#include "Fight.h"
#include<list>

BattleStage::BattleStage(Terrain atkTerr, Terrain defTerr, Squad* attacker, Squad* defender)
{
	if (attacker->isDefeated() || defender->isDefeated())
	{
		throw new std::exception();
	}

	atkTerrain = atkTerr;
	defTerrain = defTerr;

	atkSquad = attacker;
	defSquad = defender;

	visuals = BattleVisualData(*attacker, *defender);
}

void BattleStage::prepareForBattle()
{
	int i;
	std::vector<Unit*> atkUnits = atkSquad->getAllLivingUnitPtrs();
	std::vector<Unit*> defUnits = defSquad->getAllLivingUnitPtrs();

	for (i = 0; i < atkUnits.size(); i++)
	{
		atkUnits.at(i)->setupActionsForBattle(this);
	}
	for (i = 0; i < defUnits.size(); i++)
	{
		defUnits.at(i)->setupActionsForBattle(this);
	}
}

void BattleStage::doBattle()
{
	int i, j;
	std::list<ActionResults> resultsList;

	prepareForBattle();
	Fight fight = Fight(atkSquad, defSquad);
	//loop through squad and perform actions, start with front row
	for (i = TACTICAL_X - 1; i >= 0; i--)
	{
		for (j = 0; j < TACTICAL_Y; j++)
		{
			TacticalTile* tempTile = atkSquad->getTile(i, j);
			if (!tempTile->isEmpty())
			{
				Unit* atkUnit = atkSquad->getUnitPtr(i, j);

				if (!atkUnit->isDead() && !defSquad->isDefeated() && !atkUnit->isExiled())
				{
					//Action* offensiveAction = atkUnit->getAction();

					fight.setupNextFight(i, j);

					ActionResults results = fight.fight();

					resultsList.push_back(results);
				}
			}
		}
	}

	fight.battleIsDone();

	battleDone = true;
	visuals.setResults(resultsList);

	if (atkSquad->getFlagTag() == tagID::player)
	{
		visuals.playerIsAttacking();
		//visuals.setPostBattleXP(getAttackerXP());
	}
	if (defSquad->getFlagTag() == tagID::player)
	{
		visuals.playerIsDefending();
		//visuals.setPostBattleXP(getDefenderXP());
	}

}

int BattleStage::getAttackerXP()
{
	/*if (!battleDone)
	{
		throw new std::exception();
	}
	std::list<ActionResults> results = visuals.getResults();
	int totXP = 0;
	
	while (!results.empty())
	{
		unsigned int i;
		ActionResults actionResult = results.front();
		if (actionResult.getActivatorPos().attackingSide)
		{
			for (i = 0; i < results.begin()->getEffects().size(); i++)
			{
				FightEffect effect = actionResult.getEffects().at(i);
				if (!effect.affectedPos.attackingSide && effect.affectedDied)
				{
					totXP = totXP + defSquad->findUnitPtr(effect.affectedID)->getLevel() * 100;
				}
			}
		}
		results.pop_front();
	}
	return totXP;*/
	return 0;
}

int BattleStage::getDefenderXP()
{
	/*if (!battleDone)
	{
		throw new std::exception();
	}
	std::list<ActionResults> results = visuals.getResults();
	int totXP = 0;

	while (!results.empty())
	{
		unsigned int i;
		ActionResults actionResult = results.front();
		if (!actionResult.getActivatorPos().attackingSide)
		{
			for (i = 0; i < results.begin()->getEffects().size(); i++)
			{
				FightEffect effect = actionResult.getEffects().at(i);
				if (effect.affectedPos.attackingSide && effect.affectedDied)
				{
					totXP = totXP + defSquad->findUnitPtr(effect.affectedID)->getLevel() * 100;
				}
			}
		}
		results.pop_front();
	}

	return totXP;*/
	return 0;
}

BattleVisualData BattleStage::getVisuals()
{
	if (!battleDone)
	{
		throw new std::exception();
	}
	return visuals;
}