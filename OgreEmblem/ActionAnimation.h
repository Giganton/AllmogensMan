#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "FightResults.h"
#include "SpriteAnimation.h"
#include "TraitAnimation.h"
#include "GraphicsUtils.h"
#include "EffectAnimationHandler.h"

class LifeBar;
class Unit;
class BattleAnimation;
class BattleAnimationPackage;
class ActionAnimation;

class ReactionAnimationContainer
{
private:
	std::vector<ActionAnimation*> reactionAnimations;
public:
	ReactionAnimationContainer() {};

	ReactionAnimationContainer(const ReactionAnimationContainer& cpEQ);
	ReactionAnimationContainer& operator=(const ReactionAnimationContainer asEQ);
	~ReactionAnimationContainer();

	void push_back(ActionAnimation* anim) { reactionAnimations.push_back(anim); };
	ActionAnimation* at(int index) { return reactionAnimations.at(index); };
	unsigned int size() { return reactionAnimations.size(); };
};

class ActionAnimation
{
protected:
	sf::RenderWindow* window = nullptr;
	std::map<int, SpriteAnimation> spriteAnimations;
	TraitAnimationContainer traitAnimations;
	BattleAnimationPackage* animationAssets = nullptr;

	//EffectAnimationHandler effectsAnimations;

	bool instanceMaster = false;
	int currentInstance = -1; //for master
	//int currentInstance = -1;
	//bool locked = true;
	std::vector<int> instanceLocks;
	std::vector<int> instanceKeys;
	std::vector<int> finishedInstances;
	int nextLockIndex = 0;
	int activeInstance = -1;
	bool isActive = false;

	int externalStep = -1;
	int step = -1;
	bool damageSyncInitialized = false;

	bool actionInstanceFinished = false;
	bool animationFinished = false;

	BattleAnimation* currentBattle = nullptr;
	FightPos activatorPos;
	int activatorID = -1;
	ActionResults animatedResults;

	//std::vector<ActionAnimation*> reActionAnimations;
	ReactionAnimationContainer reactionAnimations;

	void initSpriteAnimMappings();
	void progressSprites();
	//void progressEffects();
	//bool dealDamageInSync(std::vector<FightEffect> damageEffects);

	bool isLockUnlocked(int lock);
	void masterProgression();
public:
	ActionAnimation() {};
	ActionAnimation(BattleAnimation* battleAnim, ActionResults results, bool master, GraphicsAssets* assets, sf::RenderWindow* ww);

	virtual ActionAnimation* clone() const = 0;
	virtual ActionAnimation* allocateNew() const = 0;

	bool areSpriteAnimationsFinished();
	bool areActionAdditionsalsDone();
	bool areActionAdditionsalsDone(int instanceNr);
	bool allAnimationsFinished();
	bool isAnyInstanceActive();
	void reset();
	void runAnimation();
	void draw(sf::RenderWindow* window);
	virtual bool progressAction() = 0;
	void externalProgress();

	bool isThisInstanceDone(int instanceNr);
	bool doIHaveThisInstance(int instanceNr);
	bool haveICompletedThisInstance(int instanceNr);

	void unlock(int key);
};

class ActionAnimation2
{
protected:

public:
	ActionAnimation2() {};
	ActionAnimation2(BattleAnimation* battleAnim, ActionResults results, bool master, GraphicsAssets* assets, sf::RenderWindow* ww);
};

class ActionAnimation_Default : public ActionAnimation
{
private:
public:
	ActionAnimation_Default() {};
	ActionAnimation_Default(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww) : ActionAnimation(battleAnim, results, isMaster, assets, ww) {};

	ActionAnimation* clone() const override { return new ActionAnimation_Default(*this); };
	ActionAnimation* allocateNew() const override { return new ActionAnimation_Default(); };

	bool progressAction() override;
};

class ActionAnimation_Unresolved : public ActionAnimation
{
private:
public:
	ActionAnimation_Unresolved() {};
	ActionAnimation_Unresolved(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww) : ActionAnimation(battleAnim, results, isMaster, assets, ww) {};

	ActionAnimation* clone() const override { return new ActionAnimation_Unresolved(*this); };
	ActionAnimation* allocateNew() const override { return new ActionAnimation_Unresolved(); };

	bool progressAction() override;
};

ActionAnimation* createActionAnimation(ActionTag tag, bool actionResolved, bool isMaster, BattleAnimation* battleAnim, ActionResults results, GraphicsAssets* assets, sf::RenderWindow* ww);