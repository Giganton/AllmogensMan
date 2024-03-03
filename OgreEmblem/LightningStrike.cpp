#include "LightningStrike.h"
#include "FightResults.h"
#include "Fight.h"
#include "Unit.h"

LightningStrike::LightningStrike()
{
	name = "Lightning Strike";
	targetingType = TargetingType::random;
	tag = ActionTag::LightningStrike;
}

ActionResults LightningStrike::performAction(int userID, std::vector<Targets> targets, Fight* activeFight, ActionResults resultsFrame)
{
	unsigned int i, j;
	//vilken betydelse har instansnummer i en actionresults? Såklart! Det är för att koppla ihop effekterna med actionanimationen.
	for (i = 0; i < targets.size(); i++)
	{
		Unit* primaryTarget = activeFight->findFighter(targets.at(i).getPrimaryTarget().first);
		int instanceNr = activeFight->takeInstanceNr();
		resultsFrame.addInstanceNr(instanceNr);

		activeFight->dealDamage(primaryDamage, targets.at(i).getPrimaryTarget().second, userID, instanceNr, &resultsFrame, TraitTag::enumTraitNone);
	}

	return resultsFrame;
}
