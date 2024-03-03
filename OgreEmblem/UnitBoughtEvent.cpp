#include "UnitBoughtEvent.h"
#include "DraftScreenLayer.h"


UnitBoughtEvent::UnitBoughtEvent(int layer, Squad sqd, int unitID) : StructuredEvent(layer)
{
	squad = sqd;
	boughtUnitID = unitID;
}

void UnitBoughtEvent::applyToDraftScreenLayer(DraftScreenLayer* layer)
{
	layer->reloadSquad(squad);
	layer->buyOutUnit(boughtUnitID);
}