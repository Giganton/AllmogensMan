#include "ActionAnimation_Attack.h"


ActionAnimation_Attack::ActionAnimation_Attack(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww) : ActionAnimation(battleAnim, results, isMaster, assets, ww)
{
}

bool ActionAnimation_Attack::progressAction()
{
	unsigned int i;
	bool allFinished = false;
	//std::vector<FightEffect> effects = animatedResults.getEffects();

	switch (step)
	{
		/*case 0:
			if (isLockUnlocked(instanceLocks.at(nextLockIndex)))
			{
				nextLockIndex = nextLockIndex + 1;
				isActive = true;
				step = 1;
			}
			else
			{
				isActive = false;
			}
			break;*/
	case 0:
		spriteAnimations.find(activatorID)->second.addToQueue(enumSpriteAnimType::move);
		step = 2;
		break;
	case 2:
		if (spriteAnimations.find(activatorID)->second.hasTriggered1())
		{
			step = 3;
			//dealDamageInSync(effects);
			//effectsAnimations.startInstance(activeInstance);
		}
		break;
	case 3:
		/*allFinished = true;
		for (i = 0; i < effects.size(); i++)
		{
			allFinished = allFinished && spriteAnimations.find(posConversion(effects.at(i).affectedPos))->second.isFinished();
		}*/

		//if (spriteAnimations.find(posConversion(activatorPos))->second.isFinished() && allFinished)
		if (spriteAnimations.find(activatorID)->second.isFinished())// && effectsAnimations.isFinished(activeInstance))
		{
			nrOfStrikesRan = nrOfStrikesRan + 1;
			if (nrOfStrikesRan == nrOfStrikesToRun)
			{
				step = 4;
			}
			else
			{
				actionInstanceFinished = true;
				step = 0;
			}
		}
		break;
	case 4:
		//animationFinished = true;
		actionInstanceFinished = true;
		break;
	}

	return (actionInstanceFinished);
}