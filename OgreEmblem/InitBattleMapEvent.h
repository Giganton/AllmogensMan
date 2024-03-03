#pragma once
#include "MapEvent.h"
#include "BattleMapVisualData.h"

class InitBattleMapEvent : public StructuredEvent
{
private:
	BattleMapVisualData mapData;
	std::vector<SquadData> squadData;
	CursorPos cursorStart;

public:
	InitBattleMapEvent() {};
	InitBattleMapEvent(int layer, BattleMapVisualData mapData, std::vector<SquadData> sqdData, CursorPos cPos);

	StructuredEvent* clone() const override;
	StructuredEvent* allocateNew() const override { return new InitBattleMapEvent(); };

	//void actUponMapAnimationLayer(MapAnimationLayer* animLayer) override;
	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;

	BattleMapVisualData getMapData() { return mapData; };
	std::vector<SquadData> getSquadData() { return squadData; };
	CursorPos getCursorPos() { return cursorStart; };
};