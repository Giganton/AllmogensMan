#pragma once
#include "StructuredEvent.h"

class OpenLevelUpScreenEvent : public StructuredEvent
{
private:

public:
	OpenLevelUpScreenEvent() {};
	OpenLevelUpScreenEvent(int lvl) : StructuredEvent(lvl) { ignoreHolds = true; };

	StructuredEvent* clone() const override { return new OpenLevelUpScreenEvent(*this); };
	StructuredEvent* allocateNew() const override { return new OpenLevelUpScreenEvent(); };

	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
};