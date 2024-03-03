#pragma once
#include "StructuredEvent.h"

class VictoryAchievedEvent : public StructuredEvent
{
private:

public:
	VictoryAchievedEvent() {};
	VictoryAchievedEvent(int level) : StructuredEvent(level) { };

	StructuredEvent* clone() const override { return new VictoryAchievedEvent(*this); };
	StructuredEvent* allocateNew() const override { return new VictoryAchievedEvent(); };

	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
};