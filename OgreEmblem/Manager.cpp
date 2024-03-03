#include "Manager.h"

void Manager::controlMenu(sf::Event keyPress)
{
	int menuChoice;
	if (!(keyPress.type == sf::Event::KeyPressed))
	{
		throw new std::exception();
	}
	switch (keyPress.key.code)
	{
	case sf::Keyboard::Up:
		activeMenu.moveUp();
		break;
	case sf::Keyboard::Down:
		activeMenu.moveDown();
		break;
	case sf::Keyboard::Left:
		activeMenu.moveLeft();
		break;
	case sf::Keyboard::Right:
		activeMenu.moveRight();
		break;
	case sf::Keyboard::X:
		menuChoice = activeMenu.enterSelected();
		performMenuAction(menuChoice);
		break;
	case sf::Keyboard::Z:
		activeMenu.goBack();
		if (activeMenu.isClosed())
		{
			deactivateMenu();
		}
		break;
	}
}

/*void Manager::receiveInput(sf::Event keyPress)
{
	if (middleMan)
	{
		if (nextLevel->shouldBeClosed())
		{
			closeSubManagers();
			handleInput(keyPress);
		}
		else
		{
			nextLevel->receiveInput(keyPress);
			if (nextLevel->shouldBeClosed())
			{
				closeSubManagers();
			}
		}
	}
	else
	{
		handleInput(keyPress);
	}
}

void Manager::closeSubManagers()
{
	if (middleMan)
	{
		nextLevel->closeSubManagers();
		delete nextLevel;
		nextLevel = nullptr;

		middleMan = false;
	}
	else
	{
		return;
	}
}*/

void Manager::goToState(int state, bool saveHistory, bool delHistory)
{
	if (getState() == state)
	{
		throw new std::exception();
	}
	else
	{
		captureState();
		if (saveHistory)
		{
			saveState();
		}
		enterState(state);
		if (delHistory)
		{
			deleteHistory();
		}
	}
}

Menu Manager::getActiveMenu()
{
	if (!isMenuActive())
	{
		throw new std::exception();
	}
	return activeMenu;
}

void Manager::closeMenu()
{
	activeMenu.deActivate();
	deactivateMenu();
}

void Manager::openMenu(Menu menu)
{
	activeMenu = menu;
	activeMenu.activate();
	activeMenu.setSelected(0);
	activateMenu();
}
