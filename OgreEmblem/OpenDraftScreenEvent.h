#pragma once
#include "StructuredEvent.h"

class OpenDraftScreenEvent : public StructuredEvent
{
private:

public:
	OpenDraftScreenEvent() {};
	OpenDraftScreenEvent(int level) : StructuredEvent(level) {};

	StructuredEvent* clone() const override { return new OpenDraftScreenEvent(*this); };
	StructuredEvent* allocateNew() const override { return new OpenDraftScreenEvent(); };

	void applyToBaseLayer(BaseLayer* layer) override;
};