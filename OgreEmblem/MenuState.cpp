#include "SquadManagerMenuState.h"
#include "SquadManagerEvent.h"

void SquadManagerMenuState::handleKeyPress(sf::Event keypress)
{
	switch (keypress.key.code)
	{
	case sf::Keyboard::Z:
		closeMe = true;
		break;
	default:
		controlMenu(keypress);
	}
	MenuVisualEvent temp = MenuVisualEvent(MenuVisualData(menu));
	SquadManagerMenuEvent event = SquadManagerMenuEvent(level, temp);
	eventQueue.addEvent(&event);
}