#include "AnimationLayer.h"
#include "ConfirmationLayer.h"

bool AnimationLayer::trackEvent(StructuredEvent* evnt)
{
	if (!evnt->tryLayer(this))
	{
		return false;
	}
	if (evnt->getDepth() > layer)
	{
		if (middleMan)
		{
			return nextLevel->trackEvent(evnt);
		}
		/*else if (evnt->getDepth() == layer + 1)
		{
			evnt->openNewAnimationLayer(this);
			nextLevel->trackEvent(evnt);
		}*/
		else
		{
			throw new std::exception();
			return false;
		}
	}
	else if (evnt->getDepth() == layer)
	{
		//applySquadManagerEvent(evnt);
		//evnt->actUponAnimationLayer(this);
		/*if (evnt->tryLayer(this))
		{*/
			applyEvent(evnt);
			return true;
		/*}
		else
		{
			return false;
		}*/
	}
	else
	{
		throw new std::exception();
		return false;
	}
}

std::vector<MouseSignal> AnimationLayer::passMousePos(sf::Vector2i mousePos)
{
	std::vector<MouseSignal> retVal;
	applyMousePos(mousePos);

	if (middleMan)
	{
		retVal = nextLevel->passMousePos(mousePos);
	}
	retVal.insert(retVal.begin(), mouseSignals.begin(), mouseSignals.end());
	mouseSignals.clear();

	return retVal;
}

void AnimationLayer::openNewLayer(AnimationLayer* newLayer)
{
	if (middleMan)
	{
		throw new std::exception();
	}
	middleMan = true;
	nextLevel = newLayer;
}

void AnimationLayer::drawAll()
{
	if (drawable && (!middleMan || nextLevel->canSeeThrough()))
	{
		draw();
	}
	if (middleMan)
	{
		nextLevel->drawAll();
	}
}

std::vector<AnimationSignal> AnimationLayer::collectSignals()
{
	std::vector<AnimationSignal> retVal;
	std::vector<AnimationSignal> nextLevelSignals;
	retVal.insert(retVal.end(), signals.begin(), signals.end());
	signals.clear();

	if (middleMan)
	{
		nextLevelSignals = nextLevel->collectSignals();
		retVal.insert(retVal.end(), nextLevelSignals.begin(), nextLevelSignals.end());
	}

	return retVal;
}

std::vector<MouseSignal> AnimationLayer::collectMouseSignals()
{
	std::vector<MouseSignal> retVal;
	std::vector<MouseSignal> nextLevelSignals;

	if (middleMan)
	{
		nextLevelSignals = nextLevel->collectMouseSignals();
		retVal.insert(retVal.end(), nextLevelSignals.begin(), nextLevelSignals.end());
	}
	else
	{
		retVal.insert(retVal.end(), mouseSignals.begin(), mouseSignals.end());
	}
	mouseSignals.clear();

	return retVal;
}

void AnimationLayer::closeSubLayer() 
{ 
	if (middleMan)
	{
		nextLevel->closeSubLayer();
		delete nextLevel;
		nextLevel = nullptr;
		middleMan = false;
	}
}


bool AnimationLayer::isSubOnHold()
{
	if (middleMan)
	{
		return nextLevel->isSubOnHold();
	}
	else
	{
		return isOnHold();
	}
}

void AnimationLayer::openConfirmationLayer()
{
	openNewLayer(new ConfirmationLayer(layer + 1, window, assets, stringHandler));
}