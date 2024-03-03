#include "Career.h"
#include "Job.h"
#include "Profession.h"
#include "AllJobs.h"
#include "Trait.h"

/*std::vector<Trait*> convertLesserTraitVector(std::vector<LesserTrait*> lesserTraits)
{
	std::vector<Trait*> retVal;
	unsigned int i;
	for (i = 0; i < lesserTraits.size(); i++)
	{
		retVal.push_back(lesserTraits.at(i));
	}
	return retVal;
}*/

CareerStage::CareerStage()
{
	job = new DummyJob();
	lesserTraitSlots = 3;
}

CareerStage::CareerStage(Job* jb, int slots)
{
	job = jb->clone();
	lesserTraitSlots = slots;
}

//void CareerStage::addLesserTrait(LesserTrait* trait)
void CareerStage::addLesserTrait(Trait trait)
{ 
	if (lesserTraits.size() >= lesserTraitSlots)
	{
		throw new std::exception();
	}

	//lesserTraits.push_back(trait->clone());
	lesserTraits.push_back(trait);
}

CareerStage::~CareerStage()
{
	unsigned int i;
	delete job;
	/*for (i = 0; i < lesserTraits.size(); i++)
	{
		delete(lesserTraits.at(i));
	}*/
}

CareerStage::CareerStage(const CareerStage& cp)
{
	unsigned int i;
	job = cp.job->clone();
	lesserTraitSlots = cp.lesserTraitSlots;
	lesserTraits = cp.lesserTraits;
	/*lesserTraits.clear();

	for (i = 0; i < cp.lesserTraits.size(); i++)
	{
		lesserTraits.push_back(cp.lesserTraits.at(i)->clone());
	}*/
}

CareerStage& CareerStage::operator=(const CareerStage as)
{
	unsigned int i;
	job = as.job->clone();
	lesserTraitSlots = as.lesserTraitSlots;
	lesserTraits = as.lesserTraits;
	/*lesserTraits.clear();

	for (i = 0; i < as.lesserTraits.size(); i++)
	{
		lesserTraits.push_back(as.lesserTraits.at(i)->clone());
	}*/

	return *this;
}

//MajorTrait* CareerStage::getMajorTrait()
Trait CareerStage::getMajorTrait()
{
	return job->getJobTrait();
}

//std::vector<LesserTrait*> CareerStage::getLesserTraits()
std::vector<Trait> CareerStage::getLesserTraits()
{
	/*unsigned int i;
	std::vector<LesserTrait*> retVal;
	for (i = 0; i < lesserTraits.size(); i++)
	{
		retVal.push_back(lesserTraits.at(i)->clone());
	}
	return retVal;*/
	return lesserTraits;
}
std::vector<Trait*> CareerStage::getLesserTraitPtrs()
{
	unsigned int i;
	std::vector<Trait*> retVal;
	for (i = 0; i < lesserTraits.size(); i++)
	{
		retVal.push_back(&lesserTraits.at(i));
	}
	return retVal;
}

Career::Career()
{
	apprenticeStage = CareerStage();
	professionalStage = CareerStage();
	masterStage = CareerStage();
}

Career::Career(Profession* prof)
{
	apprenticeStage = CareerStage(new Fencer(),3);
	professionalStage = CareerStage(new Hero(),3);
	masterStage = CareerStage(new Wizard(),3);
}

Career::Career(Job* appJob, int appSlots, Job* profJob, int profSlots, Job* mastJob, int mastSlots)
{
	apprenticeStage = CareerStage(appJob, appSlots);
	professionalStage = CareerStage(profJob, profSlots);
	masterStage = CareerStage(mastJob, mastSlots);
}

CareerStage* Career::getCareerStagePtr(CareerTierTag tag)
{
	switch (tag)
	{
	case::CareerTierTag::apprentice:
		return &apprenticeStage;
	case CareerTierTag::professional:
		return &professionalStage;
	case CareerTierTag::master:
		return &masterStage;
	default:
		throw new std::exception();
	}
	return nullptr;
}

/*Career::~Career()
{
	delete(apprenticeStage);
	delete(professionalStage);
	delete(masterStage);
}

Career::Career(const Career& cp)
{
	apprenticeStage = cp.apprenticeStage->clone();
	apprenticeSlots = cp.apprenticeSlots;
	apprenticeTraits = cp.apprenticeTraits;

	professionalStage = cp.professionalStage->clone();
	professionalSlots = cp.professionalSlots;
	professionalTraits = cp.professionalTraits;

	masterStage = cp.masterStage->clone();
	masterSlots = cp.masterSlots;
	masterTraits = cp.masterTraits;

	currentTier = cp.currentTier;
	masteredTiers = cp.masteredTiers;
}

Career& Career::operator=(const Career cp)
{
	apprenticeStage = cp.apprenticeStage->clone();
	apprenticeSlots = cp.apprenticeSlots;
	apprenticeTraits = cp.apprenticeTraits;

	professionalStage = cp.professionalStage->clone();
	professionalSlots = cp.professionalSlots;
	professionalTraits = cp.professionalTraits;

	masterStage = cp.masterStage->clone();
	masterSlots = cp.masterSlots;
	masterTraits = cp.masterTraits;

	currentTier = cp.currentTier;
	masteredTiers = cp.masteredTiers;

	return *this;
}*/


//void Career::addLesserTrait(LesserTrait* trait)
void Career::addLesserTrait(Trait trait)
{
	CareerStage* stage = getCareerStagePtr(currentTier);
	stage->addLesserTrait(trait);
	if (stage->getNumberOfLesserTraits() == stage->getNumberOfTraitSlots())
	{
		masterCurrentTier();
	}
}

Job* Career::getJob(CareerTierTag careerStage)
{
	CareerStage* stage = getCareerStagePtr(careerStage);
	return stage->getJob();
}

//MajorTrait* Career::getJobTrait(CareerTierTag careerStage)
Trait Career::getJobTrait(CareerTierTag careerStage)
{
	return getJob(careerStage)->getJobTrait();
}
Trait* Career::getJobTraitPtr(CareerTierTag careerStage)
{
	return getJob(careerStage)->getJobTraitPtr();
}

int Career::getStageSlotNumber(CareerTierTag tag)
{
	CareerStage* stage = getCareerStagePtr(tag);
	return stage->getNumberOfTraitSlots();
}

//std::vector<LesserTrait*> Career::getLesserTraitsOfTier(CareerTierTag tag)
std::vector<Trait> Career::getLesserTraitsOfTier(CareerTierTag tag)
{
	CareerStage* stage = getCareerStagePtr(tag);
	return stage->getLesserTraits();
}

CareerStage Career::getCareerStage(CareerTierTag tag)
{
	return *getCareerStagePtr(tag);
}

bool Career::isTierMastered(CareerTierTag tierTag)
{
	unsigned int i;
	for (i = 0; i < masteredTiers.size(); i++)
	{
		if (masteredTiers.at(i) == tierTag)
		{
			return true;
		}
	}
	return false;
}

bool Career::isCareerDone() 
{ 
	return careerDone; 
}

void Career::masterCurrentTier()
{
	switch (currentTier)
	{
	case CareerTierTag::apprentice:
		masteredTiers.push_back(currentTier);
		currentTier = CareerTierTag::professional;
		break;
	case CareerTierTag::professional:
		masteredTiers.push_back(currentTier);
		currentTier = CareerTierTag::master;
		break;
	case CareerTierTag::master:
		masteredTiers.push_back(currentTier);
		careerDone = true;
		break;
	default:
		throw new std::exception();
		break;
	}
}

//std::vector<Trait*> Career::getAllTraits()
std::vector<Trait> Career::getAllTraits()
{
	//std::vector<Trait*> retVal;
	//std::vector<Trait*> lessTraits = convertLesserTraitVector(apprenticeStage.getLesserTraits());
	std::vector<Trait> retVal;
	std::vector<Trait> lessTraits = apprenticeStage.getLesserTraits();
	retVal.insert(retVal.end(), lessTraits.begin(), lessTraits.end());
	if (isTierMastered(CareerTierTag::apprentice))
	{
		retVal.push_back(apprenticeStage.getJob()->getJobTrait());
	}
	lessTraits = professionalStage.getLesserTraits();
	retVal.insert(retVal.end(), lessTraits.begin(), lessTraits.end());
	if (isTierMastered(CareerTierTag::professional))
	{
		retVal.push_back(professionalStage.getJob()->getJobTrait());
	}
	lessTraits = masterStage.getLesserTraits();
	retVal.insert(retVal.end(), lessTraits.begin(), lessTraits.end());
	if (isTierMastered(CareerTierTag::master))
	{
		retVal.push_back(masterStage.getJob()->getJobTrait());
	}
	return retVal;
}
std::vector<Trait*> Career::getAllTraitPtrs()
{
	//std::vector<Trait*> retVal;
	//std::vector<Trait*> lessTraits = convertLesserTraitVector(apprenticeStage.getLesserTraits());
	std::vector<Trait*> retVal;
	std::vector<Trait*> lessTraits = apprenticeStage.getLesserTraitPtrs();
	retVal.insert(retVal.end(), lessTraits.begin(), lessTraits.end());
	if (isTierMastered(CareerTierTag::apprentice))
	{
		retVal.push_back(apprenticeStage.getJob()->getJobTraitPtr());
	}
	lessTraits = professionalStage.getLesserTraitPtrs();
	retVal.insert(retVal.end(), lessTraits.begin(), lessTraits.end());
	if (isTierMastered(CareerTierTag::professional))
	{
		retVal.push_back(professionalStage.getJob()->getJobTraitPtr());
	}
	lessTraits = masterStage.getLesserTraitPtrs();
	retVal.insert(retVal.end(), lessTraits.begin(), lessTraits.end());
	if (isTierMastered(CareerTierTag::master))
	{
		retVal.push_back(masterStage.getJob()->getJobTraitPtr());
	}
	return retVal;
}