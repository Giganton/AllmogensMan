#pragma once
#include<vector>
#include "Trait.h"

class Job;
//class LesserTrait;
class MajorTrait;
class Profession;

enum class CareerTierTag { none , apprentice, professional, master };

class CareerStage
{
private:
	Job* job = nullptr;
	int lesserTraitSlots = 0;
	//std::vector<LesserTrait*> lesserTraits;
	std::vector<Trait> lesserTraits;
public:
	CareerStage();
	CareerStage(Job* jb, int slots);

	~CareerStage();
	CareerStage(const CareerStage& cp);
	CareerStage& operator=(const CareerStage as);

	int getNumberOfLesserTraits() { return lesserTraits.size(); };
	//void addLesserTrait(LesserTrait* trait);
	void addLesserTrait(Trait trait);
	int getNumberOfTraitSlots() { return lesserTraitSlots; };
	Job* getJob() { return job; };
	//std::vector<LesserTrait*> getLesserTraits();
	std::vector<Trait> getLesserTraits();
	std::vector<Trait*> getLesserTraitPtrs();
	//MajorTrait* getMajorTrait();
	Trait getMajorTrait();
};

class Career
{
private:
	CareerStage apprenticeStage;
	CareerStage professionalStage;
	CareerStage masterStage;

	CareerTierTag currentTier = CareerTierTag::apprentice;
	std::vector<CareerTierTag> masteredTiers = {};

	CareerStage* getCareerStagePtr(CareerTierTag tag);
	bool careerDone = false;
public:
	Career();
	Career(Profession* prof);
	Career(Job* appJob, int appSlots, Job* profJob, int profSlots, Job* mastJob, int mastSlots);

	//void addLesserTrait(LesserTrait* trait);
	void addLesserTrait(Trait trait);
	void masterCurrentTier();
	bool isCareerDone();
	std::vector<Trait> getAllTraits();
	std::vector<Trait*> getAllTraitPtrs();
	bool isTierMastered(CareerTierTag tierTag);
	Job* getJob(CareerTierTag careerStage);

	//MajorTrait* getJobTrait(CareerTierTag careerStage);
	Trait getJobTrait(CareerTierTag careerStage);
	Trait* getJobTraitPtr(CareerTierTag careerStage);
	int getStageSlotNumber(CareerTierTag tag);
	//std::vector<LesserTrait*> getLesserTraitsOfTier(CareerTierTag tag);
	std::vector<Trait> getLesserTraitsOfTier(CareerTierTag tag);

	CareerStage getCareerStage(CareerTierTag tag);
};