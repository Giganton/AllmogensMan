#pragma once
#include "MenuEvent.h"
#include<list>
#include "AnimationType.h"
#include "bStageVisualData.h"
#include "mStageVisualData.h"
#include "MapCoord.h"
#include "Menu.h"

class MapManagerVisualEventData
{
private:
	//events
	std::list<AnimationType> animationOrder;
	std::list<BattleVisualData> battleList;
	std::list<mStageVisualData> movesList;
	std::list<MenuEvent> menuEventList;
	std::list<MapCoord> cursorMoves;

	//static data
	mStageVisualData ongoingMoveData;
	bool isMoving = false;
	MenuVisualData activeMenu;
	bool menuIsActive = false;
	bool cursorVisible = true;
	MapCoord cursorPos;
	int ID = -1;

public:
	MapManagerVisualEventData() {};
	MapManagerVisualEventData(int idNr) { ID = idNr; };
	bool isEmpty() { return animationOrder.size() == 0; };

	void addBattle(BattleVisualData battle) { battleList.push_back(battle); animationOrder.push_back(AnimationType::battle); };
	void addMovement(mStageVisualData move) { movesList.push_back(move); animationOrder.push_back(AnimationType::movement); };
	void addMenuEvent(MenuEvent mEvent) { menuEventList.push_back(mEvent); animationOrder.push_back(AnimationType::menu); };
	void addCursorMove(MapCoord coord) { cursorMoves.push_back(coord); animationOrder.push_back(AnimationType::cursor); };

	std::list<BattleVisualData> getBattleList() { return battleList; };
	std::list<mStageVisualData> getMovementList() { return movesList; };
	std::list<MenuEvent> getMenuEventList() { return menuEventList; };
	std::list<MapCoord> getCursorMovesList() { return cursorMoves; };
	std::list<AnimationType> getQueueOrder() { return animationOrder; };

	void addQueue(MapManagerVisualEventData addQ);

	AnimationType pullLatestAnimationType() { AnimationType retVal = animationOrder.front(); animationOrder.pop_front(); return retVal; };
	BattleVisualData pullBattle() { BattleVisualData retVal = battleList.front(); battleList.pop_front(); return retVal; };
	mStageVisualData pullMovement() { mStageVisualData retVal = movesList.front(); movesList.pop_front(); return retVal; };
	MenuEvent pullMenuEvent() { MenuEvent retVal = menuEventList.front(); menuEventList.pop_front(); return retVal; };
	MapCoord pullCursorMove() { MapCoord retVal = cursorMoves.front(); cursorMoves.pop_front(); return retVal; };

	void clearEvents() { animationOrder.clear(); battleList.clear(); movesList.clear(); menuEventList.clear(); cursorMoves.clear(); };

	void setActiveMenu(MenuVisualData menu) { menuIsActive = true; activeMenu = menu; };
	MenuVisualData getActiveMenu() { return activeMenu; };
	void deActivateMenu() { menuIsActive = false; };
	bool isMenuActive() { return menuIsActive; };
	void setOngoingMove(mStageVisualData onMove) { ongoingMoveData = onMove; isMoving = true; };
	mStageVisualData getOngoingMove() { return ongoingMoveData; };
	bool isCursorVisible() { return cursorVisible; };
	void setCursorVisibility(bool vis) { cursorVisible = vis; };
	void setCursorPos(MapCoord mapPos) { cursorPos = mapPos; };
	MapCoord getCursorPos() { return cursorPos; };
	bool isMoveInitiated() { return isMoving; };
	void setMoveInitiation(bool trflse) { isMoving = trflse; };
	int getID() { return ID; };
};