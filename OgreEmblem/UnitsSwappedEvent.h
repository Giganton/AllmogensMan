#pragma once
#include "StructuredEvent.h"
#include "Squad.h"

class DraftScreenLayer;

class UnitsSwappedEvent : public StructuredEvent
{
private:
	bool internalSwap = false;
	Squad squad1;
	Squad squad2;

public:
	UnitsSwappedEvent() {};
	UnitsSwappedEvent(int layer, Squad sqd); 
	UnitsSwappedEvent(int layer, Squad sqd1, Squad sqd2); 

	StructuredEvent* clone() const override { return new UnitsSwappedEvent(*this); };
	StructuredEvent* allocateNew() const override { return new UnitsSwappedEvent(); };

	void applyToDraftScreenLayer(DraftScreenLayer* layer) override;
};