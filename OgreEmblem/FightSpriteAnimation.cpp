#include "FightSpriteAnimation.h"


void FightSpriteAnimation::start()
{
	started = true;
	startTime = (double)std::clock();
	step = 0;

	setupStart();
}

void FightSpriteAnimation::progress()
{
	if (started)
	{
		currentTime = ((double)std::clock() - startTime) / (double)CLOCKS_PER_SEC;
		progressInternal();
	}
}