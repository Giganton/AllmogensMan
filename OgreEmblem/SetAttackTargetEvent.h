#pragma once
#include "MapEvent.h"

class SetAttackTargetEvent : public StructuredEvent
{
private:
	int targetID = -1;
public:
	SetAttackTargetEvent() {};
	SetAttackTargetEvent(int layer, int ID) : StructuredEvent(layer) { targetID = ID; };

	StructuredEvent* clone() const override { return new SetAttackTargetEvent(*this); };
	StructuredEvent* allocateNew() const override { return new SetAttackTargetEvent(); };

	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
	int getTargetID() { return targetID; };
};