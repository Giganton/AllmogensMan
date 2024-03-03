#include "InitDraftScreenEvent.h"
#include "DraftScreenLayer.h"

InitDraftScreenEvent::InitDraftScreenEvent(int layer, std::vector<Squad> sqdData, std::vector<UnitData> untData) : StructuredEvent(layer)
{
	squadData = sqdData;
	unitData = untData;
}

void InitDraftScreenEvent::applyToDraftScreenLayer(DraftScreenLayer* layer)
{
	layer->initDraftScreen(squadData, unitData);
}