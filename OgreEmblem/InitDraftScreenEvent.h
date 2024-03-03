#pragma once
#include "StructuredEvent.h"
#include "SquadData.h"
#include "Unit.h"
class InitDraftScreenEvent : public StructuredEvent
{
private:
	std::vector<Squad> squadData;
	std::vector<UnitData> unitData;
public:
	InitDraftScreenEvent() {};
	InitDraftScreenEvent(int layer, std::vector<Squad> sqdData, std::vector<UnitData> untData);

	StructuredEvent* clone() const override { return new InitDraftScreenEvent(*this);	};
	StructuredEvent* allocateNew() const override { return new InitDraftScreenEvent(); };

	void applyToDraftScreenLayer(DraftScreenLayer* layer) override;
};