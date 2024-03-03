#pragma once
#include "Squad.h"

class StringHandler;

class IdCreator
{
private:
	int squadCounter = -1;
	int unitCounter = -1;

public:
	IdCreator() { squadCounter = 0; unitCounter = 0; };

	Squad createSquad();
	Squad createSquad(Unit leaderUnit, StringHandler* strHandler);
	Squad createSquad(Unit leaderUnit, SquadPos pos, StringHandler* strHandler);
	Unit createUnit(std::string nm, int mHP, int atk, int def, Profession* prof) { Unit newUnit = Unit(nm, mHP, atk, def, prof, unitCounter); unitCounter = unitCounter + 1; return newUnit; };
	Unit createUnit(std::string nm, int mHP, int atk, int def, Profession* prof, Career career) { Unit newUnit = Unit(nm, mHP, atk, def, prof, unitCounter, career); unitCounter = unitCounter + 1; return newUnit; };
	//Hero createHero(std::string nm, int mHP, int atk, int def, Profession* prof, Action* actn) { Hero newUnit = Hero(nm, mHP, atk, def, prof, actn, unitCounter); unitCounter = unitCounter + 1; return newUnit; };
};