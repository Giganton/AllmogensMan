#pragma once
#include "BoonTags.h"
#include "Triggerable.h"

class Boon : public Triggerable
{
protected:
	BoonTag tag = BoonTag::none;
public:
	Boon() {};

	virtual Boon* clone() const = 0;
	virtual Boon* allocateNew() const = 0;
};

Boon* createBoon(BoonTag tag);
Boon* createBoon(BoonTag tag, int utilityInt);