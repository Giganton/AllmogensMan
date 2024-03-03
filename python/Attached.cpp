#include "Attached.h"
#include "ReactionStage.h"
#include "Fight.h"
#include "Unit.h"
#include "FightResults.h"

Attached::Attached()
{
	tag = BoonTag::enumAttached;
	traitTag = TraitTag::enumAttached;
}
