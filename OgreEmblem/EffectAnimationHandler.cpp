#include "EffectAnimationHandler.h"

/*EffectAnimationHandler::EffectAnimationHandler(BattleAnimation* bAnim, std::vector<FightEffect> effects, GraphicsAssets* assets)
{
	currentBattle = bAnim;
	effectsToDraw = effects;
	initiated = true;

	unsigned int i;
	for (i = 0; i < effects.size(); i++)
	{
		int instance = effects.at(i).instanceNumber;
		EffectAnimation newAnim = EffectAnimation(effects.at(i), bAnim, assets);

		if (instanceEffectAnimMap.count(instance) > 0)
		{
			instanceEffectAnimMap.find(instance)->second.push_back(newAnim);
		}
		else
		{
			instanceEffectAnimMap.insert({ instance, {newAnim} });
		}
	}
}

bool EffectAnimationHandler::isFinished()
{ 
	unsigned int j;
	bool finished = true;
	std::map<int, std::vector<EffectAnimation>>::iterator it;

	for (it = instanceEffectAnimMap.begin(); it != instanceEffectAnimMap.end(); it++)
	{
		for (j = 0; j < it->second.size(); j++)
		{
			if (!it->second.at(j).isFinished())
			{
				finished = false;
			}
		}
	}
	return finished; 
}

void EffectAnimationHandler::startInstance(int instanceNr)
{
	unsigned int i;
	if (instanceEffectAnimMap.count(instanceNr) < 1)
	{
		throw new std::exception();
	}
	int sz = instanceEffectAnimMap.find(instanceNr)->second.size();
	for (i = 0; i < sz; i++)
	{
		instanceEffectAnimMap.find(instanceNr)->second.at(i).start();
	}
}

void EffectAnimationHandler::draw(sf::RenderWindow* window)
{
	unsigned int j;
	std::map<int, std::vector<EffectAnimation>>::iterator it;

	if (instanceEffectAnimMap.size() > 0)
	{
		for (it = instanceEffectAnimMap.begin(); it != instanceEffectAnimMap.end(); it++)
		{
			for (j = 0; j < it->second.size(); j++)
			{
				it->second.at(j).draw(window);
			}
		}
	}
}


void EffectAnimationHandler::progress() 
{
	unsigned int j;
	std::map<int, std::vector<EffectAnimation>>::iterator it;

	for (it = instanceEffectAnimMap.begin(); it != instanceEffectAnimMap.end(); it++)
	{
		for (j = 0; j < it->second.size(); j++)
		{
			it->second.at(j).progress();
		}
	}
}

bool EffectAnimationHandler::isFinished(int instanceNr)
{
	unsigned int i;
	bool finished = true;
	if (instanceEffectAnimMap.size() == 0)
	{
		return true;
	}
	for (i = 0; i < instanceEffectAnimMap.find(instanceNr)->second.size(); i++)
	{
		if (!instanceEffectAnimMap.find(instanceNr)->second.at(i).isFinished())
		{
			finished = false;
		}
	}
	return finished;
}*/