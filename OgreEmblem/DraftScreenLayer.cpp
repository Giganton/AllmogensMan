#include "DraftScreenLayer.h"
#include "GraphicsAssets.h"
#include "SquadNamePickerLayer.h"

DraftScreenLayer::DraftScreenLayer(int lr, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler) : AnimationLayer(lr, ww, assts, strHandler) 
{ 
	drawable = true;

	squadDrawer = SquadDrawer(&assts->mapPackage.squadTextureMap);

	sf::Vector2f doneButtonPos = sf::Vector2f(window->getSize().x - 200, window->getSize().y - 180);
	doneButton = DialogueButton("Klar", doneButtonPos, assts);

	background.setTexture(assets->uiPackage.draftBackground);
}

DraftScreenLayer::DraftScreenLayer(const DraftScreenLayer& cpEQ)
{
	middleMan = cpEQ.middleMan;
	if (middleMan)
	{
		nextLevel = cpEQ.nextLevel->clone();
	}
	squadList = cpEQ.squadList;
	window = cpEQ.window;
	stringHandler = cpEQ.stringHandler;
	layer = cpEQ.layer;
	signals = cpEQ.signals;
	background = cpEQ.background;

	unitData = cpEQ.unitData;
	squadButtons = cpEQ.squadButtons;
	squadDrawer = cpEQ.squadDrawer;
	unitButtons = cpEQ.unitButtons;
	doneButton = cpEQ.doneButton;

	drawable = cpEQ.drawable;
	seeThrough = cpEQ.seeThrough;
}

DraftScreenLayer& DraftScreenLayer::operator=(const DraftScreenLayer cpEQ)
{
	middleMan = cpEQ.middleMan;
	if (middleMan)
	{
		nextLevel = cpEQ.nextLevel->clone();
	}
	squadList = cpEQ.squadList;
	window = cpEQ.window;
	stringHandler = cpEQ.stringHandler;
	layer = cpEQ.layer;
	signals = cpEQ.signals;
	background = cpEQ.background;

	unitData = cpEQ.unitData;
	squadButtons = cpEQ.squadButtons;
	squadDrawer = cpEQ.squadDrawer;
	unitButtons = cpEQ.unitButtons;
	doneButton = cpEQ.doneButton;

	drawable = cpEQ.drawable;
	seeThrough = cpEQ.seeThrough;

	return *this;
}

DraftScreenLayer* DraftScreenLayer::clone()
{ 
	return new DraftScreenLayer(*this); 
}

void DraftScreenLayer::applyEvent(StructuredEvent* evnt)
{
	evnt->applyToDraftScreenLayer(this);
}

void DraftScreenLayer::drawSquadBox(sf::RenderWindow* window)
{
	unsigned int i;
	//sf::Vector2f squadBoxSize = SquadWindowButton().getBoxSize();
	sf::RectangleShape squadBox(sf::Vector2f(1025, 600));
	squadBox.setFillColor(sf::Color(0, 0, 0, 230));
	squadBox.setPosition(squadBoxPos);

	window->draw(squadBox);
	for (i = 0; i < squadButtons.size(); i++)
	{
		squadButtons.at(i).draw(window);
	}

	addNewSquadButton.draw(window);
}

void DraftScreenLayer::drawShopBox(sf::RenderWindow* window)
{
	sf::RectangleShape unitBox(sf::Vector2f(350, 700));
	unitBox.setFillColor(sf::Color(0, 0, 0, 230));
	unitBox.setPosition(unitBoxPos);
	window->draw(unitBox);

	unsigned int i;
	for (i = 0; i < unitButtons.size(); i++)
	{
		unitButtons.at(i).draw(window);
	}
}

int DraftScreenLayer::findSquadIndex(int id)
{
	unsigned int i;
	for (i = 0; i < squadList.size(); i++)
	{
		if (squadList.at(i).getID() == id)
		{
			return i;
		}
	}
	throw new std::exception();
	return -1;
}

int DraftScreenLayer::findShopIndex(int id)
{
	unsigned int i;
	for (i = 0; i < unitData.size(); i++)
	{
		if (unitData.at(i).ID == id)
		{
			return i;
		}
	}
	throw new std::exception();
	return -1;
}

Squad DraftScreenLayer::decipherSquadSignal(MouseSignal signal)
{
	if (signal.getHoveredId() != DraftMouseButtons::squad)
	{
		throw new std::exception();
	}
	unsigned int i;
	for (i = 0; i < squadList.size(); i++)
	{
		if (squadList.at(i).getID() == signal.getPayload().at(0))
		{
			return squadList.at(i);
		}
	}
	throw new std::exception();
	return Squad();
}

void DraftScreenLayer::initSquadInfoWindow()
{
	sf::Vector2f pos1(1450, 100);
	sf::Vector2f pos2(1450, 425);
	squadInfo1 = SquadWindowButton(pos1, assets);
	squadInfo2 = SquadWindowButton(pos2, assets);
}

void DraftScreenLayer::initDraftScreen(std::vector<Squad> sqdData, std::vector<UnitData> untData)
{
	unsigned int i;
	SquadWindowButton dummy = SquadWindowButton();

	squadList = sqdData;

	float squadBoxWidth = dummy.getBoxSize().x;
	float squadBoxHeight = dummy.getBoxSize().y;

	//float squadXSeparation = 50;
	//float squadYSeparation = 50;

	sf::Vector2f unitOffset(30, 30);
	float unitXSeparation = 30;
	float unitYSeparation = 30;

	squadButtons.clear();
	unitButtons.clear();

	initSquadInfoWindow();

	loadSquads(sqdData);

	unitData = untData;

	for (i = 0; i < unitData.size(); i++)
	{
		//unitButtons.push_back(UnitListButton(unitData.at(i), unitBoxPos + sf::Vector2f((float)(20), (float)(20+110*i)), assets, stringHandler));
		UnitPortraitButton portrait(unitData.at(i), sf::Vector2f(0.0f, 0.0f), assets);
		sf::Vector2f unitPortraitPos = unitOffset + unitBoxPos + sf::Vector2f((portrait.getSize().x + unitXSeparation) * (float)(i % 2),(float)(i / 2) * (portrait.getSize().y + unitYSeparation));
		portrait.setPosition(unitPortraitPos);
		unitButtons.push_back(portrait);
	}

	unitDetailWindow = UnitDetailsWindow(unitDetailPos, assets, stringHandler);
}

void DraftScreenLayer::loadSquads(std::vector<Squad> sqdData)
{
	int i;
	sf::Vector2f squadOffset(50, 50);
	squadButtons.clear();

	for (i = 0; i < sqdData.size() + 1; i++)
	{
		//SquadButton button(sqdData.at(i), squadBoxPos + squadOffset + sf::Vector2f((float)(((squadBoxWidth + squadXSeparation) * (i % 2))), (float)((i / 2) * (squadBoxHeight + squadYSeparation))), assets);
		//squadButtons.push_back(button);

		int nrPerRow = 5;
		float xSquadOffset = TILE_W / 2 + 50;
		float ySquadOffset = TILE_H / 2 + (float)TILE_H / ((float)TILE_W) * 50;
		float rowOffset = ySquadOffset * 2;
		sf::Vector2f pos = squadBoxPos + squadOffset + sf::Vector2f(i % nrPerRow * xSquadOffset, (i / nrPerRow) * rowOffset + ((i % nrPerRow) % 2) * ySquadOffset);
		//sf::Vector2f pos = squadBoxPos + squadOffset + sf::Vector2f((float)(((squadBoxWidth + squadXSeparation) * (i % 2))), (float)((i / 2) * (squadBoxHeight + squadYSeparation)));

		if (i < sqdData.size())
		{
			SquadRepButton button = SquadRepButton(sqdData.at(i), pos, assets);
			squadButtons.push_back(button);
		}
		else
		{
			addNewSquadButton = SquadRepButton(pos, assets);
		}
	}
}

void DraftScreenLayer::reloadSquadList(std::vector<Squad> sqds)
{
	squadList = sqds;
	loadSquads(squadList);
}

void DraftScreenLayer::draw()
{
	window->draw(background);
	drawSquadBox(window);
	drawShopBox(window);

	squadInfo1.draw(window);
	squadInfo2.draw(window);

	unitDetailWindow.draw(window);

	doneButton.draw(window);
}

std::vector<MouseSignal> DraftScreenLayer::checkSquadInfoHover(sf::Vector2i mousePos)
{
	std::vector<MouseSignal> retVal;
	squadInfo1.mousePosUpdate(mousePos);
	squadInfo2.mousePosUpdate(mousePos);
	if (squadInfo1.isHovered())
	{
		MouseSignal signal;
		if (squadInfo1.isPortraitHovered())
		{

			if (squadInfo1.isHoveredPortraitEmpty())
			{
				signal = MouseSignal(layer, DraftMouseButtons::emptySpotInSquad);
			}
			else
			{
				signal = MouseSignal(layer, DraftMouseButtons::unitInSquad);
			}

			signal.addPayload(1);
			SquadPos pos = SquadPos(squadInfo1.getHoveredPortraitSpot());
			//int unitID = squadList.at(findSquadIndex(squadInfo1.getSquadID())).getUnitPtr(pos)->getID();
			signal.addPayload(pos.getIndexRepresentation());

			retVal.push_back(signal);
		}
		else
		{
			signal = MouseSignal(layer, DraftMouseButtons::squadInfo1);
			retVal.push_back(signal);
		}
	}
	if (squadInfo2.isHovered())
	{
		MouseSignal signal;
		if (squadInfo2.isPortraitHovered())
		{

			if (squadInfo2.isHoveredPortraitEmpty())
			{
				signal = MouseSignal(layer, DraftMouseButtons::emptySpotInSquad);
			}
			else
			{
				signal = MouseSignal(layer, DraftMouseButtons::unitInSquad);
			}

			signal.addPayload(2);
			SquadPos pos = SquadPos(squadInfo2.getHoveredPortraitSpot());
			//int unitID = squadList.at(findSquadIndex(squadInfo2.getSquadID())).getUnitPtr(pos)->getID();
			signal.addPayload(pos.getIndexRepresentation());

			retVal.push_back(signal);
		}
		else
		{
			signal = MouseSignal(layer, DraftMouseButtons::squadInfo2);
			retVal.push_back(signal);
		}
	}
	return retVal;
}

void DraftScreenLayer::applyMousePos(sf::Vector2i mousePos)
{
	unsigned int i;
	bool hitSomething = false;
	if (!middleMan)
	{
		for (i = 0; i < squadButtons.size(); i++)
		{
			squadButtons.at(i).mousePosUpdate(mousePos);
			if (squadButtons.at(i).isHovered())
			{
				MouseSignal signal = MouseSignal(layer, DraftMouseButtons::squad);
				signal.addPayload(squadButtons.at(i).getSquadID());
				mouseSignals.push_back(signal);
				hitSomething = true;
			}
		}

		std::vector<MouseSignal> squadInfoSignals = checkSquadInfoHover(mousePos);
		for (i = 0; i < squadInfoSignals.size(); i++)
		{
			hitSomething = true;
			mouseSignals.push_back(squadInfoSignals.at(i));
		}

		for (i = 0; i < unitButtons.size(); i++)
		{
			unitButtons.at(i).mousePosUpdate(mousePos);
			if (unitButtons.at(i).isHovered())
			{
				MouseSignal signal;
				if (unitButtons.at(i).isEmpty())
				{
					signal = MouseSignal(layer, DraftMouseButtons::emptySpotInShop);
				}
				else
				{
					signal = MouseSignal(layer, DraftMouseButtons::unitInShop);
					signal.addPayload(unitData.at(i).ID);
				}
				mouseSignals.push_back(signal);
				hitSomething = true;
			}
		}
		addNewSquadButton.mousePosUpdate(mousePos);
		if (addNewSquadButton.isHovered())
		{
			mouseSignals.push_back(MouseSignal(layer, DraftMouseButtons::newSquadButton));
			hitSomething = true;
		}

		doneButton.mousePosUpdate(mousePos);
		if (doneButton.isHovered())
		{
			mouseSignals.push_back(MouseSignal(layer, DraftMouseButtons::doneManagingSquads));
			hitSomething = true;
		}

		if (!hitSomething)
		{
			MouseSignal signal = MouseSignal(layer, DraftMouseButtons::none);
			mouseSignals.push_back(signal);
		}
		unitDetailWindow.passMousePos(mousePos);

	}
}

/*void DraftScreenLayer::selectEntity(MouseSignal clickedSignal)
{
	switch (clickedSignal.getHoveredId())
	{
	case DraftMouseButtons::emptySpotInSquad:
	case DraftMouseButtons::unitInSquad:
	case DraftMouseButtons::unitInShop:
		selectUnit(clickedSignal);
		break;
	case DraftMouseButtons::squad:

		break;
	}
}*/

void DraftScreenLayer::selectSquad(MouseSignal squadSignal, bool windowOne)
{
	if (squadSignal.getHoveredId() != DraftMouseButtons::squad)
	{
		throw new std::exception();
	}
	Squad squad = decipherSquadSignal(squadSignal);
	selectSquad(squad, windowOne);
}

void DraftScreenLayer::selectSquad(Squad squad, bool windowOne)
{
	unsigned int i;
	for (i = 0; i < squadButtons.size(); i++)
	{
		if (squadButtons.at(i).getSquadID() == squad.getID())
		{
			squadButtons.at(i).select();
		}
	}
	if (windowOne)
	{
		squadInfo1.insertSquad(squad);
	}
	else
	{
		squadInfo2.insertSquad(squad);
	}
}

void DraftScreenLayer::selectNewEmptySquad(bool windowOne)
{
	Squad squad = Squad();
	squad.setName(stringHandler->getDraftPhrase(DraftStringID::enumNewSquadName));
	squadInfo1.insertSquad(squad, true);
	addNewSquadButton.select();
}

void DraftScreenLayer::selectUnit(MouseSignal unitSignal)
{
	if (unitSignal.getHoveredId() == DraftMouseButtons::unitInSquad || unitSignal.getHoveredId() == DraftMouseButtons::emptySpotInSquad)
	{
		UnitData data;
		//int sIndex = findSquadIndex(unitSignal.getPayload().at(0));
		if (unitSignal.getPayload().at(0) == 1)
		{
			Squad sqd = squadList.at(findSquadIndex(squadInfo1.getSquadID()));
			SquadPos pos = SquadPos(unitSignal.getPayload().at(1));
			squadInfo1.selectPortrait(pos);
			data = squadInfo1.getUnitData(pos);
		}
		else if (unitSignal.getPayload().at(0) == 2)
		{
			Squad sqd = squadList.at(findSquadIndex(squadInfo2.getSquadID()));
			SquadPos pos = SquadPos(unitSignal.getPayload().at(1));
			squadInfo2.selectPortrait(pos);
			data = squadInfo2.getUnitData(pos);
		}
		else
		{
			throw new std::exception();
		}
		//squadButtons.at(sIndex).selectPortrait(unitSignal.getPayload().at(1));
		//UnitData data = squadButtons.at(sIndex).getUnitData(unitSignal.getPayload().at(1));
		unitDetailWindow.setUnit(data);
	}
	else if (unitSignal.getHoveredId() == DraftMouseButtons::unitInShop)
	{
		int index = findShopIndex(unitSignal.getPayload().at(0));
		unitButtons.at(index).setSelected(true);
		unitDetailWindow.setUnit(unitData.at(index));
	}
	else
	{
		throw new std::exception();
	}
}

void DraftScreenLayer::reloadSquad(Squad sqd)
{
	int index = findSquadIndex(sqd.getID());
	squadList.at(index) = sqd;
	squadButtons.at(index).reInit(sqd);
	if (squadInfo1.getSquadID() == sqd.getID())
	{
		squadInfo1.insertSquad(sqd);
	}
	if (squadInfo2.getSquadID() == sqd.getID())
	{
		squadInfo2.insertSquad(sqd);
	}
}

void DraftScreenLayer::deselectUnit()
{
	unsigned int i;
	squadInfo1.deselectPortraits();
	squadInfo2.deselectPortraits();

	for (i = 0; i < unitButtons.size(); i++)
	{
		unitButtons.at(i).setSelected(false);
	}
	unitDetailWindow.unsetUnit();
}

void DraftScreenLayer::deselectSquad(bool windowOne)
{
	int id;
	if (windowOne)
	{
		id = squadInfo1.getSquadID();
		squadInfo1.removeSquad();
	}
	else
	{
		id = squadInfo2.getSquadID();
		squadInfo2.removeSquad();
	}
	unsigned int i;
	for (i = 0; i < squadButtons.size(); i++)
	{
		if (squadButtons.at(i).getSquadID() == id)
		{
			squadButtons.at(i).unselect();
		}
	}
}

void DraftScreenLayer::buyOutUnit(int unitID)
{
	unsigned int i;
	for (i = 0; i < unitData.size(); i++)
	{
		if (unitData.at(i).ID == unitID)
		{
			unitButtons.at(i).setSold();
		}
	}
}

/*int DraftScreenLayer::findSquadIndex(int id)
{
	unsigned int i;
	for (i = 0; i < squadButtons.size(); i++)
	{
		if (squadButtons.at(i).getSquadID() == id)
		{
			return i;
		}
	}
	throw new std::exception();
	return -1;
}*/

void DraftScreenLayer::openNamePickerLayer()
{
	openNewLayer(new SquadNamePickerLayer(layer + 1, window, assets, stringHandler));
}