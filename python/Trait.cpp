#include "Trait.h"
#include "TraitTag.h"
#include "AllBoons.h"
#include "AllActions.h"
#include "ActionSetup.h"
#include "Unit.h"

Trait::~Trait()
{
	unsigned int i;
	for (i = 0; i < boons.size(); i++)
	{
		delete boons.at(i);
	}
	for (i = 0; i < actions.size(); i++)
	{
		delete actions.at(i);
	}
	for (i = 0; i < reactions.size(); i++)
	{
		delete reactions.at(i);
	}
}

Trait::Trait(const Trait& cP)
{
	tag = cP.tag;
	unsigned int i;
	for (i = 0; i < cP.boons.size(); i++)
	{
		boons.push_back(cP.boons.at(i)->clone());
	}
	for (i = 0; i < cP.actions.size(); i++)
	{
		actions.push_back(cP.actions.at(i)->clone());
	}
	for (i = 0; i < cP.reactions.size(); i++)
	{
		reactions.push_back(cP.reactions.at(i)->clone());
	}
}

Trait& Trait::operator=(const Trait cP)
{
	tag = cP.tag;
	unsigned int i;
	for (i = 0; i < cP.boons.size(); i++)
	{
		boons.push_back(cP.boons.at(i)->clone());
	}
	for (i = 0; i < cP.actions.size(); i++)
	{
		actions.push_back(cP.actions.at(i)->clone());
	}
	for (i = 0; i < cP.reactions.size(); i++)
	{
		reactions.push_back(cP.reactions.at(i)->clone());
	}

	return *this;
}

void Trait::applyToActionSetup(ActionSetup* actionSetup)
{
	unsigned int i;
	for (i = 0; i < boons.size(); i++)
	{
		actionSetup->addBoon(boons.at(i));
	}
	for (i = 0; i < reactions.size(); i++)
	{
		actionSetup->addReAction(reactions.at(i));
	}
	for (i = 0; i < actions.size(); i++)
	{
		actionSetup->addAction(actions.at(i));
	}
}

Trait::Trait(TraitTag tTag)
{
	tag = tTag;
	switch (tTag)
	{
	case enumBlastTrait:
		actions.push_back(new Blast());
		break;
	case enumFencingDrill:
		reactions.push_back(new Riposte());
		break;
	case enumLightningStrikeTrait:
		actions.push_back(new LightningStrike());
		break;
	case enumMartyrTrait:
		reactions.push_back(new Martyr());
		break;
	case enumDummyTrait:

		break;
	case enumGiantStrength:
		boons.push_back(new GiantStrength());
		break;
	case enumShieldBearer:
		boons.push_back(new ShieldBearer());
		break;
	case enumHeavyArmor:
		boons.push_back(new HeavyArmor());
		break;
	case enumRage:
		reactions.push_back(new Rage());
		break;
	case enumAttached:
		boons.push_back(new Attached());
		break;
case enumHejsan:
		boons.push_back(new Hejsan());
		break;
	case enumHejsan:
		boons.push_back(new Hejsan());
		break;
	//python-entry TraitConstructor
	default:
		throw new std::exception();
	}
}
Trait::Trait(TraitTag tTag, int utilityInt)
{
	tag = tTag;
	switch (tTag)
	{
	case enumWarriorProfTrait:
		boons.push_back(new IncreaseWepProfBoon(BoonTag::enumIncreaseWepProfBoon_WarriorProf, utilityInt));
		actions.push_back(new Strike());
		break;
	case enumHeroProfTrait:
		boons.push_back(new IncreaseWepProfBoon(BoonTag::enumIncreaseWepProfBoon_HeroProf, utilityInt));
		actions.push_back(new Strike());
		break;
	case enumWizardProfTrait:
		boons.push_back(new IncreaseWepProfBoon(BoonTag::enumIncreaseWepProfBoon_WizardProf, utilityInt));
		actions.push_back(new LightningStrike());
		break;
	default:
		throw new std::exception();
	}
}

/*MajorTrait* getMajorTraitByTag(TraitTag tag)
{
	switch (tag)
	{
	case enumBlastTrait:
		return new Blast_Trait();
		break;
	case enumFencingDrill:
		return new FencingDrill();
		break;
	case enumLightningStrikeTrait:
		return new LightningStrike_Trait();
		break;
	case enumMartyrTrait:
		return new Martyr_Trait();
		break;
	case enumDummyTrait:
		return new DummyMajorTrait();
		break;
	default:
		throw new std::exception();
		return new FencingDrill();
	}
}

LesserTrait* getLesserTraitByTag(TraitTag tag)
{
	switch (tag)
	{
	case enumDummyTrait:
		return new DummyLesserTrait();
		break;
	case enumGiantStrength:
		return new GiantStrength_Trait();
		break;
	case enumShieldBearer:
		return new ShieldBearer_Trait();
		break;
	case enumHeavyArmor:
		return new HeavyArmor_Trait();
		break;
	case enumRage:
		return new Rage_Trait();
		break;
	case enumAttached:
		return new Attached_Trait();
		break;
		//python-entry getLesserTraitByTag
	default:
		throw new std::exception();
		return new DummyLesserTrait();
	}
}*/