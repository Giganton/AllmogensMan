#include "SquadManagerState.h"
#include "SquadManager.h"
#include "MenuVisualEvent.h"
#include "SquadManagerEvent.h"
#include "SquadManagerMenuState.h"

BrowseSquadsState::BrowseSquadsState(SquadManager* manager, int lvl) : SquadManagerState(manager, lvl)
{
	addSquad = Browsable();
	addSquad.setBrowserIcon(BrowsableIconTag::plusSign);
	initSquadBrowser();
}

void BrowseSquadsState::initSquadBrowser()
{
	squadList = squadManager->getFlagPointer()->getSquadPointers();
	std::vector<BrowsingData> browsingList;
	unsigned int i;
	for (i = 0; i < squadList.size(); i++)
	{
		browsingList.push_back(squadList.at(i)->getBrowserData());
	}
	browsingList.push_back(addSquad.getBrowserData());
	squadBrowser = Browser(browsingList, 1, -1, 4, CursorEdgeType::periodic);
	squadBrowser.activate();
	absorbBrowserEvents();
}

bool BrowseSquadsState::initNeeded()
{
	std::vector<Squad*> managerList = squadManager->getFlagPointer()->getSquadPointers();
	unsigned int i;
	if (managerList.size() == squadList.size())
	{
		for (i = 0; i < squadList.size(); i++)
		{
			if (squadList.at(i) != managerList.at(i))
			{
				return true;
			}
		}
	}
	else
	{
		return true;
	}
	return false;
}

void BrowseSquadsState::handleKeyPress(sf::Event keypress)
{
	squadBrowser.handleKeyPress(keypress);
	if (squadBrowser.allAnimationsFinished())
	{
		std::vector<int> selection = squadBrowser.getSelectedIndices();
		if (selection.size() != 1)
		{
			throw new std::exception();
		}
		if (selection.at(0) < (int)squadList.size())
		{
			Squad* selectedSquad1 = squadList.at(selection.at(0));
			openSquadMenu(selectedSquad1);
		}
		else if (selection.at(0) == squadList.size())
		{
			openSquadEditor();
		}
		else
		{
			throw new std::exception();
		}
	}
	absorbBrowserEvents();
}

void BrowseSquadsState::closeFollowers()
{
	SquadManagerState::closeFollowers();
	if (finishedEditing)
	{
		initSquadBrowser();
		finishedEditing = false;
	}
	else
	{
		squadBrowser.clearSelection();
	}
}

void BrowseSquadsState::absorbBrowserEvents()
{
	std::vector<BrowserEvent*> queue = squadBrowser.pullEventQueue();
	unsigned int i;
	for (i = 0; i < queue.size(); i++)
	{
		BrowsingSquadsEvent temp = BrowsingSquadsEvent(level, queue.at(i));
		eventQueue.addEvent(&temp);
		delete(queue.at(i));
	}
}

void BrowseSquadsState::openSquadMenu(Squad* selectedSquad1)
{
	nextLevel = new SquadMenuState(squadManager, level + 1, selectedSquad1, &finishedEditing);
	middleMan = true;
	OpenSquadMenuEvent temp = OpenSquadMenuEvent(level);
	eventQueue.addEvent(&temp);
}

void BrowseSquadsState::openSquadEditor()
{
	/*nextLevel = new SquadEditorState(squadManager, level + 1, &finishedEditing);
	middleMan = true;
	OpenSquadEditorEvent temp = OpenSquadEditorEvent(level);
	eventQueue.addEvent(&temp);*/
	openLink(new SquadEditorState(squadManager, level + 1, &finishedEditing));
}

StructuredEvent* BrowseSquadsState::getOpeningEvent()
{
	return new OpenSquadManagerEvent(level - 1);
}