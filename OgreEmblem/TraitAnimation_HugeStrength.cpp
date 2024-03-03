#include "TraitAnimation_HugeStrength.h"


bool TraitAnimation_HugeStrength::animatePostDamage()
{
	//FightPos userPos = animatedResults.getActivatorPos();

	ongoingAnimation = true;
	animationStarted = true;
	step = 1;
	

	//return dealDamageInSync(animatedResults.getEffects());
	return true;
}