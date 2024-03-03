#pragma once
#include "Boon.h"

class Attached : public Boon
{
private:

public:
	Attached();

	Boon* clone() const override { return new Attached(*this); };
	Boon* allocateNew() const override { return new Attached(); };

};
