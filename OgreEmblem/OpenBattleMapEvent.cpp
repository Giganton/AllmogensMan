#include "OpenBattleMapEvent.h"
#include "BaseLayer.h"
#include "MapAnimationLayer.h"

void OpenBattleMapEvent::applyToBaseLayer(BaseLayer* layer)
{
	layer->openMapAnimationLayer();
}

void OpenBattleMapEvent::applyToMapAnimationLayer(MapAnimationLayer* layer)
{
	layer->openMapAnimationLayer(copyBattleField);
}