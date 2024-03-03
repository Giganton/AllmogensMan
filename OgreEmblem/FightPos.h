#pragma once
#include "SquadPos.h"

enum class PositionalRelation { none, invalid, samePos , neighbour , sameRow , inFrontOf , behind , sameCol , sameSide };

bool doesPRvecAcontainPRvecB(std::vector<PositionalRelation> A, std::vector<PositionalRelation> B);

class FightPos
{
public:
	SquadPos squadPos;
	bool attackingSide = true;

	FightPos() {};
	FightPos(SquadPos mapPos, bool atkSide) { squadPos = mapPos; attackingSide = atkSide; };
	bool isEqual(FightPos comp);
	bool isNeighbourTo(FightPos pos);
	bool isInSameRow(FightPos pos);
	bool isInSameCol(FightPos pos);
	bool isOnSameSide(FightPos pos);
	bool isInFrontOf(FightPos pos);
	bool isBehind(FightPos pos);

	FightPos getPosBehind();


	std::vector<PositionalRelation> getRelations(FightPos pos);


	bool operator<(const FightPos& rhs) const;
	bool operator>(const FightPos& rhs) const { return !(*this < rhs); };
};

std::vector<FightPos> getAllFightPositions();