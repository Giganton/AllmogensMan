#include "ActionAnimation_Riposte.h"

ActionAnimation_Riposte::ActionAnimation_Riposte(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww) : ActionAnimation(battleAnim, results, isMaster, assets, ww)
{

}

bool ActionAnimation_Riposte::progressAction()
{
	unsigned int i;
	bool allFinished = false;
	//std::vector<FightEffect> effects = animatedResults.getEffects();

	switch (step)
	{
	case 0:
		spriteAnimations.find(activatorID)->second.addToQueue(enumSpriteAnimType::move);
		step = 1;
		break;
	case 1:
		if (spriteAnimations.find(activatorID)->second.hasTriggered1())
		{
			step = 2;
			//effectsAnimations.startInstance(activeInstance);
		}
		break;
	case 2:
		/*allFinished = true;
		for (i = 0; i < effects.size(); i++)
		{
			allFinished = allFinished && spriteAnimations.find(posConversion(effects.at(i).affectedPos))->second.isFinished();
		}*/

		if (spriteAnimations.find(activatorID)->second.isFinished())// && effectsAnimations.isFinished(activeInstance))
		{
			step = 3;
		}
		break;
	case 3:
		actionInstanceFinished = true;
	}

	return (actionInstanceFinished);
}