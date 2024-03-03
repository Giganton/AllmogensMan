#include "MenuManager.h"


void MenuManager::controlMenu(sf::Event keyPress)
{
	int menuChoice;
	if (!(keyPress.type == sf::Event::KeyPressed))
	{
		throw new std::exception();
	}
	switch (keyPress.key.code)
	{
	case sf::Keyboard::Up:
		menu.moveUp();
		selectionAction();
		break;
	case sf::Keyboard::Down:
		menu.moveDown();
		selectionAction();
		break;
	case sf::Keyboard::Left:
		menu.moveLeft();
		selectionAction();
		break;
	case sf::Keyboard::Right:
		menu.moveRight();
		selectionAction();
		break;
	case sf::Keyboard::X:
		menuChoice = menu.enterSelected();
		performMenuAction(menuChoice);
		break;
	case sf::Keyboard::Z:
		menu.goBack();
		if (menu.isClosed())
		{
			closeMenu();
		}
		break;
	}
}