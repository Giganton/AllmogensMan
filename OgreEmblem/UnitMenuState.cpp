#include "SquadManagerMenuState.h"
#include "SquadManager.h"
#include "MenuVisualEvent.h"
#include "SquadManagerEvent.h"


UnitMenuState::UnitMenuState(SquadManager* man, int lvl, Unit* unit, UnitMenuCommand* command, UnitMenuVariant variant) : SquadManagerMenuState(man, lvl)
{
	selectedUnit = unit;
	menu = createUnitMenu(variant);
	menu.activate();
	menu.setSelected(0);

	commandBasket = command;
	*commandBasket = UnitMenuCommand::none;

	MenuVisualEvent temp = MenuVisualEvent(MenuVisualData(menu));
	SquadManagerMenuEvent event = SquadManagerMenuEvent(level, temp);
	eventQueue.addEvent(&event);
}

Menu UnitMenuState::createUnitMenu(UnitMenuVariant variant)
{
	std::vector<Menu> options;
	Menu choice;
	Menu retVal;
	switch (variant)
	{
	case UnitMenuVariant::hoveringUnit:
		options.push_back(Menu("Move", UnitMenuOptions::MoveUnit));
		options.push_back(Menu("Cancel", UnitMenuOptions::CancelUnitMenu));

		retVal = Menu("Gubbmeny", options);
		break;
	case UnitMenuVariant::holdingUnit:
		options.push_back(Menu("Swap", UnitMenuOptions::SwapUnit));
		options.push_back(Menu("Cancel", UnitMenuOptions::CancelUnitMenu));

		retVal = Menu("Gubbmeny", options);
		break;
	case UnitMenuVariant::selectingLeader:
		options.push_back(Menu("Select leader", UnitMenuOptions::selectLeader));
		options.push_back(Menu("Cancel", UnitMenuOptions::CancelUnitMenu));

		retVal = Menu("Gubbmeny", options);
	}
	return retVal;
}

void UnitMenuState::performMenuAction(int action)
{
	switch (action)
	{
	case UnitMenuOptions::MoveUnit:
		*commandBasket = UnitMenuCommand::pickUpUnit;
		closeMe = true;
		break;
	case UnitMenuOptions::SwapUnit:
		*commandBasket = UnitMenuCommand::swapUnit;
		closeMe = true;
		break;
	case UnitMenuOptions::selectLeader:
		*commandBasket = UnitMenuCommand::selectAsLeader;
		closeMe = true;
		break;
	case UnitMenuOptions::CancelUnitMenu:
		closeMe = true;
		break;
	}
}

StructuredEvent* UnitMenuState::getOpeningEvent()
{
	return new OpenUnitMenuEvent(level - 1);
}