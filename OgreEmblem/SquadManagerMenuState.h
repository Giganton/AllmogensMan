#pragma once
#include "SquadManagerState.h"
#include "MenuManager.h"

class SquadManagerMenuState : public SquadManagerState, public MenuManager
{
private:
	void handleKeyPress(sf::Event keypress) override;
public:
	SquadManagerMenuState() {};
	SquadManagerMenuState(SquadManager* manager, int lvl) : SquadManagerState(manager, lvl) {};
};

class SquadMenuState : public SquadManagerMenuState
{
private:
	Squad* selectedSquad1 = nullptr;

	bool* squadEdited = nullptr;

	bool finishedEditing = false;

	void disbandSquad(DisbandSquadCommand command);
	void performMenuAction(int action) override;
	void openSquadEditor();
	void closeFollowers() override;

	Menu createSquadMenu();

public:
	SquadMenuState() {};
	SquadMenuState(SquadManager* manager, int lvl, Squad* squad, bool* squadEdited);

	SquadMenuState* clone() const override { return new SquadMenuState(*this); };
	SquadMenuState* allocateNew() const override { return new SquadMenuState(); };

	StructuredEvent* getOpeningEvent() override;
};


class UnitMenuState : public SquadManagerMenuState
{
	Unit* selectedUnit = nullptr;
	void performMenuAction(int action) override;

	UnitMenuCommand* commandBasket = nullptr;

	Menu createUnitMenu(UnitMenuVariant variant);
public:
	UnitMenuState() {};
	UnitMenuState(SquadManager* manager, int lvl, Unit* unit, UnitMenuCommand* command, UnitMenuVariant variant);

	UnitMenuState* clone() const override { return new UnitMenuState(*this); };
	UnitMenuState* allocateNew() const override { return new UnitMenuState(); };

	StructuredEvent* getOpeningEvent() override;
};