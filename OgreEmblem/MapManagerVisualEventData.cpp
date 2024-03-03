#include "MapManagerVisualEventData.h"

void MapManagerVisualEventData::addQueue(MapManagerVisualEventData addQ)
{
	animationOrder.splice(animationOrder.end(), addQ.getQueueOrder());
	battleList.splice(battleList.end(), addQ.getBattleList());
	movesList.splice(movesList.end(), addQ.getMovementList());
	menuEventList.splice(menuEventList.end(), addQ.getMenuEventList());
	cursorMoves.splice(cursorMoves.end(), addQ.getCursorMovesList());
}