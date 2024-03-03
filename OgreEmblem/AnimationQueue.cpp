#include "AnimationQueue.h"

void AnimationQueue::addQueue(AnimationQueue addQ)
{
	animationOrder.splice(animationOrder.end(), addQ.getQueueOrder());
	battleList.splice(battleList.end(), addQ.getBattleList());
	movesList.splice(movesList.end(), addQ.getMovementList());
}