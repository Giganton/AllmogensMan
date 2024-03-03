#pragma once
#include "StructuredEvent.h"
#include "MouseSignal.h"

class DraftScreenLayer;

class SelectUnitEvent : public StructuredEvent
{
private:
	MouseSignal clickedUnit;
	bool deselect = false;

public:
	SelectUnitEvent() {};
	SelectUnitEvent(int layer, MouseSignal unit); //select unit
	SelectUnitEvent(int layer); //deselect unit

	StructuredEvent* clone() const override { return new SelectUnitEvent(*this); };
	StructuredEvent* allocateNew() const override { return new SelectUnitEvent(); };

	void applyToDraftScreenLayer(DraftScreenLayer* layer) override;
};