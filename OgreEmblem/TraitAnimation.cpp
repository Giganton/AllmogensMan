#include "TraitAnimation.h"
#include "TraitAnimation_HugeStrength.h"
#include "BattleAnimation.h"

int posConversion(FightPos mapPos)
{
	int offset = 0;
	if (mapPos.attackingSide)
	{
		offset = 100;
	}
	return (offset + mapPos.squadPos.getX() * 10 + mapPos.squadPos.getY());
}
/*bool TraitAnimation::dealDamageInSync(std::vector<FightEffect> damageEffects)
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
		allAnimationsFinished = allAnimationsFinished && spriteAnimations->find(posConversion(mapPos))->second.isFinished();
	}
	if (allAnimationsFinished)
	{
		damageSyncInitialized = true;
		for (i = 0; i < damageEffects.size(); i++)
		{
			spriteAnimations->find(posConversion(damageEffects.at(i).affectedPos))->second.addToQueue(enumSpriteAnimType::incomingDamage);
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

TraitAnimation* createTraitAnimation(BattleAnimation* bAnim, std::map<int, SpriteAnimation>* spriteMap, TraitTag results)
{
	TraitTag tag = results;
	switch (tag)
	{
	case TraitTag::enumHugeStrength:
		return new TraitAnimation_HugeStrength(bAnim, spriteMap, results);
		break;
	default:
		throw new std::exception();
		return new TraitAnimation_HugeStrength(bAnim, spriteMap, results);
	}
}

TraitAnimationContainer::~TraitAnimationContainer()
{
	unsigned int i;
	for (i = 0; i < traitList.size(); i++)
	{
		delete traitList.at(i);
	}
}
TraitAnimationContainer::TraitAnimationContainer(const TraitAnimationContainer& cp)
{
	unsigned int i;
	for (i = 0; i < traitList.size(); i++)
	{
		traitList.push_back(cp.traitList.at(i)->clone());
	}
}
TraitAnimationContainer& TraitAnimationContainer::operator=(const TraitAnimationContainer cp)
{
	unsigned int i;
	for (i = 0; i < traitList.size(); i++)
	{
		traitList.push_back(cp.traitList.at(i)->clone());
	}
	return *this;
}



TraitAnimation::TraitAnimation(BattleAnimation* bAnim, std::map<int, SpriteAnimation>* spriteMap, TraitTag traitTag)
{ 
	spriteAnimations = spriteMap; 
	tag = traitTag; 
	currentBattle = bAnim;

	TraitAnimation* anim = createTraitAnimation(bAnim, spriteAnimations, traitTag);
	traitAnimations.addTraitAnimation(anim);
	/*unsigned int i;
	for (i = 0; i < results.getActivatedTraits().size(); i++)
	{
		TraitAnimation* anim = createTraitAnimation(bAnim, spriteAnimations, results.getActivatedTraits().at(i));
		traitAnimations.addTraitAnimation(anim);
	}*/
}