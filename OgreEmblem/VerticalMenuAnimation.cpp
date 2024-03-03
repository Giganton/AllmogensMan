#include "VerticalMenuAnimation.h"
#include "GraphicsAssets.h"
#include "Menu.h"
#include "MenuVisualData.h"

VerticalMenuAnimation::VerticalMenuAnimation(VerticalMenuPackage* menuPack, UTIL::ScreenCoord offset, sf::RenderWindow* ww)
{
	windowTop.setTexture(menuPack->top);
	windowMiddle.setTexture(menuPack->middle);
	windowBottom.setTexture(menuPack->bottom);
	cursorSprite.setTexture(menuPack->cursor);
	//font = menuFont;
	optionsText.setFont(menuPack->font);
	optionsText.setCharacterSize(fontSize);
	optionsText.setFillColor(sf::Color::Black);

	window = ww;
}

void VerticalMenuAnimation::draw(Menu menu)
{
	if (active)
	{
		if (!menu.isVertical())
		{
			throw new std::exception();
		}
		int i;
		float yPos = 12;

		Menu activeSubMenu = menu.getActiveMenu();
		std::vector<std::string> textVector = activeSubMenu.getOptionsTexts();
		int nrOfOptions = int(textVector.size());
		int middleLength = nrOfOptions * (fontSize + textOffset) + (int)yPos;

		windowTop.setPosition(menuOffset.x + 0, menuOffset.y + 0);
		windowMiddle.setPosition(menuOffset.x + 0, menuOffset.y + (float)windowTop.getTextureRect().height);
		windowMiddle.setTextureRect(sf::IntRect(0, 0, windowTop.getTextureRect().width, middleLength));
		windowBottom.setPosition(menuOffset.x + 0, menuOffset.y + (float)(windowTop.getTextureRect().height + windowMiddle.getTextureRect().height));
		window->draw(windowTop);
		window->draw(windowMiddle);
		window->draw(windowBottom);

		for (i = 0; i < int(textVector.size()); i++)
		{
			optionsText.setString(textVector.at(i));
			optionsText.setPosition(menuOffset.x + 48, menuOffset.y + yPos);

			window->draw(optionsText);
			if (activeSubMenu.getSelected() == i)
			{
				cursorSprite.setPosition(menuOffset.x + 10, menuOffset.y + yPos);
				window->draw(cursorSprite);
			}
			yPos = yPos + optionsText.getCharacterSize() + textOffset;
		}
	}
}

void VerticalMenuAnimation::draw()
{
	if (active)
	{
		draw(menuData);
	}
}

void VerticalMenuAnimation::draw(MenuVisualData menu)
{
	if (active)
	{
		int i;
		float yPos = 12;

		//Menu activeSubMenu = menu.getActiveMenu();
		std::vector<std::string> textVector = menu.getOptions();
		int nrOfOptions = int(textVector.size());
		int middleLength = nrOfOptions * (fontSize + textOffset) + (int)yPos;

		windowTop.setPosition(menuOffset.x + 0, menuOffset.y + 0);
		windowMiddle.setPosition(menuOffset.x + 0, menuOffset.y + (float)windowTop.getTextureRect().height);
		windowMiddle.setTextureRect(sf::IntRect(0, 0, windowTop.getTextureRect().width, middleLength));
		windowBottom.setPosition(menuOffset.x + 0, menuOffset.y + (float)(windowTop.getTextureRect().height + windowMiddle.getTextureRect().height));
		window->draw(windowTop);
		window->draw(windowMiddle);
		window->draw(windowBottom);

		for (i = 0; i < int(textVector.size()); i++)
		{
			optionsText.setString(textVector.at(i));
			optionsText.setPosition(menuOffset.x + 48, menuOffset.y + yPos);

			window->draw(optionsText);
			if (menu.getSelected() == i)
			{
				cursorSprite.setPosition(menuOffset.x + 10, menuOffset.y + yPos);
				window->draw(cursorSprite);
			}
			yPos = yPos + optionsText.getCharacterSize() + textOffset;
		}

	}
}