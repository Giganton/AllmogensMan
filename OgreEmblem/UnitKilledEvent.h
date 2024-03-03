#pragma once
#include "StructuredEvent.h"

class UnitKilledEvent : public StructuredEvent
{
private:
	int squadID = -1;
	int unitID = -1;
public:
	UnitKilledEvent() {};
	UnitKilledEvent(int level, int sID, int uID) : StructuredEvent(level) { squadID = sID; unitID = uID; };

	StructuredEvent* clone() const override { return new UnitKilledEvent(*this); };
	StructuredEvent* allocateNew() const override { return new UnitKilledEvent(); };

	int getSquadID() { return squadID; };
	int getUnitID() { return unitID; };

	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
};