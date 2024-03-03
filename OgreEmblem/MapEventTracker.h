#pragma once
#include<list>
#include "AnimationType.h"
#include "bStageVisualData.h"
#include "mStageVisualData.h"

class MapEventTracker
{
	std::list<AnimationType> animationOrder;
	std::list<bStageVisualData> battleList;
	std::list<mStageVisualData> movesList;
};