#pragma once
#include "SquadDrawer.h"
#include "TextDrawer.h"
#include "MouseInteractionObject.h"
#include "MapAnimation2.h"

class SquadRepButton : public MouseInteractionObject
{
private:
	std::string squadName;
	int squadID = -1;
	sf::Vector2f position;
	SquadRepresentation squadRep;
	TextDrawer textDrawer;

	sf::Vector2f squadBoxSize;

	bool selected = false;
	bool empty = false;

	SquadDrawer squadDrawer;
	MapAnimation2 tileDrawer;

	void drawName(sf::RenderWindow* window);

public:
	SquadRepButton() {};
	SquadRepButton(Squad squad, sf::Vector2f pos, GraphicsAssets* assets);
	SquadRepButton(sf::Vector2f pos, GraphicsAssets* assets);

	void reInit(Squad sqd);
	void draw(sf::RenderWindow* window) override;
	//void mousePosUpdate(sf::Vector2i currentMousePos) override;
	int getSquadID() { return squadID; };

	void select() { selected = true; };
	void unselect() { selected = false; };

};