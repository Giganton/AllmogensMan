#include "SquadManagerState.h"
#include "SquadManager.h"
#include "MenuVisualEvent.h"
#include "SquadManagerEvent.h"
#include "SquadManagerMenuState.h"

SquadMenuState::SquadMenuState(SquadManager* man, int lvl, Squad* squad, bool* squadEdted) : SquadManagerMenuState(man, lvl)
{
	selectedSquad1 = squad;

	menu = createSquadMenu();
	menu.activate();
	menu.setSelected(0);

	squadEdited = squadEdted;

	MenuVisualEvent temp = MenuVisualEvent(MenuVisualData(menu));
	SquadManagerMenuEvent event = SquadManagerMenuEvent(level, temp);
	eventQueue.addEvent(&event);

}

Menu SquadMenuState::createSquadMenu()
{
	std::vector<Menu> options;
	Menu choice;
	options.push_back(Menu("Edit", SquadMenuOptions::EditSquad));
	options.push_back(Menu("Remove", SquadMenuOptions::RemoveSquad));
	options.push_back(Menu("Cancel", SquadMenuOptions::CancelSquadMenu));

	return Menu("Gruppmeny", options);
}

void SquadMenuState::disbandSquad(DisbandSquadCommand command)
{
	squadManager->disbandSquad(command);
}

void SquadMenuState::performMenuAction(int action)
{
	DisbandSquadCommand cmd;
	switch (action)
	{
	case SquadMenuOptions::EditSquad:
		openSquadEditor();
		break;
	case SquadMenuOptions::RemoveSquad:
		cmd = DisbandSquadCommand(selectedSquad1->getID());
		squadManager->disbandSquad(cmd);
		closeMe = true;
		break;
	case SquadMenuOptions::CancelSquadMenu:
		closeMe = true;
		break;
	}
}

void SquadMenuState::closeFollowers()
{
	SquadManagerState::closeFollowers();
	if (finishedEditing)
	{
		*squadEdited = true;
		finishedEditing = false;
		closeMe = true;
	}
}

void SquadMenuState::openSquadEditor()
{
	/*nextLevel = new SquadEditorState(*selectedSquad, squadManager, level + 1, &finishedEditing);
	middleMan = true;
	OpenSquadEditorEvent temp = OpenSquadEditorEvent(level);
	eventQueue.addEvent(&temp);*/

	openLink(new SquadEditorState(*selectedSquad1, squadManager, level + 1, &finishedEditing));
}

StructuredEvent* SquadMenuState::getOpeningEvent()
{
	return new OpenSquadMenuEvent(level - 1);
}