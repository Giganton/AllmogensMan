#include "StatusScreen.h"
#include "GraphicsInterface.h"

StatusScreen::StatusScreen(int id, Squad* sqd) : Manager(id)
{
	shownSquad = sqd;
	//curHandler = CursorHandler("textures\\statusScreen\\cursor.png", TACTICAL_X, TACTICAL_Y, true);
	curHandler = GridCursorHandler(TACTICAL_X, TACTICAL_Y, CursorEdgeType::periodic);

	currentState = StatusState(StatusScreenStates::initial);
}

StatusScreen::StatusScreen(const StatusScreen& cpSS)
{
	if (cpSS.nextLevel == nullptr)
	{
		nextLevel = nullptr;
	}
	else
	{
		nextLevel = cpSS.nextLevel->allocateNew();
		*nextLevel = *cpSS.nextLevel;
	}
	middleMan = cpSS.middleMan;
	closeMe = cpSS.closeMe;
	ID = cpSS.ID;

	currentState = cpSS.currentState;
	prevStates = cpSS.prevStates;

	shownSquad = cpSS.shownSquad;

	curHandler = cpSS.curHandler;
	posToSwap = cpSS.posToSwap;
}

StatusScreen& StatusScreen::operator=(const StatusScreen asSS)
{
	if (asSS.nextLevel == nullptr)
	{
		nextLevel = nullptr;
	}
	else
	{
		nextLevel = asSS.nextLevel->allocateNew();
		*nextLevel = *asSS.nextLevel;
	}
	middleMan = asSS.middleMan;
	closeMe = asSS.closeMe;
	ID = asSS.ID;

	currentState = asSS.currentState;
	prevStates = asSS.prevStates;

	shownSquad = asSS.shownSquad;

	curHandler = asSS.curHandler;
	posToSwap = asSS.posToSwap;

	return *this;
}

ScreenVisualData StatusScreen::getVisuals()
{
	ScreenVisualData retVal;

	retVal.setUnitList(shownSquad->getUnitList());

	if (isMenuActive())
	{
		retVal.setActiveMenu(activeMenu);
	}

	retVal.setHovered(getHoveredUnit());
	retVal.setCursorPos(curHandler.getCursorPos());

	return retVal;
}

void StatusScreen::returnToPrevState()
{
	if (prevStates.size() == 0)
	{
		throw new std::exception();
	}
	currentState = prevStates.at(prevStates.size() - 1);
	loadFromState();
	prevStates.pop_back();
}

void StatusScreen::deleteHistory()
{
	prevStates = { };
}

void StatusScreen::handleKeyPress(sf::Event keyPress)
{
	if (currentState.isMenuActive())
	{
		controlMenu(keyPress);
	}
	else
	{
		controlStatusScreen(keyPress);
	}
}

void StatusScreen::controlStatusScreen(sf::Event keyPress)
{
	if (!(keyPress.type == sf::Event::KeyPressed))
	{
		throw new std::exception();
	}
	switch (keyPress.key.code)
	{
	case sf::Keyboard::Z:
		if (currentState.getState() == StatusScreenStates::initial)
		{
			closeMe = true;
		}
		else
		{
			returnToPrevState();
		}
		break;
	case sf::Keyboard::Up:
		curHandler.moveCursorUp();
		break;
	case sf::Keyboard::Down:
		curHandler.moveCursorDown();
		break;
	case sf::Keyboard::Left:
		curHandler.moveCursorLeft();
		break;
	case sf::Keyboard::Right:
		curHandler.moveCursorRight();
		break;
	case sf::Keyboard::X:
		switch (currentState.getState())
		{
		case StatusScreenStates::initial:
			openMenu(createStatusMenu());
			break;
		case StatusScreenStates::swapping:
			openMenu(createSwapMenu());
			break;
		}
		break;
	}
}

void StatusScreen::saveState()
{
	prevStates.push_back(currentState);
}

void StatusScreen::loadFromState()
{
	if (currentState.isMenuActive())
	{
		activeMenu = currentState.getMenu();
	}
	if (currentState.getState() == StatusScreenStates::initial)
	{
		curHandler.setCursorPos(CursorPos(currentState.getCursorPosX(), currentState.getCursorPosY()));
	}
	else if (currentState.getState() == StatusScreenStates::swapping)
	{
		curHandler.setCursorPos(CursorPos(currentState.getCursorPosX(), currentState.getCursorPosY()));
		posToSwap = currentState.getSwappingPos();
	}
}

void StatusScreen::captureState()
{
	if (currentState.isMenuActive())
	{
		currentState.setMenu(activeMenu);
	}
	if (currentState.getState() == StatusScreenStates::initial)
	{
		CursorPos mapPos = curHandler.getCursorPos();
		currentState.setCursorPos(mapPos.x, mapPos.y);
	}
	else if (currentState.getState() == StatusScreenStates::swapping)
	{
		currentState.setCursorPos(CursorPos(currentState.getCursorPosX(), currentState.getCursorPosY()));
		currentState.setSwappingPos(posToSwap);
	}
}

Unit* StatusScreen::getHoveredUnit()
{
	CursorPos mapPos = curHandler.getCursorPos();
	return shownSquad->getUnitPtr(mapPos.x, mapPos.y);
}

void StatusScreen::initSwap()
{
	posToSwap = curHandler.getCursorPos();
	goToState(StatusScreenStates::swapping, true, false);
}

void StatusScreen::performSwap()
{
	if (currentState.getState() != StatusScreenStates::swapping)
	{
		throw new std::exception();
	}
	CursorPos currPos = curHandler.getCursorPos();
	shownSquad->swapUnits(SquadPos(posToSwap.x, posToSwap.y), SquadPos(currPos.x, currPos.y));

	goToState(StatusScreenStates::initial, true, true);
}

void StatusScreen::performMenuAction(int action)
{
	switch (action)
	{
	case StatusScreenMenuActions::initializeSwap:
		initSwap();
		break;
	case StatusScreenMenuActions::performSwap:
		performSwap();
		break;
	case StatusScreenMenuActions::closeStatusMenu:
		closeMenu();
		//goToState(StatusScreenStates::initial, true, true);
		break;
	}
}

Menu StatusScreen::createStatusMenu()
{
	std::string title = "Infomeny";

	Menu option1 = Menu("Byt plats", StatusScreenMenuActions::initializeSwap);
	Menu option2 = Menu("Avbryt", StatusScreenMenuActions::closeStatusMenu);
	std::vector<Menu> options = { option1, option2 };

	return Menu(title, options);
}

Menu StatusScreen::createSwapMenu()
{
	std::string title = "Bytmeny";

	Menu option1 = Menu("Byt hit", StatusScreenMenuActions::performSwap);
	Menu option2 = Menu("Avbryt", StatusScreenMenuActions::closeStatusMenu);
	std::vector<Menu> options = { option1, option2 };

	return Menu(title, options);
}

void StatusScreen::compileVisualStack(GraphicsInterface* graphInt)
{
	graphInt->getVisualStackPointer()->setStatusScreenVisuals(getVisuals());
	if (middleMan)
	{
		nextLevel->compileVisualStack(graphInt);
	}
}

/**************** StatusState *********************/

StatusState::StatusState(int st)
{
	switch (st)
	{
	case StatusScreenStates::initial:
		state = st;
		menuIsActive = false;
		break;
	case StatusScreenStates::swapping:
		state = st;
		menuIsActive = false;
		break;
	}
}

void StatusState::enterState(int st)
{
	switch (st)
	{
	case StatusScreenStates::initial:
		state = st;
		menuIsActive = false;

		cursorPosX = 0;
		cursorPosY = 0;
		break;
	case StatusScreenStates::swapping:
		state = st;
		menuIsActive = false;
		break;
	}
}