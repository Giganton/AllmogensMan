#pragma once
#include "Manager.h"
#include "CursorHandler.h"
#include "BattleMap.h"
#include "BattleStage.h"
#include "VisualStack.h"
#include "StatusScreen.h"
#include "MapManagerVisualData.h"
#include "MovementStage.h"
#include "TurnKeeper.h"
#include "tagID.h"
#include "Flag.h"
#include "SquadAI.h"
#include "AnimationQueue.h"
#include "MapManagerVisualEventData.h"
#include "MapManagerVisualData.h"
#include "MenuVisualData.h"
#include "AnimationSignal.h"
#include "InputLink.h"
#include "MenuManager.h"

class If_BattleManager;
class OpenBattleMapEvent;

enum Directions { up, down, left, right };
enum ConfirmationItems { yes , no };

class MapManager : public InputLink, public MenuManager
{
protected:
	If_BattleManager* bManager = nullptr;
	Cursor cursor;
	bool debugMode = false;

	int nrOfRunningAnims = 0;
	std::vector<SignalSubType> anticipatedSignals;

	MapManagerVisualEventData visualData;
	bool initDataSent = false;

	bool animationPause = false;
	bool animationsCancelable = false;

	//methods
	virtual void performMenuAction(int action) override { throw new std::exception(); };

	virtual void controlMap(sf::Event keyPress);
	void doBattle();

	virtual void handleXPress() { throw new std::exception(); };
	void handleSignal(AnimationSignal signal);
	void handleSignalAnticipation(AnimationSignal signal);
	void addSignalAnticipation(SignalSubType signalType);
	void selectionAction() override;
	virtual void uponCursorMove() { };
	virtual void collectEvents() {};
	virtual void pauseForAnimation();
	virtual void animationFinished();
	virtual void addInitEvent();

	void openConfirmationWindow(std::string menuText);
	void closeConfirmationWindow();

	bool isEnemyWithinRange(Squad sqd);
	bool isEnemyWithinRange(Squad sqd, MapCoord coord);

	void doDebugLevelUp();

public:
	MapManager() {};
	MapManager(int id) { visualData = MapManagerVisualEventData(id); level = id; closable = false; };
	MapManager(int id, If_BattleManager* man);
	MapManager(int id, If_BattleManager* man, bool debugging);
	MapManager(int id, If_BattleManager* man, CursorPos startingPos);

	MapManager(const MapManager& cpMapman);
	MapManager& operator=(const MapManager asMapman);
	~MapManager() override { InputLink::~InputLink(); };
	MapManager* clone() const override { return new MapManager(*this); };
	MapManager* allocateNew() const override { return new MapManager(ID); };

	void handleKeyPress(sf::Event keyPress) override;

	void openStatusScreen(Squad* sqd);

	void compileVisualStack(GraphicsInterface* stack) override;

	void moveCursor(Directions dir);
	bool isPaused() { return nrOfRunningAnims > 0; };
	bool isBusy() override;

	void openMenu(Menu menu) override;
	void closeMenu() override;
	//void controlMenu(sf::Event keyPress) override;

	void setBattleManagerPointer(If_BattleManager* bMan) { bManager = bMan; };
	virtual StructuredEvent* getOpeningEvent() override;

	void levelUpUnit(Squad squad, int unitID);
	void levelUpSquad(Squad squad);
};