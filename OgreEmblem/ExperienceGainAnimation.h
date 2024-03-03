#pragma once
#include "ExperienceBar.h"

struct ExpAnimationStruct
{
	ExperienceBar ExpBar;
	int startExp = -1;
	int finalExp = -1;

	int currentExp = -1;
	int finalExpFraction = -1;

	int nextLevelUpExpReq = -1;
	int levelUps = -1;
	int unitLevel = -1;
};

class ExperienceGainAnimation
{
private:

	std::vector<ExpAnimationStruct> ExpBars;
	bool animationDone = false;
	bool animationStarted = false;
	int animationStep = -1;

	std::vector<std::pair<int, int>> startAndFinalExp;

	float xpIncrementTime = 0.05;

	sf::Clock animationClock;
	
	void incrementExp();
public:
	ExperienceGainAnimation() {};
	ExperienceGainAnimation(std::vector<std::pair<int, int>> xpDetails, std::vector<int> unitLvls, std::vector<std::pair<int, int>> unitPos, bool attacker);
	void progressAction(sf::RenderWindow* window);

	bool ongoingAnimation() { return (animationStarted && !animationDone); };
	bool animationFinished() { return animationDone; };
};