#pragma once
#include "StructuredEvent.h"

class StartPlayerTurnEvent : public StructuredEvent
{
private:

public:
	StartPlayerTurnEvent() {};
	StartPlayerTurnEvent(int layer) : StructuredEvent(layer) {};

	StructuredEvent* clone() const override { return new StartPlayerTurnEvent(*this); };
	StructuredEvent* allocateNew() const override { return new StartPlayerTurnEvent(); };

	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
};