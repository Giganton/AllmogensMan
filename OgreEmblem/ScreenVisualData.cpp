#include "ScreenVisualData.h"

Menu ScreenVisualData::getActiveMenu()
{
	if (!isMenuActive())
	{
		throw new std::exception();
	}
	return activeMenu;
}