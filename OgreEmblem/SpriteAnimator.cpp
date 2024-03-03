#include "SpriteAnimator.h"

SpriteAnimator::SpriteAnimator(UTIL::ScreenCoord size, float timePerStep, int nrOfSteps)
{
	spriteSize = size;
	stepTime = timePerStep;
	maxStep = nrOfSteps;
	clock = sf::Clock();

}


void SpriteAnimator::progressAnimation()
{
	if (!initialized)
	{
		initialized = true;
		clock.restart();
		currentStep = 0;
	}
	else
	{
		if (stepTime > 0 && clock.getElapsedTime().asSeconds() > stepTime)
		{
			clock.restart();
			currentStep = (currentStep + 1) % maxStep;
		}
	}
}

void SpriteAnimator::resetAnimation()
{
	clock.restart();
	currentStep = 0;
}

sf::IntRect SpriteAnimator::getTextureRectangle()
{
	progressAnimation();
	return sf::IntRect((int)(currentStep * spriteSize.x), 0, (int)spriteSize.x, (int)spriteSize.y);
}

sf::IntRect SpriteAnimator::getFirstFrame()
{
	return sf::IntRect(0, 0, (int)spriteSize.x, (int)spriteSize.y);
}