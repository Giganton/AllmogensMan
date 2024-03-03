#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "FightResults.h"
#include "EffectAnimation.h"
#include<map>

class BattleAnimation;

/*class EffectAnimationHandler
{
private:
	BattleAnimation* currentBattle = nullptr;
	std::vector<FightEffect> effectsToDraw;
	bool initiated = false;

	std::map<int, std::vector<EffectAnimation>> instanceEffectAnimMap;

public:
	EffectAnimationHandler() {};
	EffectAnimationHandler(BattleAnimation* bAnim, std::vector<FightEffect> effects, GraphicsAssets* assets);

	void startInstance(int instanceNr);

	void draw(sf::RenderWindow* window);
	void progress();
	bool isFinished();
	bool isFinished(int instanceNr);
};*/
