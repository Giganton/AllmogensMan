#include "HorizontalMenuAnimation.h"
#include "GraphicsAssets.h"
#include "Menu.h"
#include "MenuVisualData.h"

HorizontalMenuAnimation::HorizontalMenuAnimation(HorizontalMenuPackage* menuPack, UTIL::ScreenCoord offset, bool cntered, sf::RenderWindow* ww)
{
	windowLeftEdge.setTexture(menuPack->left);
	windowMiddle.setTexture(menuPack->middle);
	windowRightEdge.setTexture(menuPack->right);
	cursorSprite.setTexture(menuPack->cursor);
	//font = menuFont;
	optionsText.setFont(menuPack->font);
	optionsText.setCharacterSize(fontSize);
	optionsText.setFillColor(sf::Color::Black);

	menuOffset = offset;
	centered = cntered;

	textOffset = 96;

	window = ww;
}

void HorizontalMenuAnimation::draw(Menu menu)
{
	if (!menu.isVertical())
	{
		throw new std::exception();
	}

	int i;
	float yPos = 36;
	float xPos = 48;

	Menu activeSubMenu = menu.getActiveMenu();
	std::vector<std::string> textVector = activeSubMenu.getOptionsTexts();
	int nrOfOptions = int(textVector.size());
	for (i = 0; i < nrOfOptions; i++)
	{
		optionsText.setString(textVector.at(i));
		wordLength = wordLength + (int)optionsText.getLocalBounds().width + textOffset;
	}

	int middleLength = 48 + wordLength;
	windowMiddle.setTextureRect(sf::IntRect(0, 0, middleLength, windowLeftEdge.getTextureRect().height));

	if (centered)
	{
		float menuLength = (float)(windowLeftEdge.getTextureRect().width + windowMiddle.getTextureRect().width + windowRightEdge.getTextureRect().width);
		float windowWidth = (float)window->getSize().x;
		menuOffset.x = menuOffset.x + windowWidth / 2 - menuLength / 2;
	}

	windowLeftEdge.setPosition(menuOffset.x + 0, menuOffset.y + 0);
	windowMiddle.setPosition(menuOffset.x + (float)windowLeftEdge.getTextureRect().width, menuOffset.y + 0);
	windowRightEdge.setPosition(menuOffset.x + (float)(windowLeftEdge.getTextureRect().width + windowMiddle.getTextureRect().width), menuOffset.y + 0);
	window->draw(windowLeftEdge);
	window->draw(windowMiddle);
	window->draw(windowRightEdge);

	for (i = 0; i < nrOfOptions; i++)
	{
		optionsText.setString(textVector.at(i));
		optionsText.setPosition(menuOffset.x + xPos, menuOffset.y + yPos);
		window->draw(optionsText);
		if (activeSubMenu.getSelected() == i)
		{
			cursorSprite.setPosition(menuOffset.x + 10, menuOffset.y + yPos);
			window->draw(cursorSprite);
		}
		xPos = xPos + optionsText.getLocalBounds().width + textOffset;
	}
}

void HorizontalMenuAnimation::draw()
{
	if (active)
	{
		draw(menuData);
	}
}

void HorizontalMenuAnimation::draw(MenuVisualData menu)
{
	int i;
	float yPos = 36;
	float xPos = 48;

	std::vector<std::string> textVector = menu.getOptions();
	int nrOfOptions = int(textVector.size());
	float lengthOfText = 0;
	for (i = 0; i < nrOfOptions; i++)
	{
		optionsText.setString(textVector.at(i));
		float size = optionsText.getLocalBounds().width;
		lengthOfText = lengthOfText + size + textOffset;
	}

	int middleLength = 48 + int(lengthOfText);
	windowMiddle.setTextureRect(sf::IntRect(0, 0, middleLength, windowLeftEdge.getTextureRect().height));

	if (centered)
	{
		float menuLength = (float)(windowLeftEdge.getTextureRect().width + windowMiddle.getTextureRect().width + windowRightEdge.getTextureRect().width);
		float windowWidth = (float)(window->getSize().x);
		menuOffset.x = windowWidth / 2 - menuLength / 2;
	}


	windowLeftEdge.setPosition(menuOffset.x + 0, menuOffset.y + 0);
	windowMiddle.setPosition(menuOffset.x + (float)windowLeftEdge.getTextureRect().width, menuOffset.y + 0);
	windowRightEdge.setPosition(menuOffset.x + (float)(windowLeftEdge.getTextureRect().width + windowMiddle.getTextureRect().width), menuOffset.y + 0);
	window->draw(windowLeftEdge);
	window->draw(windowMiddle);
	window->draw(windowRightEdge);

	for (i = 0; i < nrOfOptions; i++)
	{
		optionsText.setString(textVector.at(i));
		optionsText.setPosition(menuOffset.x + xPos + 48, menuOffset.y + yPos);
		float size = optionsText.getLocalBounds().width;
		window->draw(optionsText);
		if (menu.getSelected() == i)
		{
			cursorSprite.setPosition(menuOffset.x + 10 + xPos, menuOffset.y + yPos);
			window->draw(cursorSprite);
		}
		xPos = xPos + optionsText.getLocalBounds().width + textOffset;
	}
}