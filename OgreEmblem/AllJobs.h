#pragma once
#include "Job.h"

class Fencer : public Job
{
private:

public:
	Fencer();

	Job* clone() const override { return new Fencer(*this); };
	Job* allocateNew() const override { return new Fencer(); };
};

class Hero : public Job
{
private:

public:
	Hero();

	Job* clone() const override { return new Hero(*this); };
	Job* allocateNew() const override { return new Hero(); };
};

class Wizard : public Job
{
private:

public:
	Wizard();

	Job* clone() const override { return new Wizard(*this); };
	Job* allocateNew() const override { return new Wizard(); };
};

class DummyJob : public Job
{
private:

public:
	DummyJob();

	Job* clone() const override { return new DummyJob(*this); };
	Job* allocateNew() const override { return new DummyJob(); };
};