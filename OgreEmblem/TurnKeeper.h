#pragma once
#include "tagID.h"
#include<vector>
#include "Flag.h"

/*
class Participant
{
private:
	std::vector<int> squads;
	tagID flagTag = tagID::noID;
public:
	Participant() {};
	Participant(tagID tag, std::vector<int> sqds) { flagTag = tag; squads = sqds; };

	tagID getTag() { return flagTag; };
	std::vector<int> getSquads() { return squads; };
};*/

class BattleField;

class TurnKeeper
{
private:
	BattleField* bField = nullptr;

	std::vector<Flag*> participants = {};
	Flag* activeTeam = nullptr;
	int activeIndex = -1;
	std::vector<int> squadsInAction;
	bool turnIsFinished = false;

	void activateTeam(Flag* team);
public:
	TurnKeeper() {};
	TurnKeeper(std::vector<Flag*> teams, BattleField* battleField);

	bool isTurnFinished() { return turnIsFinished; };
	bool isPlayerActive() { return (activeTeam->getTag() == tagID::player); };
	void endTurn();
	void putToRest(int squadID);
	bool isSquadActive(int squadID);
	std::vector<int> getActiveSquads() { return squadsInAction; };
	Flag* getActiveFlag() { return activeTeam; };
};