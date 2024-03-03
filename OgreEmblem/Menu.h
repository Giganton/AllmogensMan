#pragma once
#include<vector>
#include<string>

//enum MenuAction { noAction, initiateMoveSquad, moveToTile, closeMenu, initiateBattleManager, doBattle, openStatusScreen, initiateUnitSwap, performUnitSwap, putToRest, endTurn};

class MenuVisualData;
enum class MenuType { regularMenu, confirmationMenu };

class Menu
{
private:
	 std::vector<Menu> options;
	 MenuType type = MenuType::regularMenu;
	 std::string text;
	 int selected = -1;
	 bool hidden = false;
	 bool active = false;
	 int menuValue = -1;
	 bool vertical = true;
public:
	Menu() {};
	Menu(std::string menuText, std::vector<Menu> chces);
	Menu(std::string menuText, std::vector<Menu> chces, bool vrtcal) : Menu(menuText, chces) { vertical = vrtcal; };
	Menu(std::string menuText, std::vector<Menu> chces, bool vrtcal, MenuType tpe) : Menu(menuText, chces) { vertical = vrtcal; type = tpe; };
	Menu(std::string menuText, int returnVal);

	std::string getText() { return text; };
	bool isLeaf();
	int getMenuAction() { return menuValue; };
	//void print();
	Menu getActiveMenu();
	std::vector<std::string> getOptionsTexts();

	bool isClosed();
	bool isVertical() { return vertical; };

	bool isActive() { return active; };
	void activate() { active = true; };
	void deActivate() { active = false; };

	int getSelected() { return selected; };
	void setSelected(int newSelected) { selected = newSelected; };
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	int enterSelected();
	void goBack();
	int findPath();

	MenuType getType() { return type; };

	MenuVisualData getVisuals();
};