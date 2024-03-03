#pragma once
#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "TextDrawer.h"
#include "TraitTreeAnimation.h"

class StringHandler;
class GraphicsAssets;

class UnitDetailsWindow
{
private:
	GraphicsAssets* assets = nullptr;
	UnitData unitData;
	TextDrawer textDrawer;
	StringHandler* stringHandler = nullptr;

	sf::Vector2f position;

	sf::Vector2f traitTreeOffset = sf::Vector2f(370, 0);
	sf::Vector2f infoOffset = sf::Vector2f(600, 10);
	sf::Vector2f portraitOffset = sf::Vector2f(0, 20);

	bool showUnit = false;
	TraitTreeAnimation traitTreeAnimation;

	//sf::RectangleShape visualBox;
	//sf::RectangleShape visualFrame;
	sf::RectangleShape traitBox;
	sf::RectangleShape traitFrame;

	sf::VertexArray visualQuads;
	sf::VertexArray visualFrameQuads;

	sf::Vector2f vBoxSize = sf::Vector2f(1920.0f, 180.0f);

	sf::Sprite portrait;

	std::string unitName;
	std::string descriptionText;

	std::vector<sf::Text> unitText;

	bool showTraitText = false;
	std::string traitTitle;
	std::string traitDescription;

	void setupBoxes();
	void setupUnitText(UnitData unit);
	void setupTraitText(TraitTag trait);

public:
	UnitDetailsWindow() {};
	UnitDetailsWindow(UnitData unit, sf::Vector2f pos, GraphicsAssets* assts, StringHandler* strHand);
	UnitDetailsWindow(sf::Vector2f pos, GraphicsAssets* assts, StringHandler* strHand);

	void draw(sf::RenderWindow* window);
	void pointAtTrait();
	void passMousePos(sf::Vector2i pos);
	void setUnit(UnitData unitD);
	void unsetUnit() { showUnit = false; };
};
