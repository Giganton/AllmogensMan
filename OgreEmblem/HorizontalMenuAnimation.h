#pragma once
#include "MenuAnimation.h"

class HorizontalMenuPackage;

class HorizontalMenuAnimation : public MenuAnimation
{
private:
	sf::Sprite windowLeftEdge;
	sf::Sprite windowMiddle;
	sf::Sprite windowRightEdge;

	int wordLength = 0;
	bool centered = false;

public:
	HorizontalMenuAnimation() {};
	HorizontalMenuAnimation(HorizontalMenuPackage* menuPack, UTIL::ScreenCoord offset, bool cntered, sf::RenderWindow* ww);
	void draw() override;
	void draw(Menu menu) override;
	void draw(MenuVisualData menu) override;

	HorizontalMenuAnimation* clone() { return new HorizontalMenuAnimation(*this); };
};