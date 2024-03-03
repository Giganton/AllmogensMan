#pragma once
#include<vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "SquadRepresentation.h"
#include<vector>
#include "SpriteAnimator.h"

class UnitPackage;
class GraphicsAssets;

class SquadDrawer
{
private:
	std::map < ProfessionTag, sf::Texture>* squadTextureMap = nullptr;
	//UnitPackage* unitAssets = nullptr;

	SpriteAnimator spriteAnim;



	UTIL::ScreenCoord squadSpriteSize = UTIL::ScreenCoord(40, 47);
	float animStepTime = 0.5f;
	int nrOfAnimSteps = 2;

	void drawMenuBgBox();
public:
	SquadDrawer() {};
	SquadDrawer(std::map < ProfessionTag, sf::Texture>* squadTextures);

	std::vector<sf::Sprite> drawMapSquad(SquadRepresentation squadRep);
	void drawMenuSquad(Squad squad, sf::Vector2f pos, sf::RenderWindow* window);

	void resetAnimationCycle();
};
