#pragma once
#include "StructuredEvent.h"
#include "MapCoord.h"

class MovementDotsEvent : public StructuredEvent
{
private:
	std::vector<MapCoord> dotSpots;
public:
	MovementDotsEvent() {};
	MovementDotsEvent(std::vector<MapCoord> dots){ dotSpots = dots; };
	MovementDotsEvent(int layer, std::vector<MapCoord> dots) : StructuredEvent(layer) { dotSpots = dots; };

	StructuredEvent* clone() const override { return new MovementDotsEvent(*this); };
	StructuredEvent* allocateNew() const override { return new MovementDotsEvent(); };

	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
	std::vector<MapCoord> getDotPath() { return dotSpots; };
};