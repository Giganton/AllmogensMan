#include "Menu.h"
#include<exception>
#include "MenuVisualData.h"

Menu::Menu(std::string menuText, std::vector<Menu> chces)
{
	text = menuText;
	options = chces;
}

Menu::Menu(std::string menuText, int returnVal)
{
	text = menuText;
	std::vector<Menu> temp;
	options = temp;

	menuValue = returnVal;
}

/*void Menu::print()
{
	if (active)
	{
		int i;
		for (i = 0; i < int(options.size()); i++)
		{
			if (selected == i)
			{
				std::cout << "_" + options.at(i).getText() + "_";
			}
			else
			{
				std::cout << options.at(i).getText();
			}
			std::cout << "\n";
		}
	}
	else
	{
		int path = findPath();
		if (!(path == -1))
		{
			options.at(findPath()).print();
		}
	}
}*/

bool Menu::isLeaf()
{
	return (options.empty());
}

bool Menu::isClosed()
{
	if (isActive())
	{
		return false;
	}
	else if (isLeaf())
	{
		return true;
	}
	else
	{
		int i = findPath();
		if (i == -1)
		{
			return true;
		}
		else
		{
			return options.at(i).isClosed();
		}
	}
}

int Menu::findPath()
{
	int i = 0;
	int path = -1;
	while (path == -1)
	{
		if (options.at(i).getSelected() == -1)
		{
			i = i + 1;
		}
		else
		{
			path = i;
		}
		if (i >= int(options.size()))
		{
			return -1;
		}
	}
	return path;
}

void Menu::moveUp()
{
	if (active)
	{
		if (vertical)
		{
			if (selected < 1)
			{
				selected = options.size() - 1;
			}
			else
			{
				selected = selected - 1;
			}
		}
	}
	else
	{
		options.at(findPath()).moveUp();
	}
}

void Menu::moveDown()
{
	if (active)
	{
		if (vertical)
		{
			int temp = options.size();
			if (selected >= int(options.size() - 1))
			{
				selected = 0;
			}
			else
			{
				selected = selected + 1;
			}
		}
	}
	else
	{
		options.at(findPath()).moveDown();
	}
}

void Menu::moveLeft()
{
	if (active)
	{
		if (!vertical)
		{
			if (selected < 1)
			{
				selected = options.size() - 1;
			}
			else
			{
				selected = selected - 1;
			}
		}
	}
	else
	{
		options.at(findPath()).moveLeft();
	}
}

void Menu::moveRight()
{
	if (active)
	{
		if (!vertical)
		{
			int temp = options.size();
			if (selected >= int(options.size() - 1))
			{
				selected = 0;
			}
			else
			{
				selected = selected + 1;
			}
		}
	}
	else
	{
		options.at(findPath()).moveRight();
	}
}

Menu Menu::getActiveMenu()
{
	if (isActive())
	{
		return *this;
	}
	else
	{
		return options.at(findPath()).getActiveMenu();
	}
}

std::vector<std::string> Menu::getOptionsTexts()
{
	int i;
	std::vector<std::string> retVal;

	for (i = 0; i < int(options.size()); i++)
	{
		retVal.push_back(options.at(i).getText());
	}

	return retVal;
}

int Menu::enterSelected()
{
	if (active)
	{
		Menu* menuChoice = &options.at(selected);
		if (menuChoice->isLeaf())
		{
			return menuChoice->getMenuAction();
		}
		else
		{
			active = false;
			menuChoice->activate();
			menuChoice->setSelected(0);
			return menuChoice->getMenuAction();
		}
	}
	else
	{
		return options.at(findPath()).enterSelected();
	}
}

void Menu::goBack()
{
	if (active)
	{
		selected = -1;
		deActivate();
	}
	else
	{
		bool subMenuActive = false;
		int i;
		for (i = 0; i < int(options.size()); i++)
		{
			if (options.at(i).isActive())
			{
				subMenuActive = true;
			}
		}
		if (subMenuActive)
		{
			activate();
		}
		options.at(findPath()).goBack();
	}
}

MenuVisualData Menu::getVisuals()
{
	return MenuVisualData(*this);
}