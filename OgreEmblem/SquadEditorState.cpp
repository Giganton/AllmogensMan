#include "SquadManagerState.h"
#include "SquadManager.h"
#include "MenuVisualEvent.h"
#include "SquadManagerEvent.h"
#include "SquadManagerMenuState.h"


SquadEditorState::SquadEditorState(SquadManager* manager, int level, bool* finishContainer) : SquadManagerState(manager, level)
{
	editing = false;
	squadManager = manager;
	initUnitBrowser();
	initSquadBrowser();
	browserCluster = BrowserLinker();
	browserCluster.addBrowser(&squadBrowser, BrowserSpot::center);
	browserCluster.addBrowser(&unitBrowser, BrowserSpot::right);
	browserCluster.activateSpot(BrowserSpot::center);

	finishedEditing = finishContainer;
	*finishedEditing = false;

	absorbBrowserEvents();
}

SquadEditorState::SquadEditorState(Squad squad, SquadManager* manager, int level, bool* finishContainer) : SquadManagerState(manager, level)
{
	editedSquad = squad;
	editing = true;

	squadManager = manager;
	initUnitBrowser();
	initSquadBrowser(editedSquad);
	browserCluster = BrowserLinker();
	browserCluster.addBrowser(&squadBrowser, BrowserSpot::center);
	browserCluster.addBrowser(&unitBrowser, BrowserSpot::right);
	browserCluster.activateSpot(BrowserSpot::center);

	finishedEditing = finishContainer;
	*finishedEditing = false;

	absorbBrowserEvents();
}

void SquadEditorState::initSquadBrowser()
{
	std::vector<BrowsingData> startingIcons;
	unsigned int i;
	for (i = 0; i < 8; i++)
	{
		BrowsingData temp;
		temp.setID(-2 - i);
		temp.setIcon(BrowsableIconTag::emptyUnit);
		startingIcons.push_back(temp);
	}
	squadBrowser = Browser(startingIcons, 1, 4, 2, CursorEdgeType::controlled);
	absorbBrowserEvents();
}

void SquadEditorState::initSquadBrowser(Squad squad)
{
	std::vector<BrowsingData> startingIcons;
	unsigned int i, j;
	for (j = 0; j < TACTICAL_Y; j++)
	{
		for (i = 0; i < TACTICAL_X; i++)
		{
			if (squad.getTile(i, j)->isEmpty())
			{
				BrowsingData temp;
				temp.setID(-2 - i);
				temp.setIcon(BrowsableIconTag::emptyUnit);
				startingIcons.push_back(temp);
			}
			else
			{
				Unit* unit = squad.getUnitPtr(i, j);
				BrowsingData temp = unit->getBrowserData();
				temp.setID(unit->getID());
				temp.setBrowserTag(BrowserTag::green);
				startingIcons.push_back(temp);
			}
		}
	}
	squadBrowser = Browser(startingIcons, 1, 4, 2, CursorEdgeType::controlled);
	absorbBrowserEvents();
}

void SquadEditorState::initUnitBrowser()
{
	bench = squadManager->getFlagPointer()->getBench();
	std::vector<BrowsingData> benchIcons;
	unsigned int i, j;
	for (i = 0; i < bench.size(); i++)
	{
		if (i == bench.size() - 1)
		{
			BrowsingData temp;
			temp.setIcon(BrowsableIconTag::unitKnightRed);
			temp.setID(bench.at(i).getID());
			temp.setBrowserTag(BrowserTag::blue);
			benchIcons.push_back(temp);
		}
		else
		{
			BrowsingData temp;
			temp = bench.at(i).getBrowserData();
			temp.setID(bench.at(i).getID());
			temp.setBrowserTag(BrowserTag::blue);

			benchIcons.push_back(temp);
		}
	}
	for (j = 0; j < 20 - bench.size(); j++)
	{
		BrowsingData temp;
		temp.setID(-2 - i);
		temp.setIcon(BrowsableIconTag::emptyUnit);
		benchIcons.push_back(temp);

	}
	unitBrowser = Browser(benchIcons, 1, 5, 5, CursorEdgeType::controlled);
	absorbBrowserEvents();
}

void SquadEditorState::goToLeaderSelection()
{
	selectingLeader = true;
	browserCluster.activateSpot(BrowserSpot::center);
	squadBrowser.setBorderType(CursorEdgeType::stop);
}

void SquadEditorState::handleKeyPress(sf::Event keypress)
{
	switch (keypress.key.code)
	{
	case sf::Keyboard::Enter:
		if (!selectingLeader)
		{
			goToLeaderSelection();
			break;
		}
	}
	browserCluster.handleKeyPress(keypress);

	squadBrowserFinished();
	unitBrowserFinished();

	absorbBrowserEvents();
	absorbBrowserEvents();
}

void SquadEditorState::finishEditing()
{
	if (editing)
	{
		squadManager->getFlagPointer()->emptySquad(editedSquad.getID());
	}
	createSquad(selectedLeaderID);
	*finishedEditing = true;
}

void SquadEditorState::squadBrowserFinished()
{
	if (squadBrowser.allAnimationsFinished())
	{
		std::vector<BrowsingData> selection = squadBrowser.getSelected();
		if (selection.at(0).isEmpty())
		{
			if (squadBrowser.cursorHoldingItem())
			{
				squadBrowser.dropItem();
			}
			squadBrowser.clearSelection();
		}
		else
		{
			if (selection.size() != 1)
			{
				throw new std::exception();
			}
			BrowsingData bData = selection.at(0);
			Unit* selectedUnit = findUnit(bData);

			if (selectingLeader)
			{
				openUnitMenu(selectedUnit, UnitMenuVariant::selectingLeader);
			}
			else
			{
				if (squadBrowser.cursorHoldingItem())
				{
					openUnitMenu(selectedUnit, UnitMenuVariant::holdingUnit);
				}
				else
				{
					openUnitMenu(selectedUnit, UnitMenuVariant::hoveringUnit);
				}
			}
		}
	}
}

Unit* SquadEditorState::findUnit(BrowsingData bData)
{
	Unit* unit = nullptr;
	if (bData.getBrowserTag() == BrowserTag::green)
	{
		editedSquad.findUnit(bData.getID());
	}
	else if (bData.getBrowserTag() == BrowserTag::blue)
	{
		unit = squadManager->getFlagPointer()->getUnitPtr(bData.getID());
	}
	else
	{
		throw new std::exception();
	}
	return unit;
}

void SquadEditorState::closeFollowers()
{
	SquadManagerState::closeFollowers();
	if (menuCommand != UnitMenuCommand::none)
	{
		switch (menuCommand)
		{
		case UnitMenuCommand::pickUpUnit:
			browserCluster.getActiveBrowser()->pickUpItem();
			absorbBrowserEvents();
			break;
		case UnitMenuCommand::swapUnit:
			browserCluster.getActiveBrowser()->swapItem();
			absorbBrowserEvents();
			break;
		case UnitMenuCommand::selectAsLeader:
			selectedLeaderID = squadBrowser.getHovered().getID();
			finishEditing();
			closeMe = true;
			break;
		default:
			break;
		}
		menuCommand = UnitMenuCommand::none;
	}
	squadBrowser.clearSelection();
	unitBrowser.clearSelection();
}

void SquadEditorState::unitBrowserFinished()
{
	if (unitBrowser.allAnimationsFinished())
	{
		std::vector<BrowsingData> selection = unitBrowser.getSelected();
		if (selection.at(0).isEmpty())
		{
			if (unitBrowser.cursorHoldingItem())
			{
				unitBrowser.dropItem();
				unitBrowser.clearSelection();
			}
			unitBrowser.clearSelection();
		}
		else
		{
			if (selection.size() != 1)
			{
				throw new std::exception();
			}

			BrowsingData bData = selection.at(0);
			Unit* selectedUnit = findUnit(bData);
			if (unitBrowser.cursorHoldingItem())
			{
				openUnitMenu(selectedUnit, UnitMenuVariant::holdingUnit);
			}
			else
			{
				openUnitMenu(selectedUnit, UnitMenuVariant::hoveringUnit);
			}
		}
	}
}

void SquadEditorState::openUnitMenu(Unit* selectedUnit, UnitMenuVariant variant)
{
	/*nextLevel = new UnitMenuState(squadManager, level + 1, selectedUnit, &menuCommand, variant);
	middleMan = true;
	OpenUnitMenuEvent temp = OpenUnitMenuEvent(level);
	eventQueue.addEvent(&temp);*/

	openLink(new UnitMenuState(squadManager, level + 1, selectedUnit, &menuCommand, variant));
}

void SquadEditorState::createSquad(int leaderID)
{
	std::pair<bool, int> temp;
	std::vector<BrowsingData> units = squadBrowser.getItems();
	std::vector<std::pair<bool, int>> frontRow;
	std::vector<std::pair<bool, int>> backRow;
	unsigned int i;
	for (i = 0; i < TACTICAL_Y; i++)
	{
		BrowsingData frontUnit = squadBrowser.getItem(CursorPos(1, i));
		BrowsingData backUnit = squadBrowser.getItem(CursorPos(0, i));

		if (!frontUnit.isEmpty())
		{
			temp.first = false;
			temp.second = frontUnit.getID();
		}
		else
		{
			temp.first = true;
			temp.second = -1;
		}
		frontRow.push_back(temp);

		if (!backUnit.isEmpty())
		{
			temp.first = false;
			temp.second = backUnit.getID();
		}
		else
		{
			temp.first = true;
			temp.second = -1;
		}
		backRow.push_back(temp);
	}
	if (editing)
	{
		squadManager->getFlagPointer()->fillSquad(editedSquad.getID(), frontRow, backRow, leaderID);
	}
	else
	{
		throw new std::exception();
		//squadManager->getFlagPointer()->formNewSquad(frontRow, backRow, leaderID);
	}
}

void SquadEditorState::absorbBrowserEvents()
{
	std::vector<BrowserEvent*> queue = unitBrowser.pullEventQueue();
	unsigned int i;
	for (i = 0; i < queue.size(); i++)
	{
		EditStateBrowserEvent temp = EditStateBrowserEvent(level, queue.at(i), false);
		eventQueue.addEvent(&temp);
		delete(queue.at(i));
	}
	queue = squadBrowser.pullEventQueue();
	for (i = 0; i < queue.size(); i++)
	{
		EditStateBrowserEvent temp = EditStateBrowserEvent(level, queue.at(i), true);
		eventQueue.addEvent(&temp);
		delete(queue.at(i));
	}
	std::vector<PassEvent> passEvents = browserCluster.pullPassings();
	for (i = 0; i < passEvents.size(); i++)
	{
		bool r2l;
		PassEvent passing = passEvents.at(i);
		if (passing.start == BrowserSpot::right && passing.dest == BrowserSpot::center)
		{
			r2l = true;
		}
		else if (passing.start == BrowserSpot::center && passing.dest == BrowserSpot::right)
		{
			r2l = false;
		}
		else
		{
			throw new std::exception();
		}
		EditStatePassCursorEvent temp = EditStatePassCursorEvent(level, r2l);
		eventQueue.addEvent(&temp);
	}
}

StructuredEvent* SquadEditorState::getOpeningEvent()
{
	return new OpenSquadEditorEvent(level - 1);
}