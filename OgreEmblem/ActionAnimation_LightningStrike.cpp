#include "ActionAnimation_LightningStrike.h"
#include "GraphicsAssets.h"
#include "BattleAnimation.h"
#include <ctime>

ActionAnimation_LightningStrike::ActionAnimation_LightningStrike(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww) : ActionAnimation(battleAnim, results, isMaster, assets, ww)
{
	boltSprite.setTexture(animationAssets->lightningStrike);
	boltSource = currentBattle->getBoxPos() + UTIL::ScreenCoord(currentBattle->getBoxSize().x / 2, 0);
	boltSprite.setPosition(boltSource.x, boltSource.y);

}

bool ActionAnimation_LightningStrike::progressAction()
{
	bool allSpritesFinished = true;
	//bool allFinished = false;
	//std::vector<FightEffect> effects = animatedResults.getEffects();
	std::vector<Targets> targets = animatedResults.getTargets();
	double time;
	unsigned int i;
	double fadeTime =  0.75;
	double flashTime = 0.1;
	double flashFadeTime = 0.2;
	double holdTime = 0.3;

	switch (step)
	{
	case 0:
		startTime = (double)std::clock();
		step = 2;
		break;
	case 2:
		time = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
		if (time > fadeTime)
		{
			step = 3;
			startTime = (double)std::clock();
		}
		else
		{
			fadePercent = (time / fadeTime) * 0.5;
			currentBattle->addOverlayColor(sf::Color(0, 0, 0, 255 * fadePercent));
		}
		break;
	case 3:
		time = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
		currentBattle->addOverlayColor(sf::Color(255, 255, 255, 255));
		if (time > flashTime)
		{
			step = 4;
			startTime = (double)std::clock();
		}
		else
		{
			currentBattle->addOverlayColor(sf::Color(255, 255, 255, 255));
		}
		break;
	case 4:
		drawBolt = true;
		for (i = 0; i < targets.size(); i++)
		{
			FightPos mapPos = targets.at(i).getPrimaryTarget().first;
			UTIL::ScreenCoord strikePos = currentBattle->getSpritePos(mapPos) + UTIL::ScreenCoord(SPRITE_W / 2, SPRITE_H);
			sf::FloatRect origSize = boltSprite.getLocalBounds();
			float scaleX = (strikePos.x - boltSource.x) / origSize.width;
			float scaleY = (strikePos.y - boltSource.y) / origSize.height;
			boltSprite.setScale(scaleX, scaleY);
		}

		//dealDamageInSync(effects);
		//effectsAnimations.startInstance(activeInstance);
		step = 5;
	case 5:
		time = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
		if (time > flashFadeTime)
		{
			step = 6;
			startTime = (double)std::clock();
			currentBattle->addOverlayColor(sf::Color(0, 0, 0, 255 * 0.5));
		}
		else
		{
			fadePercent = 1 - (time / flashFadeTime);
			currentBattle->addOverlayColor(sf::Color(255, 255, 255, 255 * fadePercent));
			currentBattle->addOverlayColor(sf::Color(0, 0, 0, 255 * 0.5));
		}
		break;
	case 6:
		time = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
		if (time > holdTime)
		{
			step = 7;
			startTime = (double)std::clock();
		}
		currentBattle->addOverlayColor(sf::Color(0, 0, 0, 255 * 0.5));
		break;
	case 7:
		time = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
		drawBolt = false;
		if (time > fadeTime)
		{
			step = 8;
		}
		else
		{
			fadePercent = (1-(time / fadeTime)) * 0.5;
			currentBattle->addOverlayColor(sf::Color(0, 0, 0, 255 * fadePercent));
		}
		break;
	case 8:

		for (i = 0; i < targets.size(); i++)
		{
			allSpritesFinished = allSpritesFinished && spriteAnimations.find(targets.at(i).getPrimaryTarget().second)->second.isFinished();
		}
		if (allSpritesFinished)// && effectsAnimations.isFinished())
		{
			step = 9;
		}
		break;
	case 9:
		actionInstanceFinished = true;
		isActive = false;
		drawBolt = false;
		break;
	}
	if (drawBolt)
	{
		currentBattle->addSpriteOverOverlay(boltSprite);
	}
	//progressSprites();
	return actionInstanceFinished;
}