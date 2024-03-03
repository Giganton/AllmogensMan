#pragma once
#include "InputLink.h"
#include "Menu.h"
#include "Browser.h"
#include "Flag.h"
#include "SquadManagerCommands.h"
#include "BrowserLinker.h"
#include "MenuManager.h"

class SquadManager;


class SquadManagerState : public InputLink
{
protected:

	SquadManager* squadManager = nullptr;
	//void closeFollowers() override;
public:
	SquadManagerState() {};
	SquadManagerState(SquadManager* man, int lvl) { squadManager = man; level = lvl; initTrigger = true; };

	//void receiveInput(sf::Event keyPress) override;
	//GraphicalEventQueue pullClosingEvents() override;
};

class BrowseSquadsState : public SquadManagerState
{
private:
	Browser squadBrowser;
	Browsable addSquad;
	std::vector<Squad*> squadList;

	bool finishedEditing = false;

	void handleKeyPress(sf::Event keypress) override;
	void openSquadMenu(Squad* selectedSquad1);
	void openSquadEditor();
	void absorbBrowserEvents();
	void closeFollowers() override;
	void initSquadBrowser();
	bool initNeeded();
public:
	BrowseSquadsState() {};
	BrowseSquadsState(SquadManager* manager, int lvl);

	BrowseSquadsState* clone() const override { return new BrowseSquadsState(*this); };
	BrowseSquadsState* allocateNew() const override { return new BrowseSquadsState(); };

	StructuredEvent* getOpeningEvent() override;
};

enum SquadMenuOptions { EditSquad, RemoveSquad, CancelSquadMenu };
enum UnitMenuOptions { MoveUnit, SwapUnit, CancelUnitMenu, selectLeader };
enum class UnitMenuCommand { none, pickUpUnit, swapUnit, selectAsLeader };
enum class UnitMenuVariant { none, hoveringUnit, holdingUnit, selectingLeader };

class SquadEditorState : public SquadManagerState
{
private:
	Squad newSquad;
	BrowserLinker browserCluster;
	Browser squadBrowser;
	Browser unitBrowser;
	std::vector<Unit> bench;

	Squad editedSquad;
	bool editing = false;
	bool* finishedEditing = nullptr;

	bool selectingLeader = false;
	int selectedLeaderID = -1;

	UnitMenuCommand menuCommand = UnitMenuCommand::none;

	void absorbBrowserEvents();
	void initUnitBrowser();
	void initSquadBrowser();
	void initSquadBrowser(Squad squad);
	void squadBrowserFinished();
	void unitBrowserFinished();
	void handleKeyPress(sf::Event keypress) override;
	void openUnitMenu(Unit* selectedUnit, UnitMenuVariant variant);
	void closeFollowers() override;
	void finishEditing();
	void createSquad(int leaderID);
	void goToLeaderSelection();
	Unit* findUnit(BrowsingData bData);
public:
	SquadEditorState() {};
	SquadEditorState(SquadManager* manager, int level, bool* finishContainer);
	SquadEditorState(Squad squad, SquadManager* manager, int level, bool* finishContainer);

	SquadEditorState* clone() const override { return new SquadEditorState(*this); };
	SquadEditorState* allocateNew() const override { return new SquadEditorState(); };

	StructuredEvent* getOpeningEvent() override;
};