#include "ActionAnimation_Rage.h"

ActionAnimation_Rage::ActionAnimation_Rage(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww) : ActionAnimation(battleAnim, results, isMaster, assets, ww)
{

}

bool ActionAnimation_Rage::progressAction()
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