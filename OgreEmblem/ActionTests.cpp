#include "ActionTests.h"
#include "StringHandler.h"
#include "idCreator.h"
#include "allActions.h"


std::vector<std::pair<TestTag, bool>> allTests = {
	{ TestTag::StrikeTest1, true} ,
	{ TestTag::MartyrTest1, true} ,
	{ TestTag::MartyrTest2, true} ,
	{ TestTag::MartyrTest3, true} ,
	{ TestTag::MartyrTest4, true} ,
	{ TestTag::RiposteTest1, true},
	{ TestTag::MartyrRiposteTest, true}
};

std::vector<std::pair<TestTag, bool>> devTests = {
	{ TestTag::MartyrRiposteTest, true}
};

ActionTests::ActionTests(std::map<ProfessionTag, Profession> pMap, StringHandler* strHand, IdCreator* idCr, sf::RenderWindow* ww, GraphicsAssets* assts)
{
	profMap = pMap;
	strHandler = strHand;
	idCreator = idCr;

	testList = devTests;

	assets = assts;
	window = ww;
}

void ActionTests::setupTest(bool drawTest)
{
	Strike strikeAction = Strike();
	Unit leader1 = idCreator->createUnit(strHandler->takeRandomName(), 8, 4, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit leader2 = idCreator->createUnit(strHandler->takeRandomName(), 8, 4, 2, &profMap.find(ProfessionTag::enumHero)->second);
	squad1 = idCreator->createSquad(leader1, SquadPos(1, 1), strHandler);
	squad2 = idCreator->createSquad(leader2, SquadPos(1, 2), strHandler);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &squad1, &squad2);
	battleStage.doBattle();

	if (drawTest)
	{
		BattleVisualData vData = battleStage.getVisuals();
		battleAnim = BattleAnimation(window, assets);
		battleAnim.setup(vData);
		drawingTest = true;
	}
}

std::pair<bool, BattleStage> ActionTests::StrikeTest1()
{
	Strike strikeAction = Strike();
	SquadPos pos1 = SquadPos(1, 1);
	SquadPos pos2 = SquadPos(1, 2);
	int HP = 10;
	int atk = 5;
	int def = 2;
	Unit leader1 = idCreator->createUnit(strHandler->takeRandomName(), 100, atk, 3, &profMap.find(ProfessionTag::enumHero)->second);
	Unit leader2 = idCreator->createUnit(strHandler->takeRandomName(), HP, 50, def, &profMap.find(ProfessionTag::enumHero)->second);
	squad1 = idCreator->createSquad(leader1, pos1, strHandler);
	squad2 = idCreator->createSquad(leader2, pos2, strHandler);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &squad1, &squad2);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();

	bool defHPOk = squad2.getUnitPtr(pos2)->getHP() == HP-(atk-def);
	bool atkHPOk = squad1.getUnitPtr(pos1)->getHP() == leader1.getMaxHP();
	bool testOk = defHPOk && atkHPOk;

	return { testOk , battleStage };
}

std::pair<bool, BattleStage> ActionTests::MartyrTest1()
{
	Strike strikeAction = Strike();

	SquadPos pos1 = SquadPos(1, 1);
	SquadPos pos2 = SquadPos(1, 2);
	SquadPos pos3 = SquadPos(1, 1);

	Unit leader1 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumHero)->second);

	Unit leader2 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit unit = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumWizard)->second);
	leader2.addReAction(new Martyr());

	Squad atkSquad = idCreator->createSquad(leader1, pos1, strHandler);
	Squad defSquad = idCreator->createSquad(leader2, pos2, strHandler);
	defSquad.addUnit(unit, pos3);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();

	bool martHPOk = defSquad.getUnitPtr(pos2)->getHP() == 7;
	bool saveeHPOk = defSquad.getUnitPtr(pos3)->getHP() == unit.getMaxHP();
	bool atkHPOk = atkSquad.getUnitPtr(pos1)->getHP() == leader1.getMaxHP();

	bool testOk = martHPOk && atkHPOk && saveeHPOk;

	return { testOk , battleStage };
}

std::pair<bool, BattleStage> ActionTests::MartyrTest2()
{
	Strike strikeAction = Strike();

	SquadPos pos1 = SquadPos(1, 1);
	SquadPos pos2 = SquadPos(1, 2);
	SquadPos pos3 = SquadPos(1, 1);
	SquadPos pos4 = SquadPos(1, 0);

	Unit leader1 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumHero)->second);

	Unit leader2 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit unit1 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit unit2 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);
	leader2.addReAction(new Martyr());
	unit2.addReAction(new Martyr());

	Squad atkSquad = idCreator->createSquad(leader1, pos1, strHandler);
	Squad defSquad = idCreator->createSquad(leader2, pos2, strHandler);
	defSquad.addUnit(unit1, pos3);
	defSquad.addUnit(unit2, pos4);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();

	bool martHPOk = defSquad.getUnitPtr(pos2)->getHP() == 7;
	bool saveeHPOk = defSquad.getUnitPtr(pos3)->getHP() == unit1.getMaxHP();
	bool atkHPOk = atkSquad.getUnitPtr(pos1)->getHP() == leader1.getMaxHP();

	bool testOk = martHPOk && atkHPOk && saveeHPOk;

	return { testOk , battleStage };
}

std::pair<bool, BattleStage> ActionTests::MartyrTest3()
{
	Strike strikeAction = Strike();

	SquadPos pos1 = SquadPos(1, 1);
	SquadPos pos2 = SquadPos(1, 2);
	SquadPos pos3 = SquadPos(1, 1);
	SquadPos pos4 = SquadPos(1, 2);

	Unit leader1 = idCreator->createUnit(strHandler->takeRandomName(), 10, 100, 2, &profMap.find(ProfessionTag::enumHero)->second);

	Unit leader2 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit unit1 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit unit2 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);
	leader2.addReAction(new Martyr());

	Squad atkSquad = idCreator->createSquad(leader1, pos1, strHandler);
	Squad defSquad = idCreator->createSquad(leader2, pos2, strHandler);
	defSquad.addUnit(unit1, pos3);
	atkSquad.addUnit(unit2, pos4);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();

	bool martHPOk = defSquad.getUnitPtr(pos2)->getHP() == 0;
	bool saveeHPOk = defSquad.getUnitPtr(pos3)->getHP() == unit1.getMaxHP() - 6;
	bool atkHPOk = atkSquad.getUnitPtr(pos1)->getHP() == leader1.getMaxHP();

	bool testOk = martHPOk && atkHPOk && saveeHPOk;

	return { testOk , battleStage };
}

std::pair<bool, BattleStage> ActionTests::MartyrTest4()
{
	Strike strikeAction = Strike();

	SquadPos pos1 = SquadPos(0, 1);
	SquadPos pos2 = SquadPos(1, 1);
	SquadPos pos3 = SquadPos(1, 2);

	SquadPos pos4 = SquadPos(1, 1);
	SquadPos pos5 = SquadPos(1, 2);

	Unit leader1 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumHero)->second);

	Unit leader2 = idCreator->createUnit(strHandler->takeRandomName(), 11, 5, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit unit1 = idCreator->createUnit(strHandler->takeRandomName(), 12, 5, 2, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit unit2 = idCreator->createUnit(strHandler->takeRandomName(), 13, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);
	Unit unit3 = idCreator->createUnit(strHandler->takeRandomName(), 14, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);
	leader2.addReAction(new Martyr());

	Squad atkSquad = idCreator->createSquad(leader1, pos4, strHandler);
	Squad defSquad = idCreator->createSquad(leader2, pos1, strHandler);
	defSquad.addUnit(unit1, pos2);
	defSquad.addUnit(unit2, pos3);
	atkSquad.addUnit(unit3, pos5);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();

	bool martHPOk = defSquad.getUnitPtr(pos1)->getHP() == leader2.getMaxHP() - 3;
	bool saveeHPOk = defSquad.getUnitPtr(pos2)->getHP() == unit1.getMaxHP();
	bool bystanderHPOK = defSquad.getUnitPtr(pos3)->getHP() == unit2.getMaxHP() - 3;

	bool testOk = martHPOk && bystanderHPOK && saveeHPOk;

	return { testOk , battleStage };
}
std::pair<bool, BattleStage> ActionTests::MartyrRiposteTest()
{
	Strike strikeAction = Strike();

	SquadPos pos1 = SquadPos(1, 1);
	SquadPos pos2 = SquadPos(0, 1);
	SquadPos pos3 = SquadPos(1, 1);


	Unit leader1 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumHero)->second);

	Unit leader2 = idCreator->createUnit(strHandler->takeRandomName(), 11, 5, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit unit1 = idCreator->createUnit(strHandler->takeRandomName(), 12, 5, 2, &profMap.find(ProfessionTag::enumWizard)->second);

	leader2.addReAction(new Martyr());
	leader2.addReAction(new Riposte());

	Squad atkSquad = idCreator->createSquad(leader1, pos1, strHandler);
	Squad defSquad = idCreator->createSquad(leader2, pos2, strHandler);
	defSquad.addUnit(unit1, pos3);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();

	bool martHPOk = defSquad.getUnitPtr(pos2)->getHP() == leader2.getMaxHP() - 3;
	bool saveeHPOk = defSquad.getUnitPtr(pos3)->getHP() == unit1.getMaxHP();
	bool atkerHPOK = atkSquad.getUnitPtr(pos1)->getHP() == leader1.getMaxHP() - 3;

	bool testOk = martHPOk && atkerHPOK && saveeHPOk;

	return { true , battleStage };
}

std::pair<bool, BattleStage> ActionTests::RiposteTest1()
{
	Strike strikeAction = Strike();

	SquadPos pos1 = SquadPos(1, 1);
	SquadPos pos2 = SquadPos(1, 1);

	Unit leader1 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit leader2 = idCreator->createUnit(strHandler->takeRandomName(), 10, 5, 2, &profMap.find(ProfessionTag::enumHero)->second);
	leader2.addReAction(new Riposte());

	Squad atkSquad = idCreator->createSquad(leader1, pos1, strHandler);
	Squad defSquad = idCreator->createSquad(leader2, pos2, strHandler);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();

	return { true , battleStage };
}

std::pair<bool, BattleStage> ActionTests::doTheTest(TestTag testTag)
{
	switch (testTag)
	{
	case TestTag::StrikeTest1:
		return StrikeTest1();
		break;
	case TestTag::MartyrTest1:
		return MartyrTest1();
		break;
	case TestTag::MartyrTest2:
		return MartyrTest2();
		break;
	case TestTag::MartyrTest3:
		return MartyrTest3();
		break;
	case TestTag::MartyrTest4:
		return MartyrTest4();
		break;
	case TestTag::RiposteTest1:
		return RiposteTest1();
		break;
	case TestTag::MartyrRiposteTest:
		return MartyrRiposteTest();
		break;
	default:
		throw new std::exception();
		return { false , BattleStage() };
	}
}

void ActionTests::progress()
{
	if (drawingTest)
	{
		battleAnim.progress();
		battleAnim.draw();
		if (battleAnim.isAnimationDone())
		{
			startNextTest();
		}
	}
	else
	{
		startNextTest();
	}
}

void ActionTests::startNextTest()
{
	std::pair<bool, BattleStage> retVal = doTheTest(testList.at(testIndex).first);

	if (!retVal.first)
	{
		throw new std::exception();
	}

	testResults.push_back({ testList.at(testIndex).first , retVal.first });


	if (testList.at(testIndex).second)
	{
		BattleVisualData vData = retVal.second.getVisuals();
		battleAnim = BattleAnimation(window, assets);
		battleAnim.setup(vData);
		drawingTest = true;
	}
	if (testList.size() > testIndex + 1)
	{
		testIndex++;
	}
	else
	{
		testIndex = 0;
	}
}