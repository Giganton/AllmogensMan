#include "ExperienceGainAnimation.h"
#include "Formler.h"

/*ExperienceGainAnimation::ExperienceGainAnimation(int startXp, int finalXp, int unitLvl)
{
	startExp = startXp;
	finalExp = finalXp;

	int currentLevelExpReq = FORMLER::xpRequirementByLevel(unitLvl);
	nextLevelUpExpReq = FORMLER::xpRequirementByLevel(unitLvl + 1);
	int currentExpFraction = (int)(100 * ((float)(startExp - currentLevelExpReq)) / (float)nextLevelUpExpReq);
	ExpBars = ExperienceBar(currentExpFraction, UTIL::ScreenCoord(500, 500));

	levelUps = 0;
	finalExpFraction = (int)(100 * ((float)(finalExp - currentLevelExpReq)) / (float)nextLevelUpExpReq);
	while (finalExp > nextLevelUpExpReq)
	{
		levelUps = levelUps + 1;
		nextLevelUpExpReq = FORMLER::xpRequirementByLevel(unitLvl + levelUps + 1);
		currentLevelExpReq = FORMLER::xpRequirementByLevel(unitLvl + levelUps);
		finalExpFraction = (int)(100 * ((float)(finalExp - currentLevelExpReq)) / (float)nextLevelUpExpReq);
	}
}*/

ExperienceGainAnimation::ExperienceGainAnimation(std::vector<std::pair<int, int>> xpDetails, std::vector<int> unitLvls, std::vector<std::pair<int, int>> unitPos, bool playerAttacking)
{
	unsigned int i;
	for (i = 0; i < xpDetails.size(); i++)
	{
		ExpAnimationStruct entry;
		entry.startExp = xpDetails.at(i).first;
		entry.finalExp = xpDetails.at(i).second;

		entry.unitLevel = unitLvls.at(i);
		int currentLevelExpReq = FORMLER::xpRequirementByLevel(entry.unitLevel);
		entry.nextLevelUpExpReq = FORMLER::xpRequirementByLevel(entry.unitLevel + 1);
		int currentExpFraction = (int)(100 * ((float)(entry.startExp - currentLevelExpReq)) / (float)entry.nextLevelUpExpReq);
		entry.finalExpFraction = (int)(100 * ((float)(entry.finalExp - currentLevelExpReq)) / (float)entry.nextLevelUpExpReq);

		entry.levelUps = 0;
		while (entry.finalExp > entry.nextLevelUpExpReq)
		{
			entry.levelUps = entry.levelUps + 1;
			entry.nextLevelUpExpReq = FORMLER::xpRequirementByLevel(entry.unitLevel + entry.levelUps + 1);
			currentExpFraction = (int)(100 * ((float)(entry.startExp - currentLevelExpReq)) / (float)entry.nextLevelUpExpReq);
			entry.finalExpFraction = (int)(100 * ((float)(entry.finalExp - currentLevelExpReq)) / (float)entry.nextLevelUpExpReq);
		}

		UTIL::ScreenCoord offset;
		if (playerAttacking)
		{
			offset = UTIL::ScreenCoord(150 + unitPos.at(i).first * 130 - 20, 200 + unitPos.at(i).second * 120 + 20);
		}
		else
		{
			offset = UTIL::ScreenCoord(600 + 150 + (1 - unitPos.at(i).first) * 130 - 20, 200 + unitPos.at(i).second * 120 + 20);
		}

		entry.ExpBar = ExperienceBar(currentExpFraction, offset);

		ExpBars.push_back(entry);
	}
}

void ExperienceGainAnimation::progressAction(sf::RenderWindow* window)
{
	unsigned int i;
	bool allDone = true;
	std::vector<bool> barIsDone(ExpBars.size(), false);
	if (!animationStarted)
	{
		animationClock.restart();
		animationStarted = true;
		animationStep = 0;
	}
	else
	{
		float time = animationClock.getElapsedTime().asSeconds();
		switch (animationStep)
		{
		case 0: //pause
			if (time > 0.5)
			{
				animationClock.restart();
				animationStep = 1;
			}
			break;
		case 1:
			for (i = 0; i < ExpBars.size(); i++)
			{
				ExpBars.at(i).ExpBar.draw(window);
				if (ExpBars.at(i).finalExp > ExpBars.at(i).startExp)
				{
					if (time > xpIncrementTime && !barIsDone.at(i))
					{
						animationClock.restart();
						ExpBars.at(i).ExpBar.increment();

						if (ExpBars.at(i).ExpBar.getXP() > 100)
						{
							ExpBars.at(i).ExpBar.setXP(0);
							ExpBars.at(i).levelUps = ExpBars.at(i).levelUps - 1;
						}
						if (ExpBars.at(i).levelUps == 0 && ExpBars.at(i).ExpBar.getXP() == ExpBars.at(i).finalExpFraction)
						{
							animationClock.restart();
							barIsDone.at(i) = true;
						}
					}
				}
				else
				{
					barIsDone.at(i) = true;
				}
			}

			for (i = 0; i < ExpBars.size(); i++)
			{
				allDone = allDone && barIsDone.at(i);
			}
			if (allDone)
			{
				animationStep = 2;
			}
			break;
		case 2:
			for (i = 0; i < ExpBars.size(); i++)
			{
				ExpBars.at(i).ExpBar.draw(window);
			}
			if (time > 2)
			{
				animationDone = true;
				animationClock.restart();
				animationStep = 3;
			}
			break;
		case 3:

			break;
		}
	}
}