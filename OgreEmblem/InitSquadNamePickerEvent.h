#pragma once
#include "StructuredEvent.h"
#include<string>

class InitSquadNamePickerEvent : public StructuredEvent
{
private:
	std::vector<std::string> prefixes;
	std::vector<std::string> descriptors;
	std::vector<std::string> subjects;

	std::string currentString;
public:
	InitSquadNamePickerEvent() {};
	InitSquadNamePickerEvent(int layer, std::vector<std::string> prefix, std::vector<std::string> descr, std::vector<std::string> subj, std::string startString);

	StructuredEvent* clone() const override { return new InitSquadNamePickerEvent(*this); };
	StructuredEvent* allocateNew() const override { return new InitSquadNamePickerEvent(); };

	void applyToSquadNamePickerLayer(SquadNamePickerLayer* layer) override;

};