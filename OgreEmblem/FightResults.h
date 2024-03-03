#pragma once
#include "Action.h"
#include "SquadPos.h"
#include "TraitTag.h"

class Unit;

/*struct FightEffect
{
	int affectedID = -1;
	//bool attackingSide = false;
	FightPos affectedPos;
	int damageTaken = -1;
	bool affectedDied = false;

	bool physicalBlock = false;

	int instanceNumber = -1;
	TraitTag sourceTrait = TraitTag::enumTraitNone;
	//traittagg som skapat effekt, om "none" antar animeraren att det är actionen som effekten ligger i som genererat effekten

	FightEffect() {};
	FightEffect(int id, FightPos mapPos, int instNr, TraitTag source) { affectedID = id; affectedPos = mapPos; instanceNumber = instNr; sourceTrait = source; };
	FightEffect(int id, FightPos mapPos, int incomingDamage, bool died, int instNr, TraitTag source) { affectedID = id; affectedPos = mapPos; damageTaken = incomingDamage; affectedDied = died; instanceNumber = instNr; sourceTrait = source; };
};*/

class TraitResults;

/*class FightResults
{
private:
	//bool initialized = false;
	int activatorID = -1;
	FightPos activatorPos;

	std::vector<FightEffect> activationEffects; //separera till primary/secondary/self
public:
	FightResults() {};
	FightResults(int ownerID, FightPos ownerPos);

	void addFightEffect(int unitID, FightPos unitPos, int incomingDamage, bool died);
	void addFightEffect(FightEffect effect) { activationEffects.push_back(effect); };
	void addFightEffect(std::vector<FightEffect> effect);

	int getActivatorID() { return activatorID; };
	FightPos getActivatorPos() { return activatorPos; };
	void setActivatorID(int id) { activatorID = id; };
	void setActivatorPos(FightPos mapPos) { activatorPos = mapPos; };

	//void addResponseTrait(TraitResults sEffect) { responseTraits.push_back(sEffect); };
	//bool isInitialized() { return initialized; };

	std::vector<FightEffect> getEffects() { return activationEffects; };
	//std::vector<TraitResults> getResponseTraits() { return responseTraits; };
};*/

/*class TraitResults
{
private:
	FightResults results;
	TraitTag activatedTrait = TraitTag::enumTraitNone;
	std::vector<TraitResults> responseTraits;
public:
	TraitResults();
	TraitResults(TraitTag trait, int ownerID, FightPos ownerPos) { activatedTrait = trait; results = FightResults(ownerID, ownerPos); }

	int getActivatorID() { return results.getActivatorID(); };
	FightPos getActivatorPos() { return results.getActivatorPos(); };
	void setActivatorID(int id) { results.setActivatorID(id); };
	void setActivatorPos(FightPos mapPos) { results.setActivatorPos(mapPos); };

	void setTraitTag(TraitTag trt) { activatedTrait = trt; };
	void addFightEffect(int unitID, FightPos unitPos, int incomingDamage, bool died, int inst) { results.addFightEffect(unitID, unitPos, incomingDamage, died); };
	void addFightEffect(FightEffect effect) { results.addFightEffect(effect); };
	void addFightEffect(std::vector<FightEffect> effect) { results.addFightEffect(effect); };

	//void addResponseTrait(TraitResults sEffect) { results.addResponseTrait(sEffect); };
	//bool isInitialized() { return results.isInitialized(); };
	bool isEmpty() { return results.getEffects().size() == 0; };

	TraitTag getTraitTag() { return activatedTrait; };
	std::vector<FightEffect> getEffects() { return results.getEffects(); };
	//std::vector<TraitResults> getResponseTraits() { return results.getResponseTraits(); };

	void addActivatedTrait(TraitResults sEffect) { responseTraits.push_back(sEffect); };
	std::vector<TraitResults> getActivatedTraits() { return responseTraits; };

	std::vector<std::pair<int, bool>> getDeathInfo();
};*/

enum class ReactionTiming { pre, intra, post };

class ReactionResultsList
{
private:
	std::vector<std::pair<int, std::vector<ActionResults>>> resultsList;
public:
	ReactionResultsList();

	void addReactionResults(ActionResults results);
	void addReactionResults(int index, ActionResults results);
	std::vector<std::pair<int, std::vector<ActionResults>>> getList() { return resultsList; };
};

class ActionResults
{
private:
	int activatorID = -1;
	FightPos activatorPos;

	//std::vector<FightEffect> activationEffects; //separera till primary/secondary/self
	std::vector<Targets> targets;
	//FightResults results;
	ActionTag action = ActionTag::none;
	std::vector<int> instances;

	bool actionResolved = false;
	//std::vector<TraitResults> responseTraits;

	std::vector<TraitTag> activatedTraits;// en lista över traits som aktiverats av actionen.Används eventuellt av animeraren för att påverka animationen. (tex trycka fienden bakåt vid Huge strength)
	std::vector<ActionResults> reActionResults;

	ReactionResultsList preReactionSpace;
	ReactionResultsList intraReactionResults;
	ReactionResultsList postReactionResults;

	std::vector<int> actionSpecifics; //actionspecifik information, kan tex berätta vilken del detta är om actionen varit flerdelad (tex hoppa fram eller tillbaka när det gäller martyr)
public:
	ActionResults();
	ActionResults(ActionTag act, int ownerID, FightPos ownerPos, std::vector<Targets> targetList);

	std::vector<std::pair<int, bool>> getDeathInfo();
	//void addEffect(FightEffect effect);
	//void addEffect(std::vector<FightEffect> effect);
	bool isInitiated() { return (activatorID != -1); }

	int getActivatorID() { return activatorID; };
	FightPos getActivatorPos() { return activatorPos; };
	void setActivatorID(int id) { activatorID = id; };
	void setActivatorPos(FightPos fPos) { activatorPos = fPos; };

	void setTargets(std::vector<Targets> targetList) { targets = targetList; };
	std::vector<Targets> getTargets() { return targets; };

	void addInstanceNr(int nr) { instances.push_back(nr); };
	std::vector<int> getInstanceNrs() { return instances; };
	int findLowestInstanceNr();
	int findHighestInstanceNr();
	std::vector<int>* getInstancesPtr() { return &instances; };

	void setActionTag(ActionTag act) { action = act; };
	//void addFightEffect(int unitID, FightPos unitPos, int incomingDamage, bool died, int instanceNr);
	//void addFightEffect(FightEffect effect) { activationEffects.push_back(effect); }
	//void addFightEffect(std::vector<FightEffect> effect);

	ActionTag getActionTag() { return action; };
	ReactionResultsList* getReActionResultsPtr(ReactionTiming timing);
	//std::vector<FightEffect> getEffects() { return activationEffects; };

	bool didActionResolve() { return actionResolved; };
	void actionDidResolve() { actionResolved = true; };

	//void addResponseTrait(TraitResults sEffect) { responseTraits.push_back(sEffect); };
	//std::vector<TraitResults> getResponseTraits() { return responseTraits; };

	//void addActivatedTrait(FightEffect sEffect);
	//void addActivatedTrait(std::vector<FightEffect> sEffect);
	std::vector<TraitTag> getActivatedTraits() { return activatedTraits; };

	void addSpecifics(int spec) { actionSpecifics.push_back(spec); };
	std::vector<int> getSpecifics() { return actionSpecifics; };
};
