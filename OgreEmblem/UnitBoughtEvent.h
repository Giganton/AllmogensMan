#pragma once
#include "StructuredEvent.h"
#include "Squad.h"

class DraftScreenLayer;

class UnitBoughtEvent : public StructuredEvent
{
private:
	int boughtUnitID = -1;
	Squad squad;

public:
	UnitBoughtEvent() {};
	UnitBoughtEvent(int layer, Squad sqd, int unitID);

	StructuredEvent* clone() const override { return new UnitBoughtEvent(*this); };
	StructuredEvent* allocateNew() const override { return new UnitBoughtEvent(); };

	void applyToDraftScreenLayer(DraftScreenLayer* layer) override;
};