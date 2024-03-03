#pragma once
#include "StructuredEvent.h"
#include "MapCoord.h"

class MovementTargetCrossEvent : public StructuredEvent
{
private:
public:
	MovementTargetCrossEvent();
	MovementTargetCrossEvent(MapCoord crd);
	MovementTargetCrossEvent(int level);
	MovementTargetCrossEvent(int level, MapCoord crd);

	StructuredEvent* clone() const override { return new MovementTargetCrossEvent(*this); };
	StructuredEvent* allocateNew() const override { return new MovementTargetCrossEvent(); };

	bool putDown = false;
	MapCoord coord;

	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
};