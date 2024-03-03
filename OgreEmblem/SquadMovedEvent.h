#pragma once
#include "StructuredEvent.h"
#include "MovementStage.h"

class SquadMovedEvent : public StructuredEvent
{
private:
	MoveData moveData;

public:
	SquadMovedEvent() {};
	SquadMovedEvent(int level, MoveData mData);

	StructuredEvent* clone() const override { return new SquadMovedEvent(*this); };
	StructuredEvent* allocateNew() const override { return new SquadMovedEvent(); };

	MoveData getMoveData() { return moveData; };

	virtual void applyToMapAnimationLayer(MapAnimationLayer* layer);
};