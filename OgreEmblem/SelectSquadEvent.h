#pragma once
#include "StructuredEvent.h"
#include "MouseSignal.h"
#include "Squad.h"

class DraftScreenLayer;

class SelectSquadEvent : public StructuredEvent
{
private:
	MouseSignal clickedSquadSignal;
	Squad clickedSquad;

	bool signalEvent = false;

	bool windowOne = true;
	bool deselect = false;

	bool emptySquad = false;

public:
	SelectSquadEvent() {};
	SelectSquadEvent(int layer, MouseSignal squad, bool isForOne); //select unit
	SelectSquadEvent(int layer, Squad squad, bool isForOne); //select unit
	SelectSquadEvent(int layer, bool isForOne); //deselect unit
	SelectSquadEvent(int layer); //seoect empty unit

	StructuredEvent* clone() const override { return new SelectSquadEvent(*this); };
	StructuredEvent* allocateNew() const override { return new SelectSquadEvent(); };

	bool isForWindowOne() { return windowOne; };
	bool isEmptySquad() { return emptySquad; };

	void applyToDraftScreenLayer(DraftScreenLayer* layer) override;
};