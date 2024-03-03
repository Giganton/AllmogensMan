#pragma once
#include "BattleAnimation.h"
#include "BattleStage.h"
#include "Profession.h"
#include "ProfessionID.h"

class StringHandler;
class IdCreator;
enum class TestTag;

class ActionTests
{
private:
	BattleAnimation battleAnim;
	BattleStage battleStage;

	//std::map < ProfessionTag, sf::Texture>* profTextureMap;
	sf::RenderWindow* window = nullptr;
	GraphicsAssets* assets = nullptr;

	std::map<ProfessionTag, Profession> profMap;

	StringHandler* strHandler = nullptr;
	IdCreator* idCreator = nullptr;

	std::vector<std::pair<TestTag, bool>> testList;
	std::vector<std::pair<TestTag, bool>> testResults;

	unsigned int testIndex = 0;
	bool drawingTest = false;


	Squad squad1;
	Squad squad2;

	/***************************************************************************************/
	std::pair<bool, BattleStage> StrikeTest1();

	std::pair<bool, BattleStage> MartyrTest1();
	std::pair<bool, BattleStage> MartyrTest2();
	std::pair<bool, BattleStage> MartyrTest3();
	std::pair<bool, BattleStage> MartyrTest4();

	std::pair<bool, BattleStage> RiposteTest1();

	std::pair<bool, BattleStage> MartyrRiposteTest();
public:
	ActionTests() {};
	ActionTests(std::map<ProfessionTag, Profession> pMap, StringHandler* strHand, IdCreator* idCr, sf::RenderWindow* ww, GraphicsAssets* assts);

	void setupTest(bool drawTest);
	void startNextTest();

	std::pair<bool, BattleStage> doTheTest(TestTag testTag);

	void progress();
};


enum class TestTag
{
	StrikeTest1 ,
	MartyrTest1 ,
	MartyrTest2 ,
	MartyrTest3,
	MartyrTest4,
	RiposteTest1,
	MartyrRiposteTest
};
