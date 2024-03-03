#include "ReloadSquadListEvent.h"
#include "DraftScreenLayer.h"


ReloadSquadListEvent::ReloadSquadListEvent(int layer, std::vector<Squad> sqdList) : StructuredEvent(layer)
{
	squadList = sqdList;
}

void ReloadSquadListEvent::applyToDraftScreenLayer(DraftScreenLayer* layer)
{
	layer->reloadSquadList(squadList);
}