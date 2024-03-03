#pragma once
#include "StructuredEvent.h"
#include<string>

class SquadNamePickerLayer;

class ChangeWordSelectionEvent : public StructuredEvent
{
private:
	int prefixIndex = -1;
	int descriptorIndex = -1;
	int subjectIndex = -1;
	std::string currentWord;
public:
	ChangeWordSelectionEvent() {};
	ChangeWordSelectionEvent(int layer, int prefIndex, int descIndex, int subjIndex, std::string currWord);

	StructuredEvent* clone() const override { return new ChangeWordSelectionEvent(*this); };
	StructuredEvent* allocateNew() const override { return new ChangeWordSelectionEvent(); };

	void applyToSquadNamePickerLayer(SquadNamePickerLayer* layer) override;
};