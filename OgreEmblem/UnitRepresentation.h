#pragma once
#include "ProfessionID.h"
#include "GraphicsUtils.h"

class UnitRepresentation
{
private:

public:
	UnitRepresentation() {};
	UnitRepresentation(int id, ProfessionTag prof, bool dead) { unitID = id; profession = prof; isDead = dead; };

	int unitID = -1;
	bool isDead = false;
	ProfessionTag profession = ProfessionTag::enumProfNone;
	UTIL::ScreenCoord position;
};