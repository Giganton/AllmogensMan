#pragma once
#include "MapManager.h"
#include "BrowserBucket.h"

enum mbMenuActions { nothing, initiateMoveSquad, closeMenu, initiateBattle, putToRest, endTurn, openStatusScreen};

class MapBrowser : public MapManager
{
private:
	Menu createMapMenu();
	Menu createPlayerUnitMenu(Squad sqd, bool enemyInRange);
	Menu createEnemyUnitMenu(Squad sqd);
	BrowserBucket bucket;

	bool* openCampScreen = nullptr;

	void performMenuAction(int action) override;
	void handleXPress() override;
	void preSubLevelClosing() override;
	void sendEndTurn();
public:
	MapBrowser() {};
	MapBrowser(int id, If_BattleManager* man, bool* openCampScreenBucket, bool debugMode) : MapManager(id, man, debugMode) { openCampScreen = openCampScreenBucket; };
};