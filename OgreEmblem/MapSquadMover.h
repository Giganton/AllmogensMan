#pragma once
#include "MapManager.h"
#include "MovementStage.h"
#include "BrowserBucket.h"

enum msmMenuActions { msm_moveSquad, msm_openStatusScreen, msm_closeMenu };


class MapSquadMover : public MapManager
{
private:
	Menu createMapMenu();
	Menu createSquadMenu();

	Squad squadToMove;
	MovementStage stage;

	BrowserBucket* passedBucket = nullptr;

	void performMenuAction(int action) override;
	void handleXPress() override;

	void uponCursorMove() override;
	void collectEvents() override;
	void atMenuOpening() override { closable = false; };
	void atMenuClosing() override;
	void preSubLevelClosing() override;

public:
	MapSquadMover() {};
	MapSquadMover(int id, If_BattleManager* man, CursorPos startingPos, Squad sqd, BrowserBucket* pBucket);
};