#include "Profession.h"
#include "TraitTag.h"
#include "Trait.h"

Profession::Profession(ProfessionTag pTag)
{
	tag = pTag;
	switch (pTag)
	{
	case ProfessionTag::enumWarrior:
		initWarrior();
		break;
	case ProfessionTag::enumWizard:
		initWizard();
		break;
	case ProfessionTag::enumHero:
		initHero();
		break;
	}
}

Profession::Profession(ProfessionTag pTag, int WP) : Profession(pTag)
{
	baseWP = WP;
	//delete profTrait;
	setProfTrait();
}

/*Profession::~Profession()
{
	if (profTrait != nullptr)
	{
		delete profTrait;
	}
}
Profession::Profession(const Profession& cpEQ)
{
	tag = cpEQ.tag;
	battleTextureFile = cpEQ.battleTextureFile;
	mapTextureFile = cpEQ.mapTextureFile;
	name = cpEQ.name;
	

	profTrait = cpEQ.profTrait->clone();
	baseWP = cpEQ.baseWP;
	traitPool = cpEQ.traitPool;
}
Profession& Profession::operator=(const Profession cpEQ)
{
	tag = cpEQ.tag;
	battleTextureFile = cpEQ.battleTextureFile;
	mapTextureFile = cpEQ.mapTextureFile;
	name = cpEQ.name;

	profTrait = cpEQ.profTrait->clone();
	baseWP = cpEQ.baseWP;
	traitPool = cpEQ.traitPool;

	return *this;
}*/

void Profession::setProfTrait()
{
	switch (tag)
	{
	case ProfessionTag::enumWarrior:
		//profTrait = new Warrior_ProfTrait(baseWP);
		profTrait = Trait(TraitTag::enumWarriorProfTrait, baseWP);
		break;
	case ProfessionTag::enumWizard:
		//profTrait = new Wizard_ProfTrait(baseWP);
		profTrait = Trait(TraitTag::enumWizardProfTrait, baseWP);
		break;
	case ProfessionTag::enumHero:
		//profTrait = new Hero_ProfTrait(baseWP);
		profTrait = Trait(TraitTag::enumHeroProfTrait, baseWP);
		break;
	default:
		throw new std::exception();
	}
}

void Profession::setBaseWP()
{
	switch (tag)
	{
	case ProfessionTag::enumWarrior:
		baseWP = 5;
		break;
	case ProfessionTag::enumWizard:
		baseWP = 1;
		break;
	case ProfessionTag::enumHero:
		baseWP = 3;
		break;
	default:
		throw new std::exception();
	}
}

void Profession::setBaseWP(int WP)
{
	baseWP = WP;
}

void Profession::initWarrior()
{
	battleTextureFile = "textures\\knekt.png";
	mapTextureFile = "textures\\map\\krigare_anim.png";
	name = "Warrior";
	setBaseWP();
	setProfTrait();
	traitPool = { enumDummyTrait };
}

void Profession::initWizard()
{
	battleTextureFile = "textures\\wizard.png";
	mapTextureFile = "textures\\map\\krigare_anim.png";
	name = "Wizard";
	setBaseWP();
	setProfTrait();
	traitPool = { enumDummyTrait };
}

void Profession::initHero()
{
	battleTextureFile = "textures\\knekt.png";
	mapTextureFile = "textures\\map\\hero_anim.png";
	name = "Hero";
	setBaseWP();
	setProfTrait();
	traitPool = { TraitTag::enumGiantStrength };
}

Trait Profession::getProfTrait()
{
	return profTrait;
}
Trait* Profession::getProfTraitPtr()
{
	return &profTrait;
}