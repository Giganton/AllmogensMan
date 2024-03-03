#pragma once
#include "MapManager.h"

class BrowserBucket;

class MapFightPicker : public MapManager
{
private:
	Squad fightingSquad;
	MapCoord squadPos;
	std::vector<Squad> targetList;
	unsigned int currentIndex = -1;

	bool alsoMoveUnit = false;
	MoveData moveToBePerformed;
	bool fightingDone = false;

	BrowserBucket* passedBucket = nullptr;
	void controlMap(sf::Event keyPress) override;
	void setTarget(int index);
	void rollUp();
	void rollDown();
	void selectionAction() override;
	void performMenuAction(int action) override;
	void confirmBattleAction();
	void atMenuOpening() override { closable = false; };
	void atMenuClosing() override { closable = true; };
	void doBattle();
	void preSubLevelClosing() override;

public:
	MapFightPicker() {};
	MapFightPicker(int id, If_BattleManager* man, CursorPos startingPos, MapCoord squadNewPos, Squad sqd, BrowserBucket* bBucket);
	MapFightPicker(int id, If_BattleManager* man, CursorPos startingPos, MapCoord squadNewPos, Squad sqd, MoveData moveToPerform, BrowserBucket* bBucket);

	StructuredEvent* getOpeningEvent() override;
};