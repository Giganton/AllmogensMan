#pragma once
#include "MapEvent.h"
#include "Cursor.h"

enum class MapCursorEventType { none, hide, show, move };

class MapCursorEvent : public StructuredEvent
{
private:
	MapCursorEventType type = MapCursorEventType::none;
	CursorMove moveData;
public:
	MapCursorEvent() {};
	MapCursorEvent(int layer, CursorMove cMove) : StructuredEvent(layer) { moveData = cMove; type = MapCursorEventType::move; };
	MapCursorEvent(int layer, MapCursorEventType eType) : StructuredEvent(layer) { if (eType != MapCursorEventType::hide && eType != MapCursorEventType::show) { throw new std::exception(); } type = eType;	};

	StructuredEvent* clone() const override { return new MapCursorEvent(*this); };
	StructuredEvent* allocateNew() const override { return new MapCursorEvent(); };

	CursorMove getMoveData() { return moveData; };
	MapCursorEventType getType() { return type; };
	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
};