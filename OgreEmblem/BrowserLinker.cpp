#include "BrowserLinker.h"

void BrowserLinker::handleKeyPress(sf::Event keypress)
{
	active->handleKeyPress(keypress);
	if (active->isCursorPassingEdge())
	{
		passCursor();
	}
}

void BrowserLinker::passCursor()
{
	BrowserSpot giverSpot = activeSpot;
	Direction passDir = active->getCursorPassingDir();
	BrowserSpot neighbourSpot = findNeighbour(passDir);
	Browser* neighbour = getBrowser(neighbourSpot);
	if (neighbour != nullptr)
	{
		active->stopCursor();
		active->deactivate();
		if (active->cursorHoldingItem())
		{
			BrowsingData passingItem = active->takeFromHand();
			neighbour->giveToHand(passingItem);
			passings.push_back(PassEvent(giverSpot, neighbourSpot));
		}
		
		neighbour->activate();
		active = neighbour;
		activeSpot = neighbourSpot;
	}
	else
	{
		active->allowCursor();
	}
}

std::vector<PassEvent> BrowserLinker::pullPassings()
{
	std::vector < PassEvent> temp = passings;
	passings.clear();
	return temp;
}

BrowserSpot BrowserLinker::findNeighbour(Direction dir)
{
	switch (activeSpot)
	{
	case BrowserSpot::center:
		switch (dir)
		{
		case Direction::up:
			return BrowserSpot::top;
			break;
		case Direction::left:
			return BrowserSpot::left;
			break;
		case Direction::right:
			return BrowserSpot::right;
			break;
		case Direction::down:
			return BrowserSpot::bottom;
			break;
		default:
			return BrowserSpot::none;
		}
	case BrowserSpot::left:
		switch (dir)
		{
		case Direction::right:
			return BrowserSpot::center;
			break;
		default:
			return BrowserSpot::none;
		}
	case BrowserSpot::right:
		switch (dir)
		{
		case Direction::left:
			return BrowserSpot::center;
			break;
		default:
			return BrowserSpot::none;
		}
	case BrowserSpot::top:
		switch (dir)
		{
		case Direction::down:
			return BrowserSpot::center;
			break;
		default:
			return BrowserSpot::none;
		}
	case BrowserSpot::bottom:
		switch (dir)
		{
		case Direction::up:
			return BrowserSpot::center;
			break;
		default:
			return BrowserSpot::none;
		}
	default:
		return BrowserSpot::none;
		break;
	}
}

Browser* BrowserLinker::getBrowser(BrowserSpot spot)
{
	switch (spot)
	{
	case BrowserSpot::center:
		return center;
		break;
	case BrowserSpot::top:
		return upper;
		break;
	case BrowserSpot::bottom:
		return down;
		break;
	case BrowserSpot::left:
		return left;
		break;
	case BrowserSpot::right:
		return right;
		break;
	default:
		return nullptr;
	}
}

void BrowserLinker::activateSpot(BrowserSpot spot)
{
	if (active != nullptr)
	{
		active->deactivate();
	}
	active = getBrowser(spot); 
	if (active == nullptr)
	{
		throw new std::exception();
	}
	active->activate(); 
	activeSpot = spot;
}

void BrowserLinker::addBrowser(Browser* brows, BrowserSpot spot)
{
	brows->deactivate();
	switch (spot)
	{
	case BrowserSpot::center:
		center = brows;
		break;
	case BrowserSpot::left:
		left = brows;
		break;
	case BrowserSpot::right:
		right = brows;
		break;
	case BrowserSpot::bottom:
		down = brows;
		break;
	case BrowserSpot::top:
		upper = brows;
		break;
	}
}