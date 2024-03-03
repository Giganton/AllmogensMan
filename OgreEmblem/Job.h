#pragma once
#include "JobTag.h"
#include "Trait.h";

class Job
{
protected:
	Trait jobTrait;
	//MajorTrait* jobTrait = nullptr;
	JobTag tag = JobTag::none;
public:
	Job() {};
	JobTag getTag() { return tag; };

	virtual Job* clone() const = 0;
	virtual Job* allocateNew() const = 0;

	Trait getJobTrait() { return jobTrait; };
	Trait* getJobTraitPtr() { return &jobTrait; };
};