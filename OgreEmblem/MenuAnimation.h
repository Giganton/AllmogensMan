#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GraphicsUtils.h"
#include "MenuVisualData.h"

class Menu;
class VerticalMenuPackage;

class MenuAnimation
{
protected:
	UTIL::ScreenCoord menuOffset;
	int textOffset = 12;
	int fontSize = 24;

	sf::Sprite cursorSprite;
	sf::Font font;
	sf::Text optionsText;

	MenuVisualData menuData;
	bool active = false;

	sf::RenderWindow* window = nullptr;
public:
	//MenuAnimation() {};
	//MenuAnimation(MenuPackage* menuPack, sf::RenderWindow* ww);
	void setMenuData(MenuVisualData visData) { menuData = visData; };
	virtual void draw() = 0;
	virtual void draw(Menu menu) = 0;
	virtual void draw(MenuVisualData menu) = 0;

	virtual MenuAnimation* clone() = 0;
	void activate() { active = true; };
	void deActivate() { active = false; };
	bool isActive() { return active; };
};