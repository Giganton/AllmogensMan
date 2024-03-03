#include "MapManager.h"
#include "FightResults.h"
#include "GraphicsInterface.h"
#include "InitBattleMapEvent.h"
#include "MapCursorEvent.h"
#include "BattleManager.h"
#include "OpenBattleMapEvent.h"
#include "ConfirmationMenuEvent.h"
#include "LevelUpHandler.h"


MapManager::MapManager(int id, If_BattleManager* man) : MapManager(id)
{
	bManager = man;
	cursor.setPos(bManager->getMap().getCursorStartingPos());
	closable = false;
	level = id;

	InitBattleMapEvent evnt = InitBattleMapEvent(level, bManager->getMap().getVisuals(), bManager->getBattleField().getSquadData(), cursor.getPos());
	eventQueue.addEvent(&evnt);
}

MapManager::MapManager(int id, If_BattleManager* man, bool debugging) : MapManager(id, man)
{
	debugMode = debugging;
}

MapManager::MapManager(int id, If_BattleManager* man, CursorPos startingPos)
{
	bManager = man;
	cursor.setPos(startingPos);
	closable = false;
	level = id;

}

MapManager::MapManager(const MapManager& cpMapman)
{
	if (cpMapman.nextLevel == nullptr)
	{
		nextLevel = nullptr;
	}
	else
	{
		nextLevel = cpMapman.nextLevel->allocateNew();
		*nextLevel = *cpMapman.nextLevel;
	}
	middleMan = cpMapman.middleMan;
	closeMe = cpMapman.closeMe;
	ID = cpMapman.ID;

	bManager = cpMapman.bManager;
	eventQueue = cpMapman.eventQueue;

	visualData = cpMapman.visualData;
}

MapManager& MapManager::operator=(const MapManager asMapman)
{
	if (asMapman.nextLevel == nullptr)
	{
		nextLevel = nullptr;
	}
	else
	{
		nextLevel = asMapman.nextLevel->allocateNew();
		*nextLevel = *asMapman.nextLevel;
	}
	middleMan = asMapman.middleMan;
	closeMe = asMapman.closeMe;
	ID = asMapman.ID;

	bManager = asMapman.bManager;
	eventQueue = asMapman.eventQueue;

	visualData = asMapman.visualData;

	return *this;
}

void MapManager::addInitEvent()
{
	InitBattleMapEvent evnt = InitBattleMapEvent(level, bManager->getMap().getVisuals(), bManager->getBattleField().getSquadData(), cursor.getPos());
	eventQueue.addEvent(&evnt);
}

void MapManager::handleKeyPress(sf::Event keyPress)
{
	if (!animationPause)
	{
		if (isMenuActive())
		{
			controlMenu(keyPress);
		}
		else
		{
			controlMap(keyPress);
		}
	}
}

void MapManager::controlMap(sf::Event keyPress)
{
	if (!(keyPress.type == sf::Event::KeyPressed))
	{
		throw new std::exception();
	}
	switch (keyPress.key.code)
	{
	case sf::Keyboard::Up:
		moveCursor(Directions::up);
		break;
	case sf::Keyboard::Down:
		moveCursor(Directions::down);
		break;
	case sf::Keyboard::Left:
		moveCursor(Directions::left);
		break;
	case sf::Keyboard::Right:
		moveCursor(Directions::right);
		break;
	case sf::Keyboard::X:
		handleXPress();
		break;
	case sf::Keyboard::Z:
		
		break;
	case sf::Keyboard::L:
		if (debugMode)
		{
			doDebugLevelUp();
		}
	}
}

void MapManager::moveCursor(Directions dir)
{
	CursorPos origPos = cursor.getPos();
	switch (dir)
	{
	case Directions::up:
		cursor = bManager->getMap().moveCursorUp(cursor);
		break;
	case Directions::down:
		cursor = bManager->getMap().moveCursorDown(cursor);
		break;
	case Directions::left:
		cursor = bManager->getMap().moveCursorLeft(cursor);
		break;
	case Directions::right:
		cursor = bManager->getMap().moveCursorRight(cursor);
		break;
	}
	std::vector<CursorMove> cMoves = cursor.pullHistory();

	MapCursorEvent cEvent;
	unsigned int i;
	for (i = 0; i < cMoves.size(); i++)
	{
		cEvent = MapCursorEvent(level, cMoves.at(i));
		eventQueue.addEvent(&cEvent);
	}
	if (!(cursor.getPos() == origPos))
	{
		uponCursorMove();
	}
	/*MapCoord pos = bMap->getCursorPos();
	if (currentState.getState() == MapManagerStateValues::movingSquad)
	{
		moveStage.tryCoord(pos);
	}*/
}

void MapManager::openStatusScreen(Squad* sqd)
{
	nextLevel = new StatusScreen(ID + 1, sqd);
	middleMan = true;
}

void MapManager::doBattle()
{
	//battleCounter++;
	//bStage.doBattle();
}

void MapManager::compileVisualStack(GraphicsInterface* gInt)
{
	std::vector<AnimationSignal> signals = gInt->takeSignals(level);
	while (!signals.empty())
	{
		AnimationSignal temp = signals.back();
		signals.pop_back();
		handleSignal(temp);
	}
	collectEvents();

	InputLink::compileVisualStack(gInt);
}

StructuredEvent* MapManager::getOpeningEvent()
{
	return new OpenBattleMapEvent(level - 1);
}


void MapManager::openMenu(Menu mnu)
{
	MenuManager::openMenu(mnu); 
	MenuEvent temp1;
	ConfirmationMenuEvent temp2;
	if (mnu.getType() == MenuType::regularMenu)
	{
		temp1 = MenuEvent(menu.getVisuals(), MenuEventType::opened, level);
		eventQueue.addEvent(&temp1);
	}
	else if (mnu.getType() == MenuType::confirmationMenu)
	{
		temp2 = ConfirmationMenuEvent(menu.getVisuals(), MenuEventType::opened, level);
		eventQueue.addEvent(&temp2);
	}
}
void MapManager::closeMenu()
{
	MenuType type = menu.getType();
	MenuManager::closeMenu();
	MenuEvent temp1;
	ConfirmationMenuEvent temp2;
	if (type == MenuType::regularMenu)
	{
		temp1 = MenuEvent(menu.getVisuals(), MenuEventType::closed, level);
		eventQueue.addEvent(&temp1);
	}
	else if (type == MenuType::confirmationMenu)
	{
		temp2 = ConfirmationMenuEvent(menu.getVisuals(), MenuEventType::closed, level);
		eventQueue.addEvent(&temp2);
	}
}

void MapManager::openConfirmationWindow(std::string menuText)
{
	std::vector<Menu> options;

	options.push_back(Menu("Yes", ConfirmationItems::yes));
	options.push_back(Menu("No", ConfirmationItems::no));
	Menu mnu = Menu(menuText, options, false, MenuType::confirmationMenu);
	mnu.setSelected(0);
	openMenu(mnu);
}


void MapManager::closeConfirmationWindow()
{
	closeMenu();
}

/*void MapManager::controlMenu(sf::Event keyPress)
{
	MenuManager::controlMenu(keyPress);
}*/

void MapManager::selectionAction()
{
	MenuEvent temp = MenuEvent(menu.getVisuals(), MenuEventType::changedSelected, level);
	eventQueue.addEvent(&temp);
}

void MapManager::handleSignal(AnimationSignal signal)
{
	switch (signal.getType())
	{
	case SignalType::animationStarted:
		pauseForAnimation();
		handleSignalAnticipation(signal);
		break;
	case SignalType::animationDone:
		animationFinished();
		if (signal.getSubType() == SignalSubType::Victory)
		{
			closeFollowers();
			closeMe = true;
			bManager->winBattle();
		}
		break;
	}
}

void MapManager::handleSignalAnticipation(AnimationSignal signal)
{
	unsigned int i;
	for (i = 0; i < anticipatedSignals.size(); i++)
	{
		if (signal.getSubType() == anticipatedSignals.at(i))
		{
			anticipatedSignals.erase(anticipatedSignals.begin() + i);
			break;
		}
	}
}

void MapManager::addSignalAnticipation(SignalSubType signalType)
{
	anticipatedSignals.push_back(signalType);
}

void MapManager::pauseForAnimation()
{
	nrOfRunningAnims = nrOfRunningAnims + 1;
	animationPause = true;
}

bool MapManager::isBusy()
{
	return animationPause || anticipatedSignals.size() > 0;
}

void MapManager::animationFinished()
{
	nrOfRunningAnims = nrOfRunningAnims - 1;
	if (nrOfRunningAnims == 0 && anticipatedSignals.size() == 0)
	{
		animationPause = false;
	}
}

bool MapManager::isEnemyWithinRange(Squad sqd)
{
	BattleField bField = bManager->getBattleField();
	MapCoord coord = bField.findSquadPos(sqd);
	return bManager->getBattleField().isAnyLivingEnemyInRange(coord.getX(), coord.getY(), sqd.getAtkRange(), sqd.getFlagTag());
}

bool MapManager::isEnemyWithinRange(Squad sqd, MapCoord coord)
{
	BattleField bField = bManager->getBattleField();
	return bManager->getBattleField().isAnyLivingEnemyInRange(coord.getX(), coord.getY(), sqd.getAtkRange(), sqd.getFlagTag());
}

void MapManager::levelUpUnit(Squad squad, int unitID)
{
	int level = squad.findUnitPtr(unitID)->getLevel();
	std::vector<LevelUpData> lvlUpData;
	lvlUpData.push_back(LevelUpData(squad.getID(), unitID, level + 1));

	openLink(new LevelUpHandler(level + 1, lvlUpData, bManager->getBattleFieldPtr()));
}

void MapManager::levelUpSquad(Squad squad)
{
	unsigned int i;
	std::vector<Unit*> units = squad.getAllLivingUnitPtrs();
	std::vector<LevelUpData> levelData;
	for (i = 0; i < units.size(); i++)
	{
		if (units.at(i)->isLevelable())
		{
			levelData.push_back(LevelUpData(squad.getID(), units.at(i)->getID(), units.at(i)->getLevel() + 1));
		}
	}

	openLink(new LevelUpHandler(level + 1, levelData, bManager->getBattleFieldPtr()));
}

void MapManager::doDebugLevelUp()
{
	if (bManager->getMap().doesHoveredExist(cursor))
	{
		if (!bManager->getBattleField().isHoveredEmpty(cursor))
		{
			Squad hovSqd = bManager->getBattleField().getHoveredSquad(cursor);

			if (hovSqd.getFlagTag() == tagID::player)
			{
				unsigned int i;
				std::vector<Unit*> units = hovSqd.getAllLivingUnitPtrs();
				std::vector<LevelUpData> levelData;
				for (i = 0; i < units.size(); i++)
				{
					if (units.at(i)->isLevelable())
					{
						levelData.push_back(LevelUpData(hovSqd.getID(), units.at(i)->getID(), units.at(i)->getLevel() + 1));
					}
				}
				
				openLink(new LevelUpHandler(level + 1, levelData, bManager->getBattleFieldPtr()));
			}
		}
	}
	else
	{
		throw new std::exception();
	}
}