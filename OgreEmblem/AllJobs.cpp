#include "AllJobs.h"
#include "TraitTag.h"

Fencer::Fencer()
{
	tag = JobTag::fencer;
	jobTrait = Trait(TraitTag::enumFencingDrill);
}

Hero::Hero()
{
	tag = JobTag::hero;
	jobTrait = Trait(TraitTag::enumMartyrTrait);
}

Wizard::Wizard()
{
	tag = JobTag::wizard;
	jobTrait = Trait(TraitTag::enumLightningStrikeTrait);
}

DummyJob::DummyJob()
{
	tag = JobTag::dummyJob;
	jobTrait = Trait(TraitTag::enumDummyTrait);
}