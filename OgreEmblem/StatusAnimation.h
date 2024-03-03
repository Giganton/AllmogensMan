#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "StatusScreen.h"
#include "VerticalMenuAnimation.h"
#include "Squad.h"

class ScreenPackage;
class VerticalMenuPackage;

class StatusAnimation
{
private:
	sf::RenderWindow* window = nullptr;

	sf::Font font;
	int fontSize = 24;

	float squadWindowPosX = 50;
	float squadWindowPosY = 50;
	float squadOffsetX = 50;
	float squadOffsetY = 50;
	float unitSpacingX = 100;
	float unitSpacingY = 120;


	float textWindowPosX = 500;
	float textWindowPosY = squadWindowPosY;
	float textOffsetX = 50;
	float textOffsetY = 50;
	float textSpacing = 8;

	std::map < ProfessionTag, sf::Texture>* profTextureMap = nullptr;
	sf::Sprite cursorSprite;

	VerticalMenuAnimation menuAnim;

	void drawText(Unit* hoveredUnit);
	float getSpritePosX(float posX);
	float getSpritePosY(float posY);
public:
	StatusAnimation() {};
	StatusAnimation(std::map < ProfessionTag, sf::Texture>* tMap, ScreenPackage* sPack, VerticalMenuPackage* menuPackage, sf::RenderWindow* ww);

	void draw(ScreenVisualData toDraw);
};