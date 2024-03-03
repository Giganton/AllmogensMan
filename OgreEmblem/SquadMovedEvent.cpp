#include "SquadMovedEvent.h"
#include "MapAnimationLayer.h"

SquadMovedEvent::SquadMovedEvent(int level, MoveData mData) : StructuredEvent(level)
{
	moveData = mData;
}

void SquadMovedEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{
	layer->applySquadMovedEvent(this);
}