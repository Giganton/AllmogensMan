#include "DraftScreenState.h"
#include "OpenDraftScreenEvent.h"
#include "InitDraftScreenEvent.h"
#include "Flag.h"
#include "SelectUnitEvent.h"
#include "SelectSquadEvent.h"
#include "UnitsSwappedEvent.h"
#include "UnitBoughtEvent.h"
#include "ConfirmationState.h"
#include "ReloadSquadListEvent.h"
#include "StringHandler.h"
#include "SquadNamePickerState.h"

DraftScreenState::DraftScreenState(int lvl, Flag* player, std::vector<Unit> unitsToPick, IdCreator* idCr, StringHandler* strHandler)
{
	level = lvl;
	playerTeam = player;
	draftChoices = unitsToPick;

	stateHandler = StateHandler(DraftScreenStateState::DSSS_browsing);

	squadCreator = idCr;
	stringHandler = strHandler;

	std::vector<Squad> squadData;
	std::vector<UnitData> unitData;

	newSquadNameBucket = new std::string();

	std::vector<Squad> squads = player->getSquads();
	unsigned int i;
	for (i = 0; i < unitsToPick.size(); i++)
	{
		unitData.push_back(unitsToPick.at(i).getData());
	}
	InitDraftScreenEvent evnt = InitDraftScreenEvent(level, squads, unitData);
	eventQueue.addEvent(&evnt);
}

StructuredEvent* DraftScreenState::getOpeningEvent()
{
	return new OpenDraftScreenEvent(level - 1);
}

void DraftScreenState::handleKeyPress(sf::Event inputEvent)
{

}

std::pair<Squad*, Unit*> DraftScreenState::decipherUnitInSquadSignal(MouseSignal signal)
{
	std::pair<Squad*, Unit*> retVal;

	if (signal.getHoveredId() == DraftMouseButtons::unitInShop)
	{
		throw new std::exception();
	}
	else if (signal.getHoveredId() == DraftMouseButtons::unitInSquad)
	{
		Squad* sqd = nullptr;
		if (signal.getPayload().at(0) == 1)
		{
			if (!squad1Selected)
			{
				throw new std::exception();
			}
			sqd = selectedSquad1;
		}
		else if (signal.getPayload().at(0) == 2)
		{
			if (!squad2Selected)
			{
				throw new std::exception();
			}
			sqd = selectedSquad2;
		}
		else
		{
			throw new std::exception();
		}
		retVal.first = sqd;
		//retVal.second = sqd->findUnitPtr(signal.getPayload().at(1));
		retVal.second = sqd->getUnitPtr(SquadPos(signal.getPayload().at(1)));
	}
	else if (signal.getHoveredId() == DraftMouseButtons::emptySpotInSquad)
	{
		Squad* sqd = nullptr;
		if (signal.getPayload().at(0) == 1)
		{
			if (!squad1Selected)
			{
				throw new std::exception();
			}
			sqd = selectedSquad1;
		}
		else if (signal.getPayload().at(0) == 2)
		{
			if (!squad2Selected)
			{
				throw new std::exception();
			}
			sqd = selectedSquad2;
		}
		else
		{
			throw new std::exception();
		}
		retVal.first = sqd;
		retVal.second = nullptr;
	}
	else
	{
		throw new std::exception();
	}

	return retVal;
}

Squad* DraftScreenState::decipherSquadSignal(MouseSignal signal)
{
	if (signal.getHoveredId() != DraftMouseButtons::squad)
	{
		throw new std::exception();
	}

	return playerTeam->getSquadPointer(signal.getPayload().at(0));
}

void DraftScreenState::performClickSquadSwap(MouseSignal oldClick, MouseSignal newClick)
{
	std::pair<Squad*, Unit*>  oldUnit = decipherUnitInSquadSignal(oldClick);
	std::pair<Squad*, Unit*>  newUnit = decipherUnitInSquadSignal(newClick);

	if (newClick.getHoveredId() == DraftMouseButtons::emptySpotInSquad)
	{
		Unit temp = *oldUnit.second;
		oldUnit.first->removeUnit(SquadPos(oldClick.getPayload().at(1)));
		newUnit.first->addUnit(temp, SquadPos(newClick.getPayload().at(1)));
	}
	else if (oldUnit.first == newUnit.first)
	{
		oldUnit.first->swapUnitPositions(oldUnit.second->getID(), newUnit.second->getID());
	}
	else
	{
		Unit tempUnit = oldUnit.first->insertSwapUnits(oldUnit.second->getID(), *newUnit.second);
		newUnit.first->insertSwapUnits(newUnit.second->getID(), tempUnit);
	}
	UnitsSwappedEvent evnt = UnitsSwappedEvent(level, *oldUnit.first, *newUnit.first);
	eventQueue.addEvent(&evnt);
}

void DraftScreenState::handleEmptyPortraitSquadClick(MouseSignal signal)
{
	switch (stateHandler.getState())
	{
	case DraftScreenStateState::DSSS_browsing:
		handleEmptyPortraitSquadClick_browsing(signal);
		break;
	case DraftScreenStateState::DSSS_addingSquad:
		handleEmptyPortraitSquadClick_addingSquad(signal);
		break;
	default:
		throw new std::exception();
		break;
	}
}

void DraftScreenState::handleEmptyPortraitSquadClick_addingSquad(MouseSignal signal)
{
	bool unitIsLeader = false;
	if (signal.getHoveredId() == DraftMouseButtons::emptySpotInSquad && signal.getPayload().at(0) == 1)
	{
		if (unitClicked && clickedUnit.getHoveredId() == DraftMouseButtons::unitInSquad)
		{
			if (clickedUnit.getHoveredId() == DraftMouseButtons::unitInSquad)
			{
				unitIsLeader = decipherUnitInSquadSignal(clickedUnit).second->isLeader();
				
			}

			if (!unitIsLeader) 
			{
				std::string leaderName;
				if (clickedUnit.getHoveredId() == DraftMouseButtons::unitInSquad)
				{
					leaderName = decipherUnitInSquadSignal(clickedUnit).second->getName();
				}
				else if (clickedUnit.getHoveredId() == DraftMouseButtons::unitInShop)
				{
					leaderName = draftChoices.getUnit(clickedUnit.getPayload().at(0)).getName();
				}
				std::string confirmString1 = stringHandler->getDraftPhrase(DraftStringID::enumConfirmNewLeader1);
				std::string confirmString2 = stringHandler->getDraftPhrase(DraftStringID::enumConfirmNewLeader2);
				std::string totString = confirmString1 + leaderName + confirmString2;
				openLink(new ConfirmationState(level + 1, totString, stringHandler->getDraftPhrase(DraftStringID::enumConfirmLeaderButtonText), stringHandler->getDraftPhrase(DraftStringID::enumDenyLeaderButtonText),  &newSquadConfirmed));
				stateHandler.addState(DraftScreenStateState::DSSS_addSquadPendingConfirmation);
				newSquadLeaderPosition = signal;
			}
			else
			{
				deselectUnit();
			}
		}
	}
}

void DraftScreenState::handleEmptyPortraitSquadClick_browsing(MouseSignal signal)
{
	bool unselectedClick = false;
	if (signal.getHoveredId() == DraftMouseButtons::emptySpotInSquad)
	{
		if ((signal.getPayload().at(0) == 1 && !squad1Selected) || (signal.getPayload().at(0) == 2 && !squad2Selected))
		{
			unselectedClick = true;
		}
	}
	if (unitClicked && ! unselectedClick)
	{
		if (clickedUnit.getHoveredId() == DraftMouseButtons::unitInSquad)
		{
			//Squad* oldSquad = decipherSquadSignal(clickedUnit);
			//Squad* newSquad = decipherSquadSignal(signal);

			std::pair<Squad*, Unit*> oldUnit = decipherUnitInSquadSignal(clickedUnit);
			std::pair<Squad*, Unit*> newUnit = decipherUnitInSquadSignal(signal);
			Squad* oldSquad = oldUnit.first;
			Squad* newSquad = newUnit.first;
			bool leaderSwap = (oldSquad->getID() != newSquad->getID()) && (oldUnit.second->isLeader());
			if (!leaderSwap)
			{
				performClickSquadSwap(clickedUnit, signal);
				/*Unit temp = *oldUnit.second;
				oldSquad->removeUnit(clickedUnit.getPayload().at(1));
				newSquad->addUnit(temp, signal.getPayload().at(1));

				/*unsigned int i;
				std::vector<UnitData> unitData;
				for (i = 0; i < draftChoices.getInventory().size(); i++)
				{
					unitData.push_back(draftChoices.getInventory().at(i).getData());
				}*/
				/*UnitsSwappedEvent evnt = UnitsSwappedEvent(level, *oldUnit.first, *newUnit.first);
				eventQueue.addEvent(&evnt);*/

				deselectUnit();
			}
			else
			{
				deselectUnit();
			}
		}
		else if (clickedUnit.getHoveredId() == DraftMouseButtons::unitInShop)
		{
			Unit boughtUnit = draftChoices.buyUnit(clickedUnit.getPayload().at(0));
			Squad* newSquad = decipherUnitInSquadSignal(signal).first;
			newSquad->addUnit(boughtUnit, SquadPos(signal.getPayload().at(1)));
			deselectUnit();
			UnitBoughtEvent evnt = UnitBoughtEvent(level, *newSquad, boughtUnit.getID());
			eventQueue.addEvent(&evnt);
		}
	}
}

void DraftScreenState::handleUnitInSquadClick(MouseSignal signal)
{
	if (!unitClicked)
	{
		selectUnit(latestSignal);
	}
	else if (clickedUnit.getHoveredId() == DraftMouseButtons::unitInShop)
	{
		deselectUnit();
		selectUnit(latestSignal);
	}
	//swap between squads
	else if (clickedUnit.getHoveredId() == DraftMouseButtons::unitInSquad && latestSignal.getHoveredId() == DraftMouseButtons::unitInSquad)
	{
		//Squad* oldSquad = decipherSquadSignal(clickedUnit);
		//Squad* newSquad = decipherSquadSignal(latestSignal);
		std::pair<Squad*, Unit*>  oldUnit = decipherUnitInSquadSignal(clickedUnit);
		std::pair<Squad*, Unit*>  newUnit = decipherUnitInSquadSignal(latestSignal);
		bool leaderSwap = (oldUnit.first->getID() != newUnit.first->getID()) && (oldUnit.second->isLeader() || newUnit.second->isLeader()); //man får inte flytta leader mellan följen
		if (leaderSwap)
		{
			deselectUnit();
		}
		else if (oldUnit.second->getID() != newUnit.second->getID())
		{
			performClickSquadSwap(clickedUnit, latestSignal);

			unsigned int i;
			std::vector<UnitData> unitData;
			for (i = 0; i < draftChoices.getInventory().size(); i++)
			{
				unitData.push_back(draftChoices.getInventory().at(i).getData());
			}
			//InitDraftScreenEvent evnt = InitDraftScreenEvent(level, playerTeam->getSquads(), unitData);
			//eventQueue.addEvent(&evnt);
			deselectUnit();
		}
		else
		{
			deselectUnit();
		}
	}
}

void DraftScreenState::handleUnitInShopClick(MouseSignal signal)
{
	bool clickedSame = false;
	if (unitClicked)
	{
		deselectUnit();
		if (clickedUnit.getHoveredId() == DraftMouseButtons::unitInShop && signal.getHoveredId() == DraftMouseButtons::unitInShop && clickedUnit.getPayload().at(0) == signal.getPayload().at(0))
		{
			clickedSame = true;
		}
	}
	if (signal.getHoveredId() == DraftMouseButtons::unitInShop && !clickedSame)
	{

		selectUnit(signal);
	}
	else if (signal.getHoveredId() == DraftMouseButtons::emptySpotInShop)
	{

	}
}

void DraftScreenState::handleNewSquadButtonClick()
{
	SelectSquadEvent evnt;
	switch (stateHandler.getState())
	{
	case DraftScreenStateState::DSSS_browsing:
		enterAddSquadState();
		newSquadSlot = squadCreator->createSquad();

		evnt = SelectSquadEvent(level);
		eventQueue.addEvent(&evnt);
		break;
	case DraftScreenStateState::DSSS_addingSquad:
		deselectSquad(true);
		enterBrowsingState();
		//stateHandler.backOneStep();
		break;
	default:
		throw new std::exception();
	}
}

void DraftScreenState::enterAddSquadState()
{
	stateHandler.addState(DraftScreenStateState::DSSS_addingSquad);
	deselectUnit();
	deselectSquad(true);
	deselectSquad(false);
}

void DraftScreenState::enterBrowsingState()
{
	stateHandler.setState(DraftScreenStateState::DSSS_browsing);
	//ReloadSquadListEvent evnt = ReloadSquadListEvent(level, playerTeam->getSquads());
	//eventQueue.addEvent(&evnt);
}

void DraftScreenState::enterNamingState(std::string leaderName)
{
	stateHandler.addState(DraftScreenStateState::DSSS_addSquadNamingSquad);
	openLink(new SquadNamePickerState(newSquadNameBucket, leaderName, level + 1, stringHandler));
}

void DraftScreenState::handleSquadInfoWindowClick(MouseSignal signal)
{
	if (signal.getHoveredId() == DraftMouseButtons::unitInSquad)
	{
		handleUnitInSquadClick(signal);
	}
	else if (signal.getHoveredId() == DraftMouseButtons::emptySpotInSquad)
	{
		handleEmptyPortraitSquadClick(signal);
	}
	else
	{
		throw new std::exception();
	}
}

void DraftScreenState::handleSquadClick(MouseSignal signal)
{
	switch (stateHandler.getState())
	{
	case DraftScreenStateState::DSSS_browsing:
		handleSquadClick_browsing(signal);
		break;
	case DraftScreenStateState::DSSS_addingSquad:
		handleSquadClick_addingSquad(signal);
		break;
	default:
		throw new std::exception();
		break;
	}
}

void DraftScreenState::handleSquadClick_addingSquad(MouseSignal signal)
{
	if (squad2Selected)
	{
		if (decipherSquadSignal(signal)->getID() != selectedSquad2->getID())
		{
			deselectSquad(false);
			selectSquad(signal, false);
		}
	}
	else
	{
		selectSquad(signal, false);
	}
}

void DraftScreenState::handleSquadClick_browsing(MouseSignal signal)
{
	if (squad1Selected && decipherSquadSignal(signal)->getID() == selectedSquad1->getID())
	{
		deselectSquad(true);
	}
	else if (squad2Selected && decipherSquadSignal(signal)->getID() == selectedSquad2->getID())
	{
		deselectSquad(false);
	}
	else if (!squad1Selected)
	{
		selectSquad(signal, true);
	}
	else if (!squad2Selected)
	{
		selectSquad(signal, false);
	}
	else
	{

	}
}

void DraftScreenState::handleMouseClickLeft(sf::Event mouseEvent)
{
	if (latestSignal.getHoveredId() == DraftMouseButtons::none)
	{
		deselectUnit();
	}
	if (latestSignal.getHoveredId() == DraftMouseButtons::squad)
	{
		handleSquadClick(latestSignal);
	}
	if (latestSignal.getHoveredId() == DraftMouseButtons::emptySpotInSquad || latestSignal.getHoveredId() == DraftMouseButtons::unitInSquad)
	{
		handleSquadInfoWindowClick(latestSignal);
	}
	if (latestSignal.getHoveredId() == DraftMouseButtons::unitInShop || latestSignal.getHoveredId() == DraftMouseButtons::emptySpotInShop)
	{
		handleUnitInShopClick(latestSignal);
	}
	if (latestSignal.getHoveredId() == DraftMouseButtons::newSquadButton)
	{
		handleNewSquadButtonClick();
	}
	if (latestSignal.getHoveredId() == DraftMouseButtons::doneManagingSquads)
	{
		openLink(new ConfirmationState(level + 1, stringHandler->getDraftPhrase(DraftStringID::enumConfirmDoneText), stringHandler->getDraftPhrase(DraftStringID::enumConfirmLeaderButtonText), stringHandler->getDraftPhrase(DraftStringID::enumDenyLeaderButtonText), &closeConfirmed));
		stateHandler.addState(DraftScreenStateState::DSSS_leavePagePendingConfirmation);
	}
}

void DraftScreenState::handleMouseEvent(sf::Event mouseEvent)
{
	if (mouseEvent.type == sf::Event::MouseButtonPressed)
	{
		if (mouseEvent.mouseButton.button == sf::Mouse::Left)
		{
			handleMouseClickLeft(mouseEvent);
		}
	}
}

void DraftScreenState::clickTestButton()
{

}

void DraftScreenState::selectUnit(MouseSignal signal)
{
	clickedUnit = signal;
	unitClicked = true;
	SelectUnitEvent evnt(level, signal);
	eventQueue.addEvent(&evnt);
}

void DraftScreenState::deselectUnit()
{
	unitClicked = false;
	SelectUnitEvent evnt(level);
	eventQueue.addEvent(&evnt);
}

void DraftScreenState::deselectSquad(bool windowOne)
{
	SelectSquadEvent evnt = SelectSquadEvent(level, windowOne);
	eventQueue.addEvent(&evnt);

	if (unitClicked && clickedUnit.getHoveredId() == DraftMouseButtons::unitInSquad)
	{
		int selectedSquadID;
		if (windowOne)
		{
			selectedSquadID = selectedSquad1->getID();
		}
		else
		{
			selectedSquadID = selectedSquad2->getID();
		}

		if (decipherUnitInSquadSignal(clickedUnit).first->getID() == selectedSquadID)
		{
			deselectUnit();
		}
	}

	if (windowOne)
	{
		squad1Selected = false;
	}
	else
	{
		squad2Selected = false;
	}
}

int DraftScreenState::findSquadWithUnit(int unitID)
{
	std::vector<Squad> sqdList = playerTeam->getSquads();
	unsigned int i;

	for (i = 0; i < sqdList.size(); i++)
	{
		if (sqdList.at(i).isThisUnitIn(unitID))
		{
			return sqdList.at(i).getID();
		}
	}
	throw new std::exception();
	return false;
}

Squad* DraftScreenState::findSquadPointer(int sqdID)
{
	return playerTeam->getSquadPointer(sqdID);
}

Unit* DraftScreenState::findUnitPointer(int unitID)
{
	return findSquadPointer(findSquadWithUnit(unitID))->findUnitPtr(unitID);
}

void DraftScreenState::selectSquad(MouseSignal signal, bool windowOne)
{
	SelectSquadEvent evnt(level, signal, windowOne);
	eventQueue.addEvent(&evnt);
	if (windowOne)
	{
		selectedSquad1 = decipherSquadSignal(signal);
		squad1Selected = true;
	}
	else
	{
		selectedSquad2 = decipherSquadSignal(signal);
		squad2Selected = true;
	}
}

void DraftScreenState::selectSquad(Squad* sqd, bool windowOne)
{
	SelectSquadEvent evnt(level, *sqd, windowOne);
	eventQueue.addEvent(&evnt);
	if (windowOne)
	{
		selectedSquad1 = sqd;
		squad1Selected = true;
	}
	else
	{
		selectedSquad2 = sqd;
		squad2Selected = true;
	}
}

void DraftScreenState::postSubLevelClosing()
{
	Unit newLeader;
	int oldSquadID = -1;
	Squad newSquad;
	SquadPos leaderPos;
	std::pair<Squad*, Unit*>  oldUnit;
	Squad* oldSquad;
	UnitBoughtEvent evnt;

	switch (stateHandler.getState())
	{
	case DraftScreenStateState::DSSS_addSquadPendingConfirmation:
		if (newSquadConfirmed)
		{
			oldUnit = decipherUnitInSquadSignal(clickedUnit);
			newLeader = *oldUnit.second;

			//UnitsSwappedEvent evnt = UnitsSwappedEvent(level, *selectedSquad2, newSquad);
			//eventQueue.addEvent(&evnt);

			enterNamingState(newLeader.getName());
		}
		else
		{
			deselectUnit();
			//state = DraftScreenStateState::addingSquad;
			stateHandler.backOneStep();
		}
		break;

	case DraftScreenStateState::DSSS_addSquadNamingSquad:
		if (clickedUnit.getHoveredId() == DraftMouseButtons::unitInSquad)
		{
			oldUnit = decipherUnitInSquadSignal(clickedUnit);
			oldSquadID = oldUnit.first->getID();
			newLeader = *oldUnit.second;
			oldUnit.first->removeUnit(SquadPos(clickedUnit.getPayload().at(1)));
		}
		else if (clickedUnit.getHoveredId() == DraftMouseButtons::unitInShop)
		{
			newLeader = draftChoices.buyUnit(clickedUnit.getPayload().at(0));
		}
		else
		{
			throw new std::exception();
		}

		leaderPos = SquadPos(newSquadLeaderPosition.getPayload().at(1));
		newSquad = squadCreator->createSquad(newLeader, leaderPos, stringHandler);
		//addNewSquadToPlayer(newSquad);

		newSquad.setName(*newSquadNameBucket);
		addNewSquadToPlayer(newSquad);
		selectSquad(findSquadPointer(newSquad.getID()), true);
		deselectUnit();

		if (clickedUnit.getHoveredId() == DraftMouseButtons::unitInSquad)
		{
			oldSquad = findSquadPointer(oldSquadID);
			selectSquad(oldSquad, false);
		}
		else if (clickedUnit.getHoveredId() == DraftMouseButtons::unitInShop)
		{
			evnt = UnitBoughtEvent(level, newSquad, newLeader.getID());
			eventQueue.addEvent(&evnt);
		}
		enterBrowsingState();
		break;

	case DraftScreenStateState::DSSS_leavePagePendingConfirmation:
		if (closeConfirmed)
		{
			readyForBattle = true;
			close();
		}
		else
		{
			//enterBrowsingState();
			stateHandler.backOneStep();
		}
		break;
	default:
		throw new std::exception();
	}
}

ExternalStateControls DraftScreenState::generateExternalControls()
{
	ExternalStateControls retVal;
	if (readyForBattle)
	{
		retVal.startNextBattle = true;
	}
	return retVal;
}

void DraftScreenState::addNewSquadToPlayer(Squad sqd)
{
	int sqd1ID, sqd2ID;
	if (squad1Selected)
	{
		sqd1ID = selectedSquad1->getID();
	}
	if (squad2Selected)
	{
		sqd2ID = selectedSquad2->getID();
	}
	playerTeam->addSquad(sqd);


	if (squad1Selected)
	{
		selectedSquad1 = findSquadPointer(sqd1ID);
	}
	if (squad2Selected)
	{
		selectedSquad2 = findSquadPointer(sqd2ID);
	}

	newSquadSlot = Squad();
	newSquadLeaderPosition = MouseSignal();
	ReloadSquadListEvent evnt = ReloadSquadListEvent(level, playerTeam->getSquads());
	eventQueue.addEvent(&evnt);
}