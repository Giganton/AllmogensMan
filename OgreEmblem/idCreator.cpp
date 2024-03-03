#include "idCreator.h"

Squad IdCreator::createSquad()
{
	Squad newSquad = Squad(squadCounter);
	squadCounter = squadCounter + 1;
	return newSquad;
}

Squad IdCreator::createSquad(Unit leaderUnit, StringHandler* strHandler)
{
	leaderUnit.makeLeader();
	Squad newSquad = Squad(squadCounter, leaderUnit, strHandler);
	squadCounter = squadCounter + 1;
	return newSquad;
}

Squad IdCreator::createSquad(Unit leaderUnit, SquadPos pos, StringHandler* strHandler)
{
	leaderUnit.makeLeader();
	Squad newSquad = Squad(squadCounter, leaderUnit, pos, strHandler);
	squadCounter = squadCounter + 1;
	return newSquad;
}