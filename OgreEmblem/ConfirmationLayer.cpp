#include "ConfirmationLayer.h"
#include "ConfirmationMouseButtons.h"


ConfirmationLayer::ConfirmationLayer(int lr, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler) : AnimationLayer(lr, ww, assts, strHandler)
{
	drawable = true;

	textDrawer = TextDrawer(assets);

	boxSize = sf::Vector2f(450, 250);
	boxPos = sf::Vector2f(ww->getSize().x / 2 - boxSize.x / 2, ww->getSize().y / 2 - boxSize.y / 2);
	sf::Vector2f centerOfBoxX = sf::Vector2f(boxPos.x + boxSize.x / 2, 0);
	buttonOffset = sf::Vector2f(140, 0);

	confirmButton = DialogueButton("", sf::Vector2f(), assts);
	denyButton = DialogueButton("", sf::Vector2f(), assts);

	float buttonHeight = confirmButton.getSize().y;
	float buttonWidth = confirmButton.getSize().x;

	sf::Vector2f buttonYPos = sf::Vector2f(0, boxPos.y + boxSize.y * 2 / 3 - buttonHeight / 2);

	confirmButton.setPosition(centerOfBoxX - buttonOffset + buttonYPos);
	denyButton.setPosition(centerOfBoxX + buttonOffset - sf::Vector2f(buttonWidth,0) + buttonYPos);
}

ConfirmationLayer::ConfirmationLayer(const ConfirmationLayer& cpEQ)
{
	middleMan = cpEQ.middleMan;
	if (middleMan)
	{
		nextLevel = cpEQ.nextLevel->clone();
	}
	window = cpEQ.window;
	stringHandler = cpEQ.stringHandler;
	layer = cpEQ.layer;
	signals = cpEQ.signals;

	drawable = cpEQ.drawable;
	seeThrough = cpEQ.seeThrough;

	descriptionText = cpEQ.descriptionText;

	confirmButton = cpEQ.confirmButton;
	denyButton = cpEQ.denyButton;
}

ConfirmationLayer& ConfirmationLayer::operator=(const ConfirmationLayer cpEQ)
{
	middleMan = cpEQ.middleMan;
	if (middleMan)
	{
		nextLevel = cpEQ.nextLevel->clone();
	}
	window = cpEQ.window;
	stringHandler = cpEQ.stringHandler;
	layer = cpEQ.layer;
	signals = cpEQ.signals;

	drawable = cpEQ.drawable;
	seeThrough = cpEQ.seeThrough;

	descriptionText = cpEQ.descriptionText;

	confirmButton = cpEQ.confirmButton;
	denyButton = cpEQ.denyButton;

	return *this;
}


ConfirmationLayer* ConfirmationLayer::clone()
{
	return new ConfirmationLayer(*this);
}

void ConfirmationLayer::draw()
{
	sf::RectangleShape fade = sf::RectangleShape(sf::Vector2f(window->getSize().x, window->getSize().y));

	sf::RectangleShape box = sf::RectangleShape(boxSize);
	box.setPosition(boxPos);
	
	box.setFillColor(sf::Color::Green);
	fade.setFillColor(sf::Color(0,0,0,130));

	textDrawer.setStandardFont();
	sf::Vector2f centerOfText = boxPos + sf::Vector2f(boxSize.x/2, boxSize.y/2) - sf::Vector2f(0, 50);
	sf::Text text = textDrawer.drawText(descriptionText, centerOfText, 300, true);

	window->draw(fade);
	window->draw(box);
	window->draw(text);

	confirmButton.draw(window);
	denyButton.draw(window);
}

void ConfirmationLayer::initLayer(std::string description, std::string confirm, std::string deny)
{ 
	descriptionText = description; 
	confirmText = confirm; 
	denyText = deny; 

	confirmButton.setText(confirmText);
	denyButton.setText(denyText);
}

void ConfirmationLayer::applyEvent(StructuredEvent* evnt)
{
	evnt->applyToConfirmationLayer(this);
}

void ConfirmationLayer::applyMousePos(sf::Vector2i mousePos)
{
	confirmButton.mousePosUpdate(mousePos);
	denyButton.mousePosUpdate(mousePos);
	if (confirmButton.isHovered())
	{
		MouseSignal signal = MouseSignal(layer, ConfirmationMouseButtons::confirmed);
		mouseSignals.push_back(signal);
	}
	else if (denyButton.isHovered())
	{
		MouseSignal signal = MouseSignal(layer, ConfirmationMouseButtons::denied);
		mouseSignals.push_back(signal);
	}
	else
	{
		MouseSignal signal = MouseSignal(layer, ConfirmationMouseButtons::none);
		mouseSignals.push_back(signal);
	}
}

//SIGNE