#pragma once
#include "StructuredEvent.h"

class OpenNamePickerEvent : public StructuredEvent
{
private:

public:
	OpenNamePickerEvent() {};
	OpenNamePickerEvent(int level) : StructuredEvent(level) {};

	StructuredEvent* clone() const override { return new OpenNamePickerEvent(*this); };
	StructuredEvent* allocateNew() const override { return new OpenNamePickerEvent(); };

	void applyToDraftScreenLayer(DraftScreenLayer* layer) override;
};