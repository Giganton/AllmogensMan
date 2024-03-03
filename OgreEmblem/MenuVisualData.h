#pragma once
#include<string>
#include<vector>

class Menu;

class MenuVisualData
{
private:
	std::vector<std::string> options;
	std::string text;
	int selected = -1;

public:
	MenuVisualData() {};
	MenuVisualData(Menu menu);

	std::vector<std::string> getOptions() { return options; };
	std::string getText() { return text; };
	int getSelected() { return selected; };
};