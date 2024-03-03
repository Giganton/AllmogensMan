#include "InitBattleMapEvent.h"
#include "MapAnimationLayer.h"

InitBattleMapEvent::InitBattleMapEvent(int layer, BattleMapVisualData mpData, std::vector<SquadData> sqdData,CursorPos cPos) : StructuredEvent(layer)
{
	mapData = mpData;
	squadData = sqdData;
	cursorStart = cPos;
}

StructuredEvent* InitBattleMapEvent::clone() const 
{ 
	return new InitBattleMapEvent(*this); 
};

void InitBattleMapEvent::applyToMapAnimationLayer(MapAnimationLayer* animLayer)
{
	animLayer->applyInitBattleMapEvent(this);
}