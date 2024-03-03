#pragma once
#include "MenuAnimation.h"

class VerticalMenuAnimation : public MenuAnimation
{
private:
	sf::Sprite windowTop;
	sf::Sprite windowMiddle;
	sf::Sprite windowBottom;

public:
	VerticalMenuAnimation() {};
	VerticalMenuAnimation(VerticalMenuPackage* menuPack, UTIL::ScreenCoord offset, sf::RenderWindow* ww);
	void draw() override;
	void draw(Menu menu) override;
	void draw(MenuVisualData menu) override;

	VerticalMenuAnimation* clone() override { return new VerticalMenuAnimation(*this); };
};