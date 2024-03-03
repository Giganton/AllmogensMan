#pragma once
#include<vector>
#include "Cursor.h"
#include "Terrain.h"
#include "Menu.h"
#include "BattleMap.h"
#include "bStageVisualData.h"
#include "BattleMapVisualData.h"
#include "mStageVisualData.h"
#include "AnimationQueue.h"
#include "tagID.h"


class MapManagerVisualData
{
private:
	BattleMapVisualData mapData;
	Menu activeMenu;
	bool menuIsActive = false;
	int ID = -1;

	bool cursorVisible = true;

	bool ongoingMove = false;
	bool moveDone = false;
	mStageVisualData ongoingMoveData;

	tagID currentTurnID = tagID::noID;
public:
	AnimationQueue animQueue;
	MapManagerVisualData() {};
	MapManagerVisualData(int idNr, BattleMapVisualData mpData);

	//void setBattleStage(bStageVisualData battle) { /*lastBattle = battle;*/ animQueue.addBattle(battle); /*bStageID = battleNr;*/ };
	void setActiveMenu(Menu mn) { activeMenu = mn; menuIsActive = true; };

	void setActiveMoveStage(mStageVisualData mData) { ongoingMoveData = mData; ongoingMove = true; };
	//void setCompletedMoveStage(mStageVisualData mData) { /*completedMoveData = mData;*/ ongoingMove = false; animQueue.addMovement(mData); };

	BattleMapVisualData getMapData() { return mapData; };

	int getID() { return ID; };
	Menu getActiveMenu();
	bool isMenuActive() { return menuIsActive; };
	//bStageVisualData getStageData() { return lastBattle; };
	/*long int getStageID() { return bStageID; };*/
	bool isMoving() { return ongoingMove; };
	bool hasMoved() { return moveDone; };
	mStageVisualData getOngoingMoveData() { return ongoingMoveData; };
	//mStageVisualData getCompletedMovesData() { return completedMoveData; };
	bool isCursorVisible() { return cursorVisible; };
	void setCursorVisible(bool vis) { cursorVisible = vis; };
	
	void setCurrentTurnID(tagID tag) { currentTurnID = tag; };
	tagID getCurrentTurnID() { return currentTurnID; };
};