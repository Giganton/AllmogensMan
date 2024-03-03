#pragma once
#include "BattleMapVisualData.h"
#include "StructuredEvent.h"

class BaseLayer;

class OpenBattleMapEvent : public StructuredEvent
{
private:
	bool copyBattleField = false;
public:
	OpenBattleMapEvent() {};
	OpenBattleMapEvent(int lvl) : StructuredEvent(lvl) { ignoreHolds = true; };
	OpenBattleMapEvent(int lvl, bool makeCopyOfBattleField) : StructuredEvent(lvl) { copyBattleField = makeCopyOfBattleField; ignoreHolds = true; };

	StructuredEvent* clone() const override { return new OpenBattleMapEvent(*this); };
	StructuredEvent* allocateNew() const override { return new OpenBattleMapEvent(); };

	void applyToBaseLayer(BaseLayer* layer) override;
	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
};