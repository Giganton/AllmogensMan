#include "LifeBarAnimation.h"
#include "LifeBar.h"
#include "BattleAnimation.h"

LifeBarAnimation::LifeBarAnimation(BattleAnimation* bAnim, int unitID, int incomingDamage)
{
	lifeBar = bAnim->getLifeBarPtr(unitID);
	damageToDeal = incomingDamage;
}

void LifeBarAnimation::start()
{
	int maxHP = lifeBar->getMaxHP();
	int currHP = lifeBar->getHP();
	goalHP = currHP - damageToDeal;

	if (goalHP < 0)
	{
		goalHP = 0;
	}

	damageToDeal = currHP - goalHP;

	float maxLength = lifeBar->getRedLength();
	startGreenLength = lifeBar->getGreenLength();
	goalGreenLength = ((float)goalHP) / ((float)maxHP) * maxLength;

	//speed = ((float)10) / ((float)maxHP * 1000); //10hp per sekund
	speed = 10 * maxLength / ((float)(maxHP * 1000));

	initiated = true;
	lastTime = std::clock();
}

void LifeBarAnimation::draw(sf::RenderWindow* window)
{

}

void LifeBarAnimation::progress()
{
	if (initiated)
	{
		if (!started)
		{
			lastTime = std::clock();
			started = true;
		}
		else if (!finished)
		{
			float time = std::clock() - lastTime;
			lastTime = std::clock();
			float newLength = lifeBar->getGreenLength() - time * speed;
			if (newLength > goalGreenLength)
			{
				lifeBar->setGreenLength(newLength);
			}
			else
			{
				newLength = goalGreenLength;
				lifeBar->setHP(goalHP);
				finished = true;
			}
		}
		else
		{

		}
	}
}