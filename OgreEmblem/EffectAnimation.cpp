#include "EffectAnimation.h"
#include "LifeBar.h"
#include "BattleAnimation.h"

/*EffectAnimation::EffectAnimation(FightEffect effect, BattleAnimation* bAnim, GraphicsAssets* assets)
{
	effectToDraw = effect;

	currentSprite = SpriteAnimation(bAnim, effectToDraw.affectedID, effectToDraw.affectedPos.attackingSide);
	if (effectToDraw.physicalBlock)
	{
		damageNumberAnim = DamageNumberAnimation(bAnim, effectToDraw.affectedID, assets);
	}
	else
	{
		damageNumberAnim = DamageNumberAnimation(bAnim, effectToDraw.affectedID, effectToDraw.damageTaken, assets);
	}
	
	lifeBarAnim = LifeBarAnimation(bAnim, effectToDraw.affectedID, effectToDraw.damageTaken);
}


void EffectAnimation::draw(sf::RenderWindow* window)
{
	damageNumberAnim.draw(window);
	lifeBarAnim.draw(window);
}

void EffectAnimation::start()
{
	started = true;
	if (effectToDraw.damageTaken > 0)
	{
		currentSprite.addToQueue(enumSpriteAnimType::incomingDamage);
	}
	else if (effectToDraw.physicalBlock)
	{
		currentSprite.addToQueue(enumSpriteAnimType::block);		
	}
	damageNumberAnim.start();
	lifeBarAnim.start();
	startTime = std::clock();
}

void EffectAnimation::progress()
{
	if (started)
	{
		currentSprite.progress();
		damageNumberAnim.progress();
		lifeBarAnim.progress();
	}
	if (currentSprite.isFinished() && damageNumberAnim.isFinished() && lifeBarAnim.isFinished())
	{
		if (effectToDraw.affectedDied && !deathAnimStarted)
		{
			deathAnimStarted = true;
			currentSprite.startFadeAnimation(1, 0.5, true);
		}
		else
		{
			finished = true;
		}
	}
}*/


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////// Skadesiffra /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DamageNumberAnimation::DamageNumberAnimation(BattleAnimation* bAnim, int dmgedUnitID, int dmg, GraphicsAssets* assets)
{
	currentBattle = bAnim;
	damagedUnitID = dmgedUnitID;
	//startPos = spritePos + sf::Vector2f(25, -50);
	incomingDamage = dmg;

	textDrawer = TextDrawer(assets);
	textDrawer.setStandardFont();
	textDrawer.setSize(32);
	textDrawer.setColor(sf::Color::Black);
}

DamageNumberAnimation::DamageNumberAnimation(BattleAnimation* bAnim, int dmgedUnitID, GraphicsAssets* assets)
{
	currentBattle = bAnim;
	damagedUnitID = dmgedUnitID;
	//startPos = spritePos +sf::Vector2f(0, -50);
	blocked = true;

	textDrawer = TextDrawer(assets);
	textDrawer.setStandardFont();
	textDrawer.setSize(32);
	textDrawer.setColor(sf::Color::Black);
}

void DamageNumberAnimation::start()
{
	initiated = true;
	startTime = std::clock();
	startPos = currentBattle->getSpritePos(damagedUnitID) + sf::Vector2f(SPRITE_W / 2, - 40);
	textPos = startPos;
}

void DamageNumberAnimation::draw(sf::RenderWindow* window)
{
	if (nrVisible)
	{
		sf::Text text;
		if (blocked)
		{
			text = textDrawer.drawText("Block!", textPos, 100,true, false);
		}
		else
		{
			text = textDrawer.drawText(std::to_string(incomingDamage), textPos, 100,true, false);
		}
		window->draw(text);
	}
}

void DamageNumberAnimation::progress()
{
	if (initiated)
	{
		if ((std::clock() - startTime) < 500)
		{
			nrVisible = true;
		}
		else
		{
			nrVisible = false;
			finished = true;
		}
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////// HP-radda /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


