#include "GraphicsInterface.h"

std::vector<AnimationSignal> GraphicsInterface::getSignals(int ID)
{
	unsigned int i;
	std::vector<AnimationSignal> retVal;
	for (i = 0; i < signals.size(); i++)
	{
		if (signals.at(i).getAddress() == ID)
		{
			retVal.push_back(signals.at(i));
		}
	}
	return retVal;
}

std::vector<AnimationSignal> GraphicsInterface::takeSignals(int ID)
{
	unsigned int i;
	std::vector<AnimationSignal> retVal;
	std::vector<AnimationSignal> newList;
	for (i = 0; i < signals.size(); i++)
	{
		if (signals.at(i).getAddress() == ID)
		{
			retVal.push_back(signals.at(i));
		}
		else
		{
			newList.push_back(signals.at(i));
		}
	}
	signals = newList;
	return retVal;
}
