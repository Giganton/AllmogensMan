#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GraphicsUtils.h"
#include "Browser.h"
#include "BrowserVisualData.h"
#include "PointerAnimation.h"

class BrowserCursorMove;
class SelectionMade;
class BrowserPackage;

struct BrowserNodeData
{
public:
	BrowsableIcon icon;
	bool selected;
	std::pair<int, int> mapPos;
};


class BrowserAnimation
{
private:
	sf::RenderWindow* window;
	std::map<BrowsableIconTag, std::pair<sf::Texture, sf::IntRect>>* iconTextureMap = nullptr;
	UTIL::ScreenCoord browserOffset;
	sf::Texture* backgroundTexture = nullptr;
	std::vector<BrowserNodeData> itemIcons;

	BrowsableIcon heldIcon;
	bool isHolding = false;
	bool browserActive = false;

	int rowLength = -1;
	float colOffset = -1;
	float rowOffset = -1;

	bool active = false;
	bool initialized = false;

	PointerAnimation cursorAnimation;

	int indexAtPos(CursorPos mapPos);
	void drawNode(BrowserNodeData node);
	void drawIcon(BrowsableIcon icon, UTIL::ScreenCoord mapPos);
	void drawIcon(BrowsableIcon icon, std::pair<int, int> mapPos);
	UTIL::ScreenCoord findIconSize(BrowsableIcon icon);

public:
	BrowserAnimation() {};
	BrowserAnimation(BrowserPackage* bPack, UTIL::ScreenCoord xOff, float colOff, float rowOff, sf::RenderWindow* ww);
	void initBrowser(BrowserVisualData visualData);
	void performCursorMove(BrowserCursorMove* cMove);
	void performSelection(SelectionMade* sel);
	void activateBrowser() { browserActive = true; };
	void deActivateBrowser() { browserActive = false; };
	void pickUpItem(CursorPos mapPos);
	void dropItem(CursorPos mapPos);
	void swapItem(CursorPos mapPos);
	void draw();
	BrowsableIcon passItem();
	void receiveItem(BrowsableIcon texture);
};