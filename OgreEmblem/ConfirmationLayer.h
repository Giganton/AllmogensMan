#pragma once
#include "AnimationLayer.h"
#include<string>
#include "TextDrawer.h"
#include "DialogueButton.h"

class ConfirmationLayer : public AnimationLayer
{
private:
	std::string descriptionText = "hejsan svejsan gamle tok";
	std::string confirmText = "nänänänä";
	std::string denyText = "hohohoho";

	sf::Vector2f boxSize;
	sf::Vector2f boxPos;
	sf::Vector2f buttonOffset;

	DialogueButton confirmButton;
	DialogueButton denyButton;

	TextDrawer textDrawer;


	void applyMousePos(sf::Vector2i mousePos) override;
public:
	ConfirmationLayer() {};
	ConfirmationLayer(int lr, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler);

	ConfirmationLayer(const ConfirmationLayer& cpEQ);
	ConfirmationLayer& operator=(const ConfirmationLayer asEQ);
	~ConfirmationLayer() { AnimationLayer::~AnimationLayer(); };

	ConfirmationLayer* clone() override;

	void initLayer(std::string description, std::string confirm, std::string deny);
	void draw() override;
	void applyEvent(StructuredEvent* evnt) override;
};