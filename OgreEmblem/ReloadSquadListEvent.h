#pragma once
#include "StructuredEvent.h"
#include "Squad.h"

class DraftScreenLayer;

class ReloadSquadListEvent : public StructuredEvent
{
private:
	std::vector<Squad> squadList;
public:
	ReloadSquadListEvent() {};
	ReloadSquadListEvent(int layer, std::vector<Squad> sqdList);

	StructuredEvent* clone() const override { return new ReloadSquadListEvent(*this); };
	StructuredEvent* allocateNew() const override { return new ReloadSquadListEvent(); };

	void applyToDraftScreenLayer(DraftScreenLayer* layer) override;
};