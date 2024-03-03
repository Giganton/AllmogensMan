#pragma once
#include "AnimationLayer.h"
#include "TestButton.h"
#include "DraftMouseButtons.h"
#include "SquadDrawer.h"
#include "SquadWindowButton.h"
#include "UnitListButton.h"
#include "UnitDetailsWindow.h"
#include "SquadRepButton.h"
#include "DialogueButton.h"

class DraftScreenLayer : public AnimationLayer
{
private:
	//std::vector<SquadWindowButton> squadButtons;
	SquadWindowButton squadInfo1;
	SquadWindowButton squadInfo2;

	std::vector<Squad> squadList;
	std::vector<SquadRepButton> squadButtons;
	SquadDrawer squadDrawer;
	
	SquadRepButton addNewSquadButton;

	std::vector<UnitData> unitData;
	std::vector<UnitPortraitButton> unitButtons;

	DialogueButton doneButton;

	UnitDetailsWindow unitDetailWindow;

	sf::Sprite background;
	
	sf::Vector2f squadBoxPos = sf::Vector2f(400, 100);
	sf::Vector2f unitBoxPos = sf::Vector2f(25, 100);
	sf::Vector2f unitDetailPos = sf::Vector2f(0, 830);

	void initSquadInfoWindow();
	void applyMousePos(sf::Vector2i mousePos) override;
	std::vector<MouseSignal> checkSquadInfoHover(sf::Vector2i mousePos);
	void drawSquadInfoWindow(sf::RenderWindow* window);
	void drawSquadBox(sf::RenderWindow* window);
	void drawShopBox(sf::RenderWindow* window);
	int findSquadIndex(int id);
	int findShopIndex(int id);
	void loadSquads(std::vector<Squad> sqdData);

	Squad decipherSquadSignal(MouseSignal signal);

public:
	DraftScreenLayer() {};
	DraftScreenLayer(int lr, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler);

	DraftScreenLayer(const DraftScreenLayer& cpEQ);
	DraftScreenLayer& operator=(const DraftScreenLayer asEQ);
	~DraftScreenLayer() { AnimationLayer::~AnimationLayer(); };

	DraftScreenLayer* clone() override;

	void draw() override;
	void applyEvent(StructuredEvent* evnt) override;

	void initDraftScreen(std::vector<Squad> sqdData, std::vector<UnitData> untData);
	void reloadSquad(Squad sqd);
	void reloadSquadList(std::vector<Squad> sqds);
	//void selectEntity(MouseSignal signal);
	void selectUnit(MouseSignal unitSignal);
	void selectSquad(Squad squad, bool windowOne);
	void selectSquad(MouseSignal unitSignal, bool windowOne);
	void selectNewEmptySquad(bool windowOne);
	void deselectUnit();
	void deselectSquad(bool windowOne);

	void buyOutUnit(int unitID);

	void openNamePickerLayer();
};
