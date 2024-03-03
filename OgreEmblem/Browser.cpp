#include "Browser.h"

Browser::Browser(std::vector<BrowsingData> browsables, int nrOfItems, int rMax, int cMax, CursorEdgeType edgeT)
{
	items = browsables;
	rowMax = rMax;
	colMax = cMax;
	itemsToPick = nrOfItems;
	BrowserOpened* event = new BrowserOpened(getBrowserVisualData());
	eventQueue.push_back(event);

	cursorHandler = ListCursorHandler(browsables.size(), colMax, edgeT);
}

Browser::~Browser()
{
	unsigned int i;
	for (i = 0; i < eventQueue.size(); i++)
	{
		delete(eventQueue.at(i));
	}
}

Browser::Browser(const Browser& cpEQ)
{
	items = cpEQ.items;
	selected = cpEQ.selected;
	rowMax = cpEQ.rowMax;
	colMax = cpEQ.colMax;
	itemsToPick = cpEQ.itemsToPick;

	cursorHandler = cpEQ.cursorHandler;
	active = cpEQ.active;
	done = cpEQ.done;
	doneAtFilled = cpEQ.doneAtFilled;

	unsigned int i;
	for (i = 0; i < cpEQ.eventQueue.size(); i++)
	{
		eventQueue.push_back(cpEQ.eventQueue.at(i)->cloneAsBrowser());
	}
}

Browser& Browser::operator=(const Browser asEQ)
{
	items = asEQ.items;
	selected = asEQ.selected;
	rowMax = asEQ.rowMax;
	colMax = asEQ.colMax;
	itemsToPick = asEQ.itemsToPick;

	cursorHandler = asEQ.cursorHandler;
	active = asEQ.active;
	done = asEQ.done;
	doneAtFilled = asEQ.doneAtFilled;

	unsigned int i;
	for (i = 0; i < asEQ.eventQueue.size(); i++)
	{
		eventQueue.push_back(asEQ.eventQueue.at(i)->cloneAsBrowser());
	}

	return *this;
}

BrowsingData Browser::getItem(CursorPos mapPos)
{
	return items.at(findCursorIndex(mapPos));
}

void Browser::handleKeyPress(sf::Event keyPress)
{
	CursorPos start, dest;
	BrowserCursorMove graphicalEvent;
	if (!(keyPress.type == sf::Event::KeyPressed))
	{
		throw new std::exception();
	}
	switch (keyPress.key.code)
	{
	case sf::Keyboard::Up:
		start = cursorHandler.getCursorPos();
		cursorHandler.moveCursorUp();
		dest = cursorHandler.getCursorPos();
		if (!(start == dest))
		{
			eventQueue.push_back(new BrowserCursorMove(start, dest));
		}
		break;
	case sf::Keyboard::Down:
		start = cursorHandler.getCursorPos();
		cursorHandler.moveCursorDown();
		dest = cursorHandler.getCursorPos();
		if (!(start == dest))
		{
			eventQueue.push_back(new BrowserCursorMove(start, dest));
		}
		break;
	case sf::Keyboard::Left:
		start = cursorHandler.getCursorPos();
		cursorHandler.moveCursorLeft();
		dest = cursorHandler.getCursorPos();
		if (!(start == dest))
		{
			eventQueue.push_back(new BrowserCursorMove(start, dest));
		}
		break;
	case sf::Keyboard::Right:
		start = cursorHandler.getCursorPos();
		cursorHandler.moveCursorRight();
		dest = cursorHandler.getCursorPos();
		if (!(start == dest))
		{
			eventQueue.push_back(new BrowserCursorMove(start, dest));
		}
		break;
	case sf::Keyboard::X:
		toggleHovered();
		break;
	case sf::Keyboard::C:
		if (!isHoldingItem)
		{
			pickUpItem();
		}
		else
		{
			dropItem();
		}
		break;
	}
}

void Browser::allowCursor()
{
	CursorPos start, dest;
	start = cursorHandler.getCursorPos();
	cursorHandler.pass();
	dest = cursorHandler.getCursorPos();
	if (!(start == dest))
	{
		eventQueue.push_back(new BrowserCursorMove(start, dest));
	}
}

void Browser::pickUpItem()
{
	if (isHoldingItem) //if 
	{
		throw new std::exception();
	}

	int hoveredIndex = findCursorIndex();
	itemInHand = getHovered();

	if (itemInHand.isEmpty())
	{
		throw new std::exception();
	}

	BrowsingData emptyItem = BrowsingData(BrowsableIconTag::emptyUnit, 999);
	items.at(hoveredIndex) = emptyItem;
	isHoldingItem = true;
	eventQueue.push_back(new BrowserPickup(getCursorPos()));
}

void Browser::dropItem()
{
	if (!isHoldingItem)
	{
		throw new std::exception();
	}

	int hoveredIndex = findCursorIndex();
	BrowsingData itemInSpot = getHovered();

	if (!itemInSpot.isEmpty())
	{
		throw new std::exception();
	}

	items.at(hoveredIndex) = itemInHand;
	isHoldingItem = false;
	eventQueue.push_back(new BrowserDrop(getCursorPos()));
}

void Browser::swapItem()
{
	if (!isHoldingItem)
	{
		throw new std::exception();
	}
	int hoveredIndex = findCursorIndex();
	BrowsingData itemInSpot = getHovered();

	if (itemInSpot.isEmpty())
	{
		throw new std::exception();
	}
	items.at(hoveredIndex) = itemInHand;
	itemInHand = itemInSpot;
	eventQueue.push_back(new BrowserSwap(getCursorPos()));

}

std::vector<BrowserEvent*> Browser::pullEventQueue()
{
	std::vector<BrowserEvent*> temp = eventQueue;
	eventQueue.clear();
	return temp;
};

void Browser::select()
{
	if (selected.size() >= (unsigned int)itemsToPick)
	{
		throw new std::exception();
	}

	int index = findCursorIndex();
	selected.push_back(index);
	addSelectionEvent(index);
}

void Browser::toggleHovered()
{
	int index = findCursorIndex();

	unsigned int i;
	bool wasSelected = false;
	for (i = 0; i < selected.size(); i++)
	{
		if (selected.at(i) == index)
		{
			selected.erase(selected.begin() + i);
			wasSelected = true;
			break;
		}
	}
	if (!wasSelected)
	{
		if (selected.size() >= (unsigned int)itemsToPick)
		{
			throw new std::exception();
		}
		selected.push_back(index);
		if (selected.size() == itemsToPick && doneAtFilled)
		{
			done = true;
		}
	}
	addSelectionEvent(index);
}

void Browser::addSelectionEvent(int selectedIndex)
{
	SelectionMade* sel = new SelectionMade();
	sel->addToggled(selectedIndex);
	eventQueue.push_back(sel);
}

BrowsingData Browser::getHovered()
{
	int index = findCursorIndex();
	return items.at(index);
}

bool Browser::isHoveredSelected()
{
	int index = findCursorIndex();
	unsigned int i;
	for (i = 0; i < selected.size(); i++)
	{
		if (selected.at(i) == index)
		{
			return true;
		}
	}
	return false;

}

int Browser::findCursorIndex(CursorPos mapPos)
{
	return mapPos.y * colMax + mapPos.x;
}

int Browser::findCursorIndex()
{
	return findCursorIndex(getCursorPos());
}

void Browser::activate()
{
	active = true;
	BrowserActiveness* event = new BrowserActiveness(true);
	eventQueue.push_back(event);
}

void Browser::deactivate()
{
	active = false;
	BrowserActiveness* event = new BrowserActiveness(false);
	eventQueue.push_back(event);
}

std::vector<BrowsingData> Browser::getSelected()
{
	std::vector<BrowsingData> retVal;
	unsigned int i;
	for (i = 0; i < selected.size(); i++)
	{
		retVal.push_back(items.at(selected.at(i)));
	}
	return retVal;
}

BrowserVisualData Browser::getBrowserVisualData()
{
	std::vector<std::pair<BrowsableIcon, bool>> icons;
	unsigned int i, j;

	for (i = 0; i < items.size(); i++)
	{
		BrowsableIcon icon = items.at(i).getIcon();
		bool isSelected = false;
		for (j = 0; j < selected.size(); j++)
		{
			if (selected.at(j) == i)
			{
				isSelected = true;
			}
		}
		icons.push_back(std::pair<BrowsableIcon, bool>(icon, isSelected));
	}

	return BrowserVisualData(icons, colMax, cursorHandler.getCursorPos().x, cursorHandler.getCursorPos().y);
}

void Browser::giveToHand(BrowsingData data)
{
	if (isHoldingItem)
	{
		throw new std::exception();
	}
	itemInHand = data;
	isHoldingItem = true;
}

BrowsingData Browser::takeFromHand()
{
	if (!isHoldingItem)
	{
		throw new std::exception();
	}
	BrowsingData retval = itemInHand;
	itemInHand = BrowsingData();
	isHoldingItem = false;

	return retval;
}