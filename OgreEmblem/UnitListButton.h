#pragma once
#include "MouseInteractionObject.h"
#include "Unit.h"
#include "TextDrawer.h"

class GraphicsAssets;
class StringHandler;

class UnitListButton : public MouseInteractionObject
{
private:
	TextDrawer textDrawer;
	StringHandler* stringHandler = nullptr;

	UnitData unitData;

	sf::Vector2f position;
	sf::RectangleShape visualBox;
	sf::Vector2f vBoxSize = sf::Vector2f(300.0f, 95.0f);

	sf::Text unitName;
	sf::Text unitDescription;

	sf::Sprite portrait;

	std::string descriptionText;

	sf::Vector2f unitNamePos;

	void setup();
public:
	UnitListButton() {};
	UnitListButton(UnitData unit, sf::Vector2f pos, GraphicsAssets* assets, StringHandler* strHand);

	/*UnitListButton(const UnitListButton& cpEQ);
	UnitListButton& operator=(const UnitListButton asEQ);
	~UnitListButton() { };*/

	void draw(sf::RenderWindow* window) override;
	void mousePosUpdate(sf::Vector2i currentMousePos) override;
};
