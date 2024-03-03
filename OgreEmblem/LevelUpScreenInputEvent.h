#pragma once
#include "StructuredEvent.h"

enum class LevelUpScreenEvent { None , MoveCursorLeft , MoveCursorRight , AcceptTrait };

class LevelUpScreenInputEvent : public StructuredEvent
{
private:
	LevelUpScreenEvent happening = LevelUpScreenEvent::None;
public:
	LevelUpScreenInputEvent() {};
	LevelUpScreenInputEvent(int level, LevelUpScreenEvent evnt) :StructuredEvent(level) { happening = evnt; };

	StructuredEvent* clone() const override { return new LevelUpScreenInputEvent(*this); };
	StructuredEvent* allocateNew() const override { return new LevelUpScreenInputEvent(); };

	LevelUpScreenEvent getHappening() { return happening; };
	void applyToLevelUpScreenLayer(LevelUpScreenLayer* layer) override;
};