#pragma once
#include "StructuredEvent.h"
#include "bStageVisualData.h"

class BattleEvent : public StructuredEvent
{
private:
	BattleVisualData visualData;

public:
	BattleEvent() {};
	BattleEvent(int layer, BattleVisualData data) : StructuredEvent(layer) { visualData = data; };

	StructuredEvent* clone() const override { return new BattleEvent(*this); };
	StructuredEvent* allocateNew() const override { return new BattleEvent(); };

	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;

	BattleVisualData getVisualData() { return visualData; };
};