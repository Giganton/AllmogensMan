#include "BattleMap.h"
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "BattleStage.h"
#include "FightResults.h"
#include "StatusScreen.h"
#include "MapManager.h"
#include "SquadManager.h"
#include "GraphicsInterface.h"
#include "Camp.h"
#include "idCreator.h"
#include "BattleManager.h"
#include "RootLink.h"
#include "ChapterCollection.h"

class Flag;

enum class State { initialState, mapBrowse, camp };
class StringHandler;


class MasterState
{
private:
	State state = State::initialState;
	Menu menu;
	
	bool menuIsActive = false;
	bool mapIsActive = false;

public:
	MasterState() {};
	MasterState(State st);

	State getState() { return state; };
	bool isMenuActive() { return menuIsActive; };
	bool isMapActive() { return mapIsActive; };
	void deActivateMenu() { menuIsActive = false; };
	void activateMenu() { menuIsActive = true; };
	Menu getMenu() { return menu; };
	void setMenu(Menu mn) { menu = mn; };
};



class GameMaster
{
private:
	std::map<ProfessionTag, Profession> profMap;

	StringHandler* stringHandler = nullptr;
	bool debugMode = false;

	IdCreator idCreator;

	Flag player;
	BattleManager battleManager;

	RootLink rootLink;
	ExternalStateControls rootControls;

	Camp camp;
	bool openMapBucket = false;
	bool openCampBucket = false;

	ChapterCollection chapterCollection;
	Chapter currentChapter;

	//methods
	void initPlayer();
	void initBattle();
	void startBattle();
	void openCampScreen();
	void handleRootControls();
	std::vector<Unit> generateShopUnits();

public:
	GameMaster();
	GameMaster(IdCreator idC, std::map<ProfessionTag, Profession> pMap, std::map<std::string, TerrainTypes> terrainMap, StringHandler* strHandler, ChapterCollection chaptColl, bool debugging);
	GameMaster(const GameMaster& cpMapman);
	GameMaster& operator=(const GameMaster asMapman);

	void takeInput(sf::Event keyPress);

	void createVisualStack(GraphicsInterface* graphInt);
	void passMouseSignals(std::vector<MouseSignal> signals) { rootLink.passMouseSignals(signals); };
	void run();
};