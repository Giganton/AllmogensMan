#pragma once
#include "Trait.h"

class Martyr_Trait : public MajorTrait
{
private:

public:
	Martyr_Trait() { tag = TraitTag::enumMartyrTrait; }

	MajorTrait* clone() const override { return new Martyr_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Martyr_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;

};

class FencingDrill : public MajorTrait
{
private:

public:
	FencingDrill() { tag = TraitTag::enumFencingDrill; }

	MajorTrait* clone() const override { return new FencingDrill(*this); };
	MajorTrait* allocateNew() const override { return new FencingDrill(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Rage_Trait : public LesserTrait
{
private:

public:
	Rage_Trait() { tag = TraitTag::enumRage; }

	LesserTrait* clone() const override { return new Rage_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Rage_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class LightningStrike_Trait : public MajorTrait
{
private:

public:
	LightningStrike_Trait() { tag = TraitTag::enumLightningStrikeTrait; }

	MajorTrait* clone() const override { return new LightningStrike_Trait(*this); };
	MajorTrait* allocateNew() const override { return new LightningStrike_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Blast_Trait : public MajorTrait
{
private:

public:
	Blast_Trait() { tag = TraitTag::enumBlastTrait; };

	MajorTrait* clone() const override { return new Blast_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Blast_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class GiantStrength_Trait : public LesserTrait
{
private:

public:
	GiantStrength_Trait() { tag = TraitTag::enumGiantStrength; };

	LesserTrait* clone() const override { return new GiantStrength_Trait(*this); };
	LesserTrait* allocateNew() const override { return new GiantStrength_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class ShieldBearer_Trait : public LesserTrait
{
private:

public:
	ShieldBearer_Trait() { tag = TraitTag::enumShieldBearer; };

	LesserTrait* clone() const override { return new ShieldBearer_Trait(*this); };
	LesserTrait* allocateNew() const override { return new ShieldBearer_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class HeavyArmor_Trait : public LesserTrait
{
private:

public:
	HeavyArmor_Trait() { tag = TraitTag::enumHeavyArmor; };

	LesserTrait* clone() const override { return new HeavyArmor_Trait(*this); };
	LesserTrait* allocateNew() const override { return new HeavyArmor_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Warrior_ProfTrait : public ProfessionTrait
{
private:

public:
	Warrior_ProfTrait() {};
	Warrior_ProfTrait(int WP) { tag = TraitTag::enumWarriorProfTrait; baseWP = WP; };

	ProfessionTrait* clone() const override { return new Warrior_ProfTrait(*this); };
	ProfessionTrait* allocateNew() const override { return new Warrior_ProfTrait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Hero_ProfTrait : public ProfessionTrait
{
private:

public:
	Hero_ProfTrait() {};
	Hero_ProfTrait(int WP) { tag = TraitTag::enumHeroProfTrait; baseWP = WP; };

	ProfessionTrait* clone() const override { return new Hero_ProfTrait(*this); };
	ProfessionTrait* allocateNew() const override { return new Hero_ProfTrait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Wizard_ProfTrait : public ProfessionTrait
{
private:

public:
	Wizard_ProfTrait() {};
	Wizard_ProfTrait(int WP) { tag = TraitTag::enumWizardProfTrait; baseWP = WP; };

	ProfessionTrait* clone() const override { return new Wizard_ProfTrait(*this); };
	ProfessionTrait* allocateNew() const override { return new Wizard_ProfTrait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Strike_Trait : public MajorTrait
{
private:

public:
	Strike_Trait() { tag = TraitTag::enumStrikeTrait; }

	MajorTrait* clone() const override { return new Strike_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Strike_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class DummyMajorTrait : public MajorTrait
{
private:

public:
	DummyMajorTrait() { tag = TraitTag::enumDummyTrait; }

	MajorTrait* clone() const override { return new DummyMajorTrait(*this); };
	MajorTrait* allocateNew() const override { return new DummyMajorTrait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override {};
};

class DummyLesserTrait : public LesserTrait
{
private:

public:
	DummyLesserTrait() { tag = TraitTag::enumDummyTrait; }

	LesserTrait* clone() const override { return new DummyLesserTrait(*this); };
	LesserTrait* allocateNew() const override { return new DummyLesserTrait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override {};
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public MajorTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	MajorTrait* clone() const override { return new Attached_Trait(*this); };
	MajorTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

class Attached_Trait : public LesserTrait
{
private:

public:
	Attached_Trait() { tag = TraitTag::enumAttached; };

	LesserTrait* clone() const override { return new Attached_Trait(*this); };
	LesserTrait* allocateNew() const override { return new Attached_Trait(); };

	void applyToActionSetup(ActionSetup* actionSetup) override;
};

//python-entry AllTraits.h