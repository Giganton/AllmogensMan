#pragma once
#include "Graphics.h"
#include "StructuredEvent.h"

class MapEvent : public StructuredEvent
{
protected:

public:
	MapEvent() {};
	MapEvent(int layer) : StructuredEvent(layer) {};

	//void actUponAnimationLayer(AnimationLayer* layer) override;
	//void findBaseLayer(Graphics* graphics) { graphics->applyMapEvent(this); };
};