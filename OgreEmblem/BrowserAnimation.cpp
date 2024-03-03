#include "BrowserAnimation.h"
#include "BrowserEvent.h"
#include "GraphicsAssets.h"
#include <algorithm>

BrowserAnimation::BrowserAnimation(BrowserPackage* bPack, UTIL::ScreenCoord offset, float colOff, float rowOff, sf::RenderWindow* ww)
{
	iconTextureMap = &(bPack->iconTextures);
	backgroundTexture = &(bPack->background);
	window = ww;
	colOffset = colOff;
	rowOffset = rowOff;
	browserOffset = offset;

	cursorAnimation = PointerAnimation(browserOffset, UTIL::ScreenCoord(colOffset, rowOffset), UTIL::ScreenCoord(50,50), CursorPos(0, 0), &(bPack->cursorTexture), window);
}

void BrowserAnimation::initBrowser(BrowserVisualData visualData)
{
	initialized = true;
	CursorPos startPos = CursorPos(visualData.getCursorPosX(), visualData.getCursorPosY());
	cursorAnimation.moveCursor(startPos);
	std::vector<std::pair<BrowsableIcon, bool>> icons = visualData.getIcons();
	rowLength = visualData.getMaxColumns();
	unsigned int i;
	itemIcons.clear();
	cursorAnimation.resetSpritemap();
	for (i = 0; i < icons.size(); i++)
	{
		int posX = i % rowLength;
		int posY = (int)(floor)(i / rowLength);
		cursorAnimation.setSpriteSize(CursorPos(posX, posY), findIconSize(icons.at(i).first));
		BrowserNodeData node;

		node.icon = icons.at(i).first;
		node.selected = icons.at(i).second;
		node.mapPos = std::make_pair(posX, posY);

		itemIcons.push_back(node);
	}
	cursorAnimation.reInitialize();
}


UTIL::ScreenCoord BrowserAnimation::findIconSize(BrowsableIcon icon)
{
	std::vector<BrowsableIconTag> tags = icon.getTags();
	std::vector<std::pair<float, float>> offsets = icon.getOffsets();
	unsigned int i;
	float width, height;
	float maxWidth = 0;
	float maxHeight = 0;

	for (i = 0; i < tags.size(); i++)
	{
		sf::IntRect rectangle = iconTextureMap->find(tags.at(i))->second.second;
		width = rectangle.width + offsets.at(i).first;
		height = rectangle.height + offsets.at(i).second;
		if (width > maxWidth)
		{
			maxWidth = width;
		}
		if (height > maxHeight)
		{
			maxHeight = height;
		}
	}
	return UTIL::ScreenCoord(width, height);
}

void BrowserAnimation::performCursorMove(BrowserCursorMove* cMove)
{
	cursorAnimation.initiateMove(cMove->start, cMove->destination);
}

void BrowserAnimation::performSelection(SelectionMade* sel)
{
	unsigned int i;
	std::vector<int> newToggles = sel->getToggled();
	for (i = 0; i < newToggles.size(); i++)
	{
		itemIcons.at(newToggles.at(i)).selected = !itemIcons.at(newToggles.at(i)).selected;
	}
}

void BrowserAnimation::pickUpItem(CursorPos mapPos)
{
	if (isHolding)
	{
		throw new std::exception();
	}
	int pickupIndex = indexAtPos(mapPos);
	heldIcon = itemIcons.at(pickupIndex).icon;
	itemIcons.at(pickupIndex).icon = BrowsableIcon(BrowsableIconTag::emptyUnit);
	isHolding = true;
}

void BrowserAnimation::dropItem(CursorPos mapPos)
{
	if (!isHolding)
	{
		throw new std::exception();
	}
	int dropIndex = indexAtPos(mapPos);
	itemIcons.at(dropIndex).icon = heldIcon;
	isHolding = false;
}

void BrowserAnimation::swapItem(CursorPos mapPos)
{
	if (!isHolding)
	{
		throw new std::exception();
	}
	int swapIndex = indexAtPos(mapPos);
	BrowsableIcon temp = heldIcon;
	heldIcon = itemIcons.at(swapIndex).icon;
	itemIcons.at(swapIndex).icon = temp;
}

BrowsableIcon BrowserAnimation::passItem()
{
	if (!isHolding)
	{
		throw new std::exception();
	}
	BrowsableIcon retval = heldIcon;
	isHolding = false;
	return retval;
}

void BrowserAnimation::receiveItem(BrowsableIcon icon)
{
	if (isHolding)
	{
		throw new std::exception();
	}
	heldIcon = icon;
	isHolding = true;
}

int BrowserAnimation::indexAtPos(CursorPos mapPos)
{
	int index = mapPos.y * rowLength + mapPos.x;
	return index;
}

void BrowserAnimation::draw()
{
	sf::RectangleShape background(sf::Vector2f(rowLength*rowOffset + 50, 700));

	background.setPosition(browserOffset.x, browserOffset.y);
	background.setFillColor(sf::Color(220, 240, 200, 255));
	window->draw(background);
	if (!initialized)
	{
		throw new std::exception();
	}

	unsigned int i;
	for (i = 0; i < itemIcons.size(); i++)
	{
		drawNode(itemIcons.at(i));
	}
	if (browserActive)
	{
		if (isHolding)
		{
			CursorPos mapPos = cursorAnimation.getCursorPosition();
			drawIcon(heldIcon, std::make_pair(mapPos.x, mapPos.y));
		}
		else
		{
			cursorAnimation.draw();
		}
	}
}

void BrowserAnimation::drawNode(BrowserNodeData node)
{
	drawIcon(node.icon, node.mapPos);
}

/*void BrowserAnimation::drawIcon(BrowsableIcon icon, std::pair<int, int> pos)
{
	drawIcon(icon, UTIL::ScreenCoord(pos.x, pos.y));
}*/

void BrowserAnimation::drawIcon(BrowsableIcon icon, std::pair<int, int> mapPos)
{
	std::vector<BrowsableIconTag> tagList = icon.getTags();
	std::vector<std::pair<float, float>> offsetList = icon.getOffsets();
	float posX = colOffset * mapPos.first + browserOffset.x;
	float posY = rowOffset * mapPos.second + browserOffset.y;

	unsigned int i;
	for (i = 0; i < tagList.size(); i++)
	{
		sf::Sprite sprite;
		sf::Vector2f partialPos = sf::Vector2f(posX + offsetList.at(i).first, posY + offsetList.at(i).second);
		sprite.setPosition(partialPos);
		sprite.setTexture(iconTextureMap->find(tagList.at(i))->second.first);

		window->draw(sprite);
	}
}