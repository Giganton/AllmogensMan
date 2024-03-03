#include "MapOverlayAnimation.h"
#include <ctime>


MapOverlayAnimation::MapOverlayAnimation(int lvl, MapOverlayPackage* overlayPackage, sf::RenderWindow* ww)
{
	mapOverlayPackage = overlayPackage;
	window = ww;
	level = lvl;
}

void MapOverlayAnimation::progress()
{
	switch (currentlyRunningAnimation)
	{
	case OverlayAnimationType::none:
		break;
	case OverlayAnimationType::Victory:
		progressVictoryAnimation();
		break;
	default:
		throw new std::exception();
	}
}

sf::RectangleShape MapOverlayAnimation::produceFadeSprite()
{
	sf::Vector2f size(window->getSize().x, window->getSize().y);
	sf::RectangleShape retVal = sf::RectangleShape(size);
	retVal.setFillColor(sf::Color::Black);
	
	return retVal;
}

sf::Sprite MapOverlayAnimation::produceVictorySprite()
{
	sf::Sprite retVal;
	sf::Vector2f mapPos;

	retVal.setTexture(mapOverlayPackage->victoryBanner);
	mapPos.x = window->getSize().x / 2 - retVal.getTextureRect().width / 2;
	mapPos.y = window->getSize().y / 2 - retVal.getTextureRect().height / 2;
	retVal.setPosition(mapPos);

	return retVal;
}

std::vector<AnimationSignal> MapOverlayAnimation::retrieveSignals()
{
	std::vector<AnimationSignal> retVal = waitingSignals;
	waitingSignals.clear();
	return retVal;
}

void MapOverlayAnimation::progressVictoryAnimation()
{
	double fadeInDuration = 1.2;
	double fadeInDelay = 2;
	double holdDuration = 0.2;
	double fadeToBlackDuration = 3;
	double holdBlackDuration = 2;
	double fadePercent;
	double time = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
	sf::Sprite bannerSprite = produceVictorySprite();


	switch (step)
	{
	case 0:
		startTime = (double)std::clock();
		step = 1;
		break;

	case 1:
		drawRect = true;
		overlayRectangle = produceFadeSprite();
		fadePercent = (time / fadeToBlackDuration)*0.7;
		overlayRectangle.setFillColor(sf::Color(0, 0, 0, 255 * fadePercent));

		if (time > fadeToBlackDuration)
		{
			step = 4;
			startTime = (double)std::clock();
		}
		
		if (time > fadeInDelay)
		{
			fadePercent = ((time - fadeInDelay) / fadeInDuration);
			if (fadePercent > 1)
			{
				fadePercent = 1;
			}
			bannerSprite.setColor(sf::Color(255, 255, 255, 255 * fadePercent));
			spriteVector.push_back(bannerSprite);
		}

		break;
	case 2:
		if (time > holdDuration)
		{
			step = 3;
			startTime = (double)std::clock();
		}
		spriteVector.push_back(bannerSprite);

		break;
	case 3:
		drawRect = true;
		overlayRectangle = produceFadeSprite();
		fadePercent = (time / fadeToBlackDuration);
		overlayRectangle.setFillColor(sf::Color(0, 0, 0, 255 * fadePercent));
		spriteVector.push_back(bannerSprite);
		if (time > fadeToBlackDuration)
		{
			step = 4;
		}
		break;
	case 4:
		drawRect = true;
		overlayRectangle = produceFadeSprite();
		overlayRectangle.setFillColor(sf::Color(0, 0, 0, 255*0.7));
		spriteVector.push_back(bannerSprite);
		if (time > holdBlackDuration)
		{
			step = 5;
		}
		break;
	case 5:
		drawRect = false;
		animationFinished();
		break;
	default:
		throw new std::exception();
	}
}

void MapOverlayAnimation::animationFinished()
{
	switch (currentlyRunningAnimation)
	{
	case OverlayAnimationType::Victory:
		waitingSignals.push_back(AnimationSignal(level, SignalType::animationDone, SignalSubType::Victory));
		break;
	default:
		throw new std::exception();
	}
	if (animQueue.size() > 0)
	{
		startAnimation(animQueue.at(0));
		animQueue.erase(animQueue.begin());
	}
	else
	{
		currentlyRunningAnimation = OverlayAnimationType::none;
	}
}

void MapOverlayAnimation::draw()
{
	unsigned int i;

	progress();

	if (drawRect)
	{
		window->draw(overlayRectangle);
	}

	for (i = 0; i < spriteVector.size(); i++)
	{
		window->draw(spriteVector.at(i));
	}
	spriteVector.clear();
}

void MapOverlayAnimation::playVictoryAnimation()
{
	addAnimation(OverlayAnimationType::Victory);
	waitingSignals.push_back(AnimationSignal(level, SignalType::animationStarted, SignalSubType::Victory));
}

void MapOverlayAnimation::startAnimation(OverlayAnimationType type)
{
	step = 0;
	currentlyRunningAnimation = type;
}

void MapOverlayAnimation::addAnimation(OverlayAnimationType type)
{
	if (currentlyRunningAnimation == OverlayAnimationType::none)
	{
		startAnimation(type);
	}
	else
	{
		animQueue.push_back(type);
	}
}