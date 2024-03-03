#include "ActionAnimation.h"
#include "Graphics.h"
#include <ctime>
#include "Unit.h"
#include "AllActionAnimations.h"
#include "GraphicsAssets.h"


ReactionAnimationContainer::ReactionAnimationContainer(const ReactionAnimationContainer& cpEQ)
{
	unsigned int i;
	for (i = 0; i < cpEQ.reactionAnimations.size(); i++)
	{
		reactionAnimations.push_back((cpEQ.reactionAnimations.at(i))->clone());
	}
}
ReactionAnimationContainer& ReactionAnimationContainer::operator=(const ReactionAnimationContainer cpEQ)
{
	unsigned int i;
	for (i = 0; i < cpEQ.reactionAnimations.size(); i++)
	{
		reactionAnimations.push_back((cpEQ.reactionAnimations.at(i))->clone());
	}

	return *this;
}
ReactionAnimationContainer::~ReactionAnimationContainer()
{
	unsigned int i;
	for (i = 0; i < reactionAnimations.size(); i++)
	{
		delete(reactionAnimations.at(i));
	}

}

ActionAnimation* createActionAnimation(ActionTag tag, bool actionResolved, bool isMaster, BattleAnimation* battleAnim, ActionResults results, GraphicsAssets* assets, sf::RenderWindow* ww)
{
	if (actionResolved)
	{
		switch (tag)
		{
		case ActionTag::LightningStrike:
			return new ActionAnimation_LightningStrike(battleAnim, results, isMaster, assets, ww);
		case ActionTag::Strike:
			return new ActionAnimation_Strike(battleAnim, results, isMaster, assets, ww);
		case ActionTag::Riposte:
			return new ActionAnimation_Riposte(battleAnim, results, isMaster, assets, ww);
		case ActionTag::Rage:
			return new ActionAnimation_Rage(battleAnim, results, isMaster, assets, ww);
		case ActionTag::Martyr:
			return new ActionAnimation_Martyr(battleAnim, results, isMaster, assets, ww);
		default:
			return new ActionAnimation_Default(battleAnim, results, isMaster, assets, ww);
		}
	}
	else
	{
		return new ActionAnimation_Unresolved(battleAnim, results, isMaster, assets, ww);
	}
}

ActionAnimation::ActionAnimation(BattleAnimation* battleAnim, ActionResults results, bool master, GraphicsAssets* assets, sf::RenderWindow* ww)
{
	unsigned int i;
	step = 0;
	externalStep = 0;
	currentBattle = battleAnim; 
	animatedResults = results;
	activatorPos = results.getActivatorPos();
	activatorID = results.getActivatorID();
	animationAssets = &assets->battleAnimationPackage;
	window = ww;

	instanceMaster = master;
	instanceLocks = results.getInstanceNrs();


	std::vector<ActionResults>* reactions = {};// = results.getReActionResultsPtr();

	for (i = 0; i < reactions->size(); i++)
	{
		ActionTag tag = reactions->at(i).getActionTag();
		bool resolved = reactions->at(i).didActionResolve();
		reactionAnimations.push_back(createActionAnimation(tag, resolved, false, battleAnim, reactions->at(i), assets, ww));
	}

	//effectsAnimations = EffectAnimationHandler(battleAnim, results.getEffects(), assets);

	for (i = 0; i < results.getActivatedTraits().size(); i++)
	{

		//TraitAnimation* anim = createTraitAnimation(currentBattle, &spriteAnimations, results.getActivatedTraits().at(i));
		//traitAnimations.addTraitAnimation(anim);
	}

	if (master)
	{
		currentInstance = 1;
		unlock(currentInstance);
	}

	initSpriteAnimMappings();
}

ActionAnimation2::ActionAnimation2(BattleAnimation* battleAnim, ActionResults results, bool master, GraphicsAssets* assets, sf::RenderWindow* ww)
{

}

void ActionAnimation::initSpriteAnimMappings()
{
	FightPos ab1 = FightPos(SquadPos(0, 0), true);
	FightPos ab2 = FightPos(SquadPos(0, 1), true);
	FightPos ab3 = FightPos(SquadPos(0, 2), true);
	FightPos af1 = FightPos(SquadPos(1, 0), true);
	FightPos af2 = FightPos(SquadPos(1, 1), true);
	FightPos af3 = FightPos(SquadPos(1, 2), true);
	FightPos db1 = FightPos(SquadPos(0, 0), false);
	FightPos db2 = FightPos(SquadPos(0, 1), false);
	FightPos db3 = FightPos(SquadPos(0, 2), false);
	FightPos df1 = FightPos(SquadPos(1, 0), false);
	FightPos df2 = FightPos(SquadPos(1, 1), false);
	FightPos df3 = FightPos(SquadPos(1, 2), false);

	std::vector<int> allIDs = currentBattle->getAllIDs();
	unsigned int i;

	for (i = 0; i < allIDs.size(); i++)
	{
		spriteAnimations.insert({ allIDs.at(i) , SpriteAnimation(currentBattle, allIDs.at(i), currentBattle->isSpriteAttacking(allIDs.at(i))) });
	}

	/*spriteAnimations.insert({ posConversion(ab1) , SpriteAnimation(currentBattle, ab1) });
	spriteAnimations.insert({ posConversion(ab2) , SpriteAnimation(currentBattle, ab2) });
	spriteAnimations.insert({ posConversion(ab3) , SpriteAnimation(currentBattle, ab3) });
	spriteAnimations.insert({ posConversion(af1) , SpriteAnimation(currentBattle, af1) });
	spriteAnimations.insert({ posConversion(af2) , SpriteAnimation(currentBattle, af2) });
	spriteAnimations.insert({ posConversion(af3) , SpriteAnimation(currentBattle, af3) });
	spriteAnimations.insert({ posConversion(db1) , SpriteAnimation(currentBattle, db1) });
	spriteAnimations.insert({ posConversion(db2) , SpriteAnimation(currentBattle, db2) });
	spriteAnimations.insert({ posConversion(db3) , SpriteAnimation(currentBattle, db3) });
	spriteAnimations.insert({ posConversion(df1) , SpriteAnimation(currentBattle, df1) });
	spriteAnimations.insert({ posConversion(df2) , SpriteAnimation(currentBattle, df2) });
	spriteAnimations.insert({ posConversion(df3) , SpriteAnimation(currentBattle, df3) });*/
}

bool ActionAnimation::isLockUnlocked(int lock)
{
	unsigned int i;
	for (i = 0; i < instanceKeys.size(); i++)
	{
		if (instanceKeys.at(i) == lock)
		{
			return true;
		}
	}
	return false;
}

void ActionAnimation::unlock(int key)
{ 
	unsigned int i;
	instanceKeys.push_back(key); 
	for (i = 0; i < reactionAnimations.size(); i++)
	{
		reactionAnimations.at(i)->unlock(key);
	}
}


bool ActionAnimation::isAnyInstanceActive()
{
	bool retVal = isActive;
	unsigned int i;
	if (!retVal)
	{
		for (i = 0; i < reactionAnimations.size(); i++)
		{
			retVal = retVal || reactionAnimations.at(i)->isAnyInstanceActive();
		}
	}
	return retVal;
}

void ActionAnimation::externalProgress()
{
	switch (externalStep)
	{
	case 0:
		if (nextLockIndex == instanceLocks.size())
		{
			animationFinished = true;
		}
		else if (isLockUnlocked(instanceLocks.at(nextLockIndex)))
		{
			activeInstance = instanceLocks.at(nextLockIndex);
			isActive = true;
			externalStep = 1;
		}
		else
		{
			isActive = false;
		}
		break;
	case 1:
		actionInstanceFinished = false;
		if (progressAction())
		{
			externalStep = 2;
		}
		break;
	case 2:
		if (areActionAdditionsalsDone(activeInstance))
		{
			finishedInstances.push_back(activeInstance);
			nextLockIndex = nextLockIndex + 1;
			externalStep = 0;
		}
	}

}

bool ActionAnimation::doIHaveThisInstance(int instanceNr)
{
	unsigned int i;
	for (i = 0; i < instanceLocks.size(); i++)
	{
		if (instanceLocks.at(i) == instanceNr)
		{
			return true;
		}
	}
	return false;
}

bool ActionAnimation::haveICompletedThisInstance(int instanceNr)
{
	unsigned int j;
	for (j = 0; j < finishedInstances.size(); j++)
	{
		if (finishedInstances.at(j) == instanceNr)
		{
			return true;
		}
	}
	return false;
}

bool ActionAnimation::isThisInstanceDone(int instanceNr)
{
	bool retVal;
	unsigned int i;
	if (doIHaveThisInstance(instanceNr) && !haveICompletedThisInstance(instanceNr))
	{
		return false;
	}
	retVal = true;
	for (i = 0; i < reactionAnimations.size(); i++)
	{
		retVal = retVal && reactionAnimations.at(i)->isThisInstanceDone(instanceNr);
	}
	return retVal;
}

void ActionAnimation::masterProgression()
{
	if (!instanceMaster)
	{
		throw new std::exception();
	}

	if (isThisInstanceDone(currentInstance)) //om ingen instans är aktiv, starta nästa instans
	{
		currentInstance++;
		unlock(currentInstance);
	}
}

void ActionAnimation::progressSprites()
{
	std::map<int, SpriteAnimation>::iterator it;
	//bool retVal = true;

	for (it = spriteAnimations.begin(); it != spriteAnimations.end(); it++)
	{
		it->second.progress();
		//retVal = retVal && it->second.isFinished();
	}
	//return retVal;
}

bool ActionAnimation::areSpriteAnimationsFinished()
{
	std::map<int, SpriteAnimation>::iterator it;
	bool retVal = true;

	for (it = spriteAnimations.begin(); it != spriteAnimations.end(); it++)
	{
		retVal = retVal && it->second.isFinished();
	}
	return retVal;
}

/*void ActionAnimation::progressEffects()
{
	//effectsAnimations.progress();
	//return effectsAnimations.isFinished();
}*/

bool ActionAnimation::areActionAdditionsalsDone(int instanceNr)
{
	return areSpriteAnimationsFinished();// && effectsAnimations.isFinished(instanceNr);
}


bool ActionAnimation::areActionAdditionsalsDone()
{
	return areSpriteAnimationsFinished();// && effectsAnimations.isFinished();
}

bool ActionAnimation::allAnimationsFinished()
{
	unsigned int i;

	bool retVal = animationFinished && areActionAdditionsalsDone();

	for (i = 0; i < reactionAnimations.size(); i++)
	{
		retVal = retVal && reactionAnimations.at(i)->allAnimationsFinished();
	}
	return retVal;
}

void ActionAnimation::runAnimation()
{
	externalProgress();
	progressSprites();
	//progressEffects();

	unsigned int i;
	for (i = 0; i < reactionAnimations.size(); i++)
	{
		reactionAnimations.at(i)->runAnimation();
		//tag reaktionsanimationerna i tur och ordning
		/*if (reactionAnimations.at(i)->allAnimationsFinished())
		{
				
		}
		else
		{
			actionFinished = reactionAnimations.at(i)->runAnimation() && i == (reactionAnimations.size() - 1);
			break;
		}*/
	}

	if (instanceMaster)
	{
		masterProgression();
	}
}

void ActionAnimation::draw(sf::RenderWindow* window)
{
	//effectsAnimations.draw(window);
	unsigned int i;
	for (i = 0; i < reactionAnimations.size(); i++)
	{
		reactionAnimations.at(i)->draw(window);
	}
}

void ActionAnimation::reset()
{
	step = 0;
	damageSyncInitialized = false;
}

/*bool ActionAnimation::dealDamageInSync(std::vector<FightEffect> damageEffects)
{
	unsigned int i;
	bool allAnimationsFinished = true;
	bool preDamageFinished = true;
	bool postDamageFinished = true;

	for (i = 0; i < traitAnimations.size(); i++)
	{
		preDamageFinished = preDamageFinished && traitAnimations.getAnim(i)->animatePreDamage();
	}

	for (i = 0; i < damageEffects.size(); i++)
	{
		FightPos mapPos = damageEffects.at(i).affectedPos;
		allAnimationsFinished = allAnimationsFinished && spriteAnimations.find(posConversion(mapPos))->second.isFinished();
	}
	if (allAnimationsFinished)
	{
		damageSyncInitialized = true;
		for (i = 0; i < damageEffects.size(); i++)
		{
			spriteAnimations.find(posConversion(damageEffects.at(i).affectedPos))->second.addToQueue(enumSpriteAnimType::incomingDamage);
			currentBattle->getLifeBarPtr(damageEffects.at(i).affectedPos)->dealDamage(damageEffects.at(i).damageTaken);
		}
	}

	if (damageSyncInitialized)
	{
		for (i = 0; i < traitAnimations.size(); i++)
		{
			postDamageFinished = postDamageFinished && traitAnimations.getAnim(i)->animatePostDamage();
		}
	}
	if (postDamageFinished)
	{
		damageSyncInitialized = false;
	}

	return preDamageFinished && postDamageFinished && allAnimationsFinished;
}*/

bool ActionAnimation_Default::progressAction()
{
	unsigned int i;
	bool allFinished = false;
	//std::vector<FightEffect> effects = animatedResults.getEffects();
	std::vector<Targets> targets = animatedResults.getTargets();

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
			//dealDamageInSync(effects);
			//effectsAnimations.startInstance(activeInstance);
		}
		break;
	case 2:
		allFinished = true;
		for (i = 0; i < targets.size(); i++)
		{
			allFinished = allFinished && spriteAnimations.find(targets.at(i).getPrimaryTarget().second)->second.isFinished();
		}

		if (spriteAnimations.find(activatorID)->second.isFinished() && allFinished)// && effectsAnimations.isFinished())
		{
			actionInstanceFinished = true;
			step = 3;
		}
		break;
	case 3:
		actionInstanceFinished = true;
		break;
	}
	//progressSprites();
	return (actionInstanceFinished);
}
bool ActionAnimation_Unresolved::progressAction()
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
		/*for (i = 0; i < effects.size(); i++)
		{
			if (spriteAnimations.find(activatorID)->second.hasTriggered1())
			{
				spriteAnimations.find(effects.at(i).affectedID)->second.addToQueue(enumSpriteAnimType::incomingDamage);
				currentBattle->getLifeBarPtr(effects.at(i).affectedPos)->dealDamage(effects.at(i).damageTaken);
			}
		}*/
		step = 2;
		break;
	case 2:
		if (spriteAnimations.find(activatorID)->second.isFinished())
		{
			actionInstanceFinished = true;
		}
	}
	return (actionInstanceFinished);
}