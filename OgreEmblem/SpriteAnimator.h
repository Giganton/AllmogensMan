#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GraphicsUtils.h"

class SpriteAnimator
{
private:
	UTIL::ScreenCoord spriteSize;
	float stepTime = -1;
	int maxStep = -1;
	int currentStep = -1;

	bool initialized = false;
	sf::Clock clock;

public:
	SpriteAnimator() {};
	SpriteAnimator(UTIL::ScreenCoord size, float timePerStep, int nrOfSteps);

	void progressAnimation();
	sf::IntRect getTextureRectangle();
	sf::IntRect getFirstFrame();
	void resetAnimation();
};
