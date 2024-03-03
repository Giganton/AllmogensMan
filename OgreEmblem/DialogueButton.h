#pragma once
#include "MouseInteractionObject.h"
#include "TextDrawer.h"

class GraphicsAssets;

class DialogueButton : public MouseInteractionObject
{
protected:
	sf::Vector2f position;
	std::string buttonText = "hejhej";

	sf::Vector2f buttonSize;
	sf::Vector2f textOffset;

	TextDrawer textDrawer;
public:
	DialogueButton() {};
	DialogueButton(std::string bttonText, sf::Vector2f pos, GraphicsAssets* assets);

	void draw(sf::RenderWindow* window) override;
	//void mousePosUpdate(sf::Vector2i currentMousePos) override;

	sf::Vector2f getSize() { return buttonSize; };
	void setText(std::string newText) { buttonText = newText; };

	void setPosition(sf::Vector2f newPos) { position = newPos; setInteractionBoxPos(newPos); };

};