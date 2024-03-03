#pragma once
#include "MapManager.h"
#include "BrowserBucket.h"

enum mpmMenuActions { mpm_startFight, mpm_squadWait, mpm_back};

class MapPostMove : public MapManager
{
private:
	Squad movedSquad;
	MoveData moveToBePerformed;
	BrowserBucket* passedBucket = nullptr;
	Menu createPostMoveMenu();

	void moveSquad();

	void performMenuAction(int action) override;
	void pauseForAnimation() override;
	void animationFinished() override;
	void preSubLevelClosing() override;

public:
	MapPostMove() {};
	MapPostMove(int id, If_BattleManager* man, CursorPos startingPos, Squad sqd, MoveData moveData, BrowserBucket* bBucket);
};