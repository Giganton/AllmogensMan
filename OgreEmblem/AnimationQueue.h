#pragma once
#include<list>
#include "AnimationType.h"
#include "bStageVisualData.h"
#include "mStageVisualData.h"

class AnimationQueue
{
private:

	std::list<AnimationType> animationOrder;
	std::list<BattleVisualData> battleList;
	std::list<mStageVisualData> movesList;

public:
	AnimationQueue() {};
	bool isEmpty() { return animationOrder.size() == 0; };
	void addBattle(BattleVisualData battle) { battleList.push_back(battle); animationOrder.push_back(AnimationType::battle); };
	void addMovement(mStageVisualData move) { movesList.push_back(move); animationOrder.push_back(AnimationType::movement); };
	void addQueue(AnimationQueue addQ);

	std::list<BattleVisualData> getBattleList() { return battleList; };
	std::list<mStageVisualData> getMovementList() { return movesList; };
	std::list<AnimationType> getQueueOrder() { return animationOrder; };

	AnimationType pullLatestAnimationType() { AnimationType retVal = animationOrder.front(); animationOrder.pop_front(); return retVal; };
	BattleVisualData pullBattle() { BattleVisualData retVal = battleList.front(); battleList.pop_front(); return retVal; };
	mStageVisualData pullMovement() { mStageVisualData retVal = movesList.front(); movesList.pop_front(); return retVal; };

	void clear() { animationOrder.clear(); battleList.clear(); movesList.clear(); };
};