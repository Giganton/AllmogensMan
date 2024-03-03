#pragma once
#include "InputLink.h"
#include "DraftMouseButtons.h"
#include "Unit.h"
#include "UnitShop.h"
#include "StateHandler.h"

class Flag;
class IdCreator;
class StringHandler;

enum DraftScreenStateState { DSSS_none , DSSS_browsing , DSSS_addingSquad , DSSS_addSquadPendingConfirmation, DSSS_addSquadNamingSquad, DSSS_leavePagePendingConfirmation};

class DraftScreenState : public InputLink
{
private:
	IdCreator* squadCreator = nullptr;
	StringHandler* stringHandler = nullptr;

	DraftScreenStateState state = DraftScreenStateState::DSSS_none;
	StateHandler stateHandler;

	int hoveredButton = -1;
	bool hoveringButton = false;

	Flag* playerTeam = nullptr;

	Squad newSquadSlot;
	//std::vector<Unit> draftChoices;
	UnitShop draftChoices;

	bool squad1Selected = false;
	Squad* selectedSquad1 = nullptr;
	bool squad2Selected = false;
	Squad* selectedSquad2 = nullptr;

	bool unitClicked = false;
	MouseSignal clickedUnit;

	MouseSignal newSquadLeaderPosition;
	bool newSquadConfirmed = false;
	Squad newSquadTempPos;

	bool readyForBattle = false;

	std::string* newSquadNameBucket = nullptr;

	bool closeConfirmed = false;

	void clickTestButton();
	void selectUnit(MouseSignal signal);
	void deselectUnit();
	void deselectSquad(bool windowOne);
	void selectSquad(MouseSignal signal, bool windowOne);
	void selectSquad(Squad* sqd, bool windowOne);

	int findSquadWithUnit(int unitID);
	Unit* findUnitPointer(int unitID);
	Squad* findSquadPointer(int sqdID);

	std::pair<Squad* , Unit*> decipherUnitInSquadSignal(MouseSignal signal);
	Squad* decipherSquadSignal(MouseSignal signal);
	void handleKeyPress(sf::Event inputEvent) override;
	void handleMouseEvent(sf::Event mouseEvent) override;
	void handleMouseClickLeft(sf::Event mouseEvent);

	void handleSquadClick(MouseSignal signal);
	void handleSquadClick_browsing(MouseSignal signal);
	void handleSquadClick_addingSquad(MouseSignal signal);

	void handleSquadInfoWindowClick(MouseSignal signal);

	void handleEmptyPortraitSquadClick(MouseSignal signal);
	void handleEmptyPortraitSquadClick_browsing(MouseSignal signal);
	void handleEmptyPortraitSquadClick_addingSquad(MouseSignal signal);

	void handleUnitInSquadClick(MouseSignal signal);
	void handleUnitInShopClick(MouseSignal signal);
	void handleNewSquadButtonClick();

	void enterAddSquadState();
	void enterBrowsingState();
	void enterNamingState(std::string leaderName);

	void performClickSquadSwap(MouseSignal oldClick, MouseSignal newClick);

	void addNewSquadToPlayer(Squad sqd);

	void postSubLevelClosing() override;

	ExternalStateControls generateExternalControls() override;
public:
	DraftScreenState() {};
	DraftScreenState(int lvl, Flag* player, std::vector<Unit> unitsToPick, IdCreator* idCr, StringHandler* strHandler);

	DraftScreenState* clone() const override { return new DraftScreenState(*this); };
	DraftScreenState* allocateNew() const override { return new DraftScreenState(); };

	StructuredEvent* getOpeningEvent() override;
};