#pragma once
#include "StructuredEvent.h"

class OpenConfirmationEvent : public StructuredEvent
{
private:

public:
	OpenConfirmationEvent() {};
	OpenConfirmationEvent(int level) : StructuredEvent(level) {};

	StructuredEvent* clone() const override { return new OpenConfirmationEvent(*this); };
	StructuredEvent* allocateNew() const override { return new OpenConfirmationEvent(); };

	//void applyToBaseLayer(BaseLayer* layer) override;
	void applyToDraftScreenLayer(DraftScreenLayer* layer) override;
};