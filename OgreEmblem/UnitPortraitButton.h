#pragma once
#include "MouseInteractionObject.h"
#include "Unit.h"
#include "TextDrawer.h"

class GraphicsAssets;


class UnitPortraitButton : public MouseInteractionObject
{
private:
	TextDrawer textDrawer;

	sf::Vector2f position;
	float frameWidth = 1;

	bool selected = false;

	bool empty = true;
	bool soldOut = false;

	std::string name;
	std::string level;
	sf::Texture* portrait = nullptr;
	sf::Vector2f portraitSize;
public:
	UnitPortraitButton() {};
	UnitPortraitButton(UnitData unitData, sf::Vector2f pos, GraphicsAssets* assets);
	UnitPortraitButton(sf::Vector2f pos, GraphicsAssets* assets);

	void setPosition(sf::Vector2f pos);
	void setSelected(bool sel) { selected = sel; };
	sf::Vector2f getSize();

	void draw(sf::RenderWindow* window);
	void mousePosUpdate(sf::Vector2i currentMousePos) override;

	void setEmpty() { empty = true; };
	bool isEmpty() { return empty; };

	void setSold() { soldOut = true; empty = true; };
};
