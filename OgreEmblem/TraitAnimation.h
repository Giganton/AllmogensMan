#pragma once
#include<map>
#include "SpriteAnimation.h"
#include "FightResults.h"

class BattleAnimation;
class TraitAnimation;
int posConversion(FightPos mapPos);

class TraitAnimationContainer
{
private:
	std::vector<TraitAnimation*> traitList;
public:
	TraitAnimationContainer() {};
	~TraitAnimationContainer();
	TraitAnimationContainer(const TraitAnimationContainer& cp);
	TraitAnimationContainer& operator=(const TraitAnimationContainer as);

	void addTraitAnimation(TraitAnimation* anim) { traitList.push_back(anim); };
	TraitAnimation* getAnim(int i) { return traitList.at(i); };
	unsigned int size() { return traitList.size(); };

};

class TraitAnimation
{
protected:
	BattleAnimation* currentBattle = nullptr;
	std::map<int, SpriteAnimation>* spriteAnimations = nullptr;
	TraitAnimationContainer traitAnimations;
	//TraitResults animatedResults;
	TraitTag tag;
	bool ongoingAnimation = false;
	bool animationStarted = false;
	int step = -1;
	bool damageSyncInitialized = false;

	bool dealDamageInSync();
public:
	TraitAnimation() {};
	TraitAnimation(BattleAnimation* bAnim, std::map<int, SpriteAnimation>* spriteMap, TraitTag tag);
	virtual TraitAnimation* clone() const = 0;

	virtual bool animatePostDamage() { return true; };
	virtual bool animatePreDamage() { return true; };

	bool allAnimationsFinished() { return animationStarted && !ongoingAnimation; };
};



TraitAnimation* createTraitAnimation(BattleAnimation* bAnim, std::map<int, SpriteAnimation>* spriteMap, TraitTag traitTag);