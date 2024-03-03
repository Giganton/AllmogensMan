#pragma once
#include "MouseInteractionObject.h"
#include "TextDrawer.h"
#include "UnitPortraitButton.h"
#include "SquadPos.h"

class SquadDrawer;
class GraphicsAssets;


class SquadWindowButton : public MouseInteractionObject
{
private:
	//sf::RectangleShape visualBox;
	//SquadRepresentation squadRep;
	TextDrawer textDrawer;

	bool empty = true;
	bool newSquad = false;

	std::string squadName = "";
	int squadID = -1;

	GraphicsAssets* assets = nullptr;

	sf::Vector2f position;

	sf::Vector2f squadBoxSize = sf::Vector2f(410.0f, 290.0f);

	std::vector<std::pair<bool, UnitData>> unitGrid;
	std::vector<UnitPortraitButton> unitButtons;

	bool portraitIsHovered = false;
	int hoveredPortraitSpot = -1;

	//SquadDrawer* squadDrawer = nullptr;

	void drawName(sf::RenderWindow* window);
	void drawBox(sf::RenderWindow* window);
	void drawAllPortraits(sf::RenderWindow* window);
	void setupPortraits();
	void drawPortrait(UnitData uData, sf::Vector2f pos, sf::RenderWindow* window);
	void drawPortrait(sf::Vector2f pos, sf::RenderWindow* window);
	void setupSquad(Squad squad);

	int getUnitIndex(SquadPos pos);
public:
	SquadWindowButton() {};
	SquadWindowButton(Squad squad, sf::Vector2f pos, GraphicsAssets* assets);
	SquadWindowButton(sf::Vector2f pos, GraphicsAssets* assets);

	void insertSquad(Squad sqd);
	void insertSquad(Squad sqd, bool emptySquad);
	void removeSquad();

	bool isNewSquad() { return newSquad; };

	void draw(sf::RenderWindow* window) override;
	void mousePosUpdate(sf::Vector2i currentMousePos) override;
	sf::Vector2f getBoxSize() { return squadBoxSize; };

	bool isPortraitHovered() { return portraitIsHovered; };
	int getHoveredPortraitSpot();
	SquadPos getHoveredSquadPos();
	int getSquadID() { return squadID; };
	int isHoveredPortraitEmpty();

	void selectPortrait(SquadPos pos);
	void deselectPortraits();
	UnitData getUnitData(SquadPos pos);
};