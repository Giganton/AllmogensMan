#include "AllTraits.h"
#include "ActionSetup.h"

void Martyr_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addReAction(createReAction(ActionTag::Martyr));
}

void FencingDrill::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addReAction(createReAction(ActionTag::Riposte));
}

void Rage_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addReAction(createReAction(ActionTag::Rage));
}

void LightningStrike_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::LightningStrike));
}

void Blast_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::Blast));
}

void GiantStrength_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumGiantStrength));
}

void ShieldBearer_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumShieldBearer));
}

void HeavyArmor_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumHeavyArmor));
}

void Strike_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::Strike));
}

void Warrior_ProfTrait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::Strike));
	actionSetup->addBoon(createBoon(BoonTag::enumIncreaseWepProfBoon_WarriorProf, baseWP));
}

void Hero_ProfTrait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::Strike));
	actionSetup->addBoon(createBoon(BoonTag::enumIncreaseWepProfBoon_HeroProf, baseWP));
}

void Wizard_ProfTrait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::Strike));
	actionSetup->addBoon(createBoon(BoonTag::enumIncreaseWepProfBoon_WizardProf, baseWP));
}

void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addAction(createAction(ActionTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
void Attached_Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	actionSetup->addBoon(createBoon(BoonTag::enumAttached));
}
//python-entry AllTraits.cpp