#pragma once
#include "Boon.h"

class Hejsan : public Boon
{
private:

public:
	Hejsan();

	Boon* clone() const override { return new Hejsan(*this); };
	Boon* allocateNew() const override { return new Hejsan(); };

};
