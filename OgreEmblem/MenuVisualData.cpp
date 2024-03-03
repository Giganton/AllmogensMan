#include "MenuVisualData.h"
#include "Menu.h"

MenuVisualData::MenuVisualData(Menu menu)
{
	options = menu.getOptionsTexts();
	text = menu.getText();
	selected = menu.getSelected();
}