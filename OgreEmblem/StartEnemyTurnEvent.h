#pragma once
#include "StructuredEvent.h"

class StartEnemyTurnEvent : public StructuredEvent
{
private:

public:
	StartEnemyTurnEvent() {};
	StartEnemyTurnEvent(int layer) : StructuredEvent(layer) {};

	StructuredEvent* clone() const override { return new StartEnemyTurnEvent(*this); };
	StructuredEvent* allocateNew() const override { return new StartEnemyTurnEvent(); };

	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
};