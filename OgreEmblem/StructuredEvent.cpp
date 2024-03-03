#include "StructuredEvent.h"
#include "CampMenuLayer.h"
#include "BaseLayer.h"
#include "SquadManagerLayer.h"
#include "MapAnimationLayer.h"
#include "LevelUpScreenLayer.h"
#include "DraftScreenLayer.h"

void CloseSubLayerEvent::applyToBaseLayer(BaseLayer* layer) { layer->closeSubLayer(); }
void CloseSubLayerEvent::applyToCampMenuLayer(CampMenuLayer* layer) { layer->closeSubLayer(); }
void CloseSubLayerEvent::applyToSquadBrowserLayer(SquadBrowserLayer* layer) { layer->closeSubLayer(); }
void CloseSubLayerEvent::applyToEditSquadLayer(EditSquadLayer* layer) { layer->closeSubLayer(); }
void CloseSubLayerEvent::applyToSquadMenuLayer(SquadMenuLayer* layer) { layer->closeSubLayer(); }
void CloseSubLayerEvent::applyToMapAnimationLayer(MapAnimationLayer* layer) { layer->closeSubLayer(); }
void CloseSubLayerEvent::applyToLevelUpScreenLayer(LevelUpScreenLayer* layer) { layer->closeSubLayer(); }
void CloseSubLayerEvent::applyToDraftScreenLayer(DraftScreenLayer* layer) { layer->closeSubLayer(); }


bool CloseSubLayerEvent::tryLayer(AnimationLayer* layer)
{
	return (!layer->isOnHold() && !layer->isSubOnHold());
}


bool StructuredEvent::tryLayer(AnimationLayer* layer) 
{ 
	if (ignoreHolds)
	{
		return true;
	}
	else
	{
		return !layer->isOnHold();
	}
}