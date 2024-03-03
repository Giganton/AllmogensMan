#include "pch.h"
#include "AllmogeTest.h"
#include "TraitTag.h"
#include "Career.h"
#include "AllJobs.h"
#include "AllActions.h"
#include "MainHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void ActionTests::ActionTests::StrikeTest1()
{
	//idCreator = IdCreator();
	//strHandler = StringHandler(Language::Svenska);hej
			
	Strike strikeAction = Strike();
	SquadPos pos1 = SquadPos(1, 1);
	SquadPos pos2 = SquadPos(1, 1);
	SquadPos pos3 = SquadPos(1, 2);

	int HP = 10;
	int atk = 5;
	int def = 2;

	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), 100, atk, 3, &profMap.find(ProfessionTag::enumHero)->second);
	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP, 50, def, &profMap.find(ProfessionTag::enumHero)->second);
	Unit unit1 = idCreator.createUnit(strHandler.takeRandomName(), 100, atk, 3, &profMap.find(ProfessionTag::enumWarrior)->second);
			
	Squad squad1 = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad squad2 = idCreator.createSquad(leader2, pos2, &strHandler);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &squad1, &squad2);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();

	Assert::AreEqual(squad2.getUnitPtr(pos2)->getHP(), HP - (atk - def));
	Assert::AreEqual(squad1.getUnitPtr(pos1)->getHP(), leader1.getMaxHP());

	Assert::IsTrue(results.didActionResolve());

	//Assert::AreEqual(results.getEffects().at(0).damageTaken, atk - def);
	Assert::AreEqual(leader2.getMaxHP() - leader2.getHP(), atk - def);
	//Assert::AreEqual(results.getEffects().at(0).affectedID, leader2.getID());
}
/*
void ActionTests::ActionTests::MartyrTest1()
{
	Strike strikeAction = Strike();

	int HP = 10;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(1, 1);
	SquadPos pos2 = SquadPos(1, 2);
	SquadPos pos3 = SquadPos(1, 1);

	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumHero)->second);

	Profession prof = Profession(ProfessionTag::enumWizard);
	Career car = Career(new Hero,0,new DummyJob, 0, new DummyJob,0);
	car.masterCurrentTier();

	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumHero)->second, car);
	Unit unit = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumWizard)->second);


	Squad atkSquad = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad defSquad = idCreator.createSquad(leader2, pos2, &strHandler);
	defSquad.addUnit(unit, pos3);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();

	Assert::AreEqual(defSquad.getUnitPtr(pos2)->getHP(), HP-(atk-def));

	Assert::AreEqual(defSquad.getUnitPtr(pos3)->getHP(), HP);
	Assert::AreEqual(atkSquad.getUnitPtr(pos1)->getHP(), HP);
}
void ActionTests::ActionTests::MartyrTest2()
{
	Strike strikeAction = Strike();

	int HP = 10;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(1, 1);
	SquadPos pos2 = SquadPos(1, 2);
	SquadPos pos3 = SquadPos(1, 1);
	SquadPos pos4 = SquadPos(1, 0);

	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumHero)->second);

	Profession prof = Profession(ProfessionTag::enumWizard);
	Career car1 = Career(new Hero, 0, new DummyJob, 0, new DummyJob, 0);
	car1.masterCurrentTier();

	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumWarrior)->second, car1);
	Unit unit1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit unit2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumWarrior)->second, car1);

	Squad atkSquad = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad defSquad = idCreator.createSquad(leader2, pos2, &strHandler);
	defSquad.addUnit(unit1, pos3);
	defSquad.addUnit(unit2, pos4);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	std::list<ActionResults> resultsList = battleStage.getResults();
	ActionResults results = battleStage.getResults().front();

	Assert::AreEqual(defSquad.getUnitPtr(pos2)->getHP(), HP -(atk-def));
	Assert::AreEqual(defSquad.getUnitPtr(pos3)->getHP(), HP);
	Assert::AreEqual(atkSquad.getUnitPtr(pos1)->getHP(), HP);
}
void ActionTests::ActionTests::MartyrTest3()
{
	Strike strikeAction = Strike();

	int HP = 10;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(1, 1);
	SquadPos pos2 = SquadPos(1, 2);
	SquadPos pos3 = SquadPos(1, 1);
	SquadPos pos4 = SquadPos(1, 2);

	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP, 100, def, &profMap.find(ProfessionTag::enumHero)->second);
	
	Profession prof = Profession(ProfessionTag::enumWizard);
	Career car1 = Career(new Hero, 0, new DummyJob, 0, new DummyJob, 0);
	car1.masterCurrentTier();

	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumHero)->second, car1);
	Unit unit1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit unit2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumWarrior)->second);

	Squad atkSquad = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad defSquad = idCreator.createSquad(leader2, pos2, &strHandler);
	defSquad.addUnit(unit1, pos3);
	atkSquad.addUnit(unit2, pos4);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();

	Assert::AreEqual(defSquad.getUnitPtr(pos2)->getHP(), 0);
	Assert::AreEqual(defSquad.getUnitPtr(pos3)->getHP(), HP - (atk-def)*2);
	Assert::AreEqual(atkSquad.getUnitPtr(pos1)->getHP(), HP);
}
void ActionTests::ActionTests::MartyrTest4()
{
	Strike strikeAction = Strike();

	int HP = 10;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(0, 1);
	SquadPos pos2 = SquadPos(1, 1);
	SquadPos pos3 = SquadPos(1, 2);

	SquadPos pos4 = SquadPos(1, 1);
	SquadPos pos5 = SquadPos(1, 2);

	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), 10, atk, def, &profMap.find(ProfessionTag::enumHero)->second);

	Profession prof = Profession(ProfessionTag::enumWizard);
	Career car1 = Career(new Hero, 0, new DummyJob, 0, new DummyJob, 0);
	car1.masterCurrentTier();

	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), 11, atk, def, &profMap.find(ProfessionTag::enumHero)->second, car1);
	Unit unit1 = idCreator.createUnit(strHandler.takeRandomName(), 12, atk, def, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit unit2 = idCreator.createUnit(strHandler.takeRandomName(), 13, atk, def, &profMap.find(ProfessionTag::enumWarrior)->second);
	Unit unit3 = idCreator.createUnit(strHandler.takeRandomName(), 14, atk, def, &profMap.find(ProfessionTag::enumWarrior)->second);

	Squad atkSquad = idCreator.createSquad(leader1, pos4, &strHandler);
	Squad defSquad = idCreator.createSquad(leader2, pos1, &strHandler);
	defSquad.addUnit(unit1, pos2);
	defSquad.addUnit(unit2, pos3);
	atkSquad.addUnit(unit3, pos5);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();
	int hp = defSquad.getUnitPtr(pos1)->getHP();
	int hp2 = leader2.getMaxHP() - (atk - def);

	Assert::AreEqual(defSquad.getUnitPtr(pos1)->getHP(), leader2.getMaxHP() - (atk-def));
	Assert::AreEqual(defSquad.getUnitPtr(pos2)->getHP(), unit1.getMaxHP());
	Assert::AreEqual(defSquad.getUnitPtr(pos3)->getHP(), unit2.getMaxHP() - (atk-def));
}
void ActionTests::ActionTests::MartyrRiposteTest()
{
	Strike strikeAction = Strike();

	int HP = 10;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(1, 1);
	SquadPos pos2 = SquadPos(0, 1);
	SquadPos pos3 = SquadPos(1, 1);


	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), 10, atk, def, &profMap.find(ProfessionTag::enumHero)->second);
	
	Profession prof = Profession(ProfessionTag::enumWizard);
	Career car1 = Career(new Hero, 0, new Fencer, 0, new DummyJob, 0);
	car1.masterCurrentTier();
	car1.masterCurrentTier();

	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), 11, atk, def, &profMap.find(ProfessionTag::enumHero)->second, car1);
	Unit unit1 = idCreator.createUnit(strHandler.takeRandomName(), 12, atk, def, &profMap.find(ProfessionTag::enumWizard)->second);

	Squad atkSquad = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad defSquad = idCreator.createSquad(leader2, pos2, &strHandler);
	defSquad.addUnit(unit1, pos3);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();
	//Assert::IsTrue(true);
	if (defSquad.getUnitPtr(pos2)->getHP() != leader2.getMaxHP())
	{
		int hej = 1;
		hej++;
	}
	Assert::AreEqual(defSquad.getUnitPtr(pos2)->getHP(), leader2.getMaxHP());
	Assert::AreEqual(defSquad.getUnitPtr(pos3)->getHP(), unit1.getMaxHP());
	Assert::AreEqual(atkSquad.getUnitPtr(pos1)->getHP(), leader1.getMaxHP() - (atk-def));
}*/
void ActionTests::ActionTests::RiposteTest1()
{
	Strike strikeAction = Strike();

	int HP = 10;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(SquadColCoord::front, SquadRowCoord::mid);
	SquadPos pos2 = SquadPos(SquadColCoord::front, SquadRowCoord::mid);
	SquadPos pos3 = SquadPos(SquadColCoord::back, SquadRowCoord::mid);

	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumHero)->second);

	Profession prof = Profession(ProfessionTag::enumWizard);
	Career car1 = Career(new Fencer, 0, new DummyJob, 0, new DummyJob, 0);
	car1.masterCurrentTier();

	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumHero)->second, car1);

	//leader2.addTraitRandomly(new FencingDrill());

	Squad atkSquad = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad defSquad = idCreator.createSquad(leader2, pos2, &strHandler);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();

	Assert::AreEqual(defSquad.getUnitPtr(pos1)->getHP(), leader1.getMaxHP());
	Assert::AreEqual(atkSquad.getUnitPtr(pos2)->getHP(), leader2.getMaxHP() - (atk - def));
}
void ActionTests::ActionTests::RageTest()
{
	Strike strikeAction = Strike();

	int HP = 100;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(SquadColCoord::front, SquadRowCoord::mid);
	SquadPos pos2 = SquadPos(SquadColCoord::front, SquadRowCoord::mid);
	SquadPos pos3 = SquadPos(SquadColCoord::back, SquadRowCoord::mid);

	Profession prof = Profession(ProfessionTag::enumWarrior, 5);
	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &prof);

	Career car1 = Career(new Fencer, 3, new DummyJob, 3, new DummyJob, 3);
	car1.addLesserTrait(Trait(TraitTag::enumRage));

	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &prof, car1);

	//leader2.addTraitRandomly(new FencingDrill());

	Squad atkSquad = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad defSquad = idCreator.createSquad(leader2, pos2, &strHandler);
	Unit unit1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &prof);
	atkSquad.addUnit(unit1, pos3);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();
	int totHPLoss = 2 * HP - (atkSquad.getUnitPtr(pos1)->getHP()) - (atkSquad.getUnitPtr(pos3)->getHP());

	Assert::AreEqual(totHPLoss, 2*(atk - def));
	Assert::AreEqual(defSquad.getUnitPtr(pos2)->getHP(), leader2.getMaxHP() - 2*(atk - def));
}

void ActionTests::ActionTests::GiantStrengthTest1()
{
	int HP = 10;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(SquadColCoord::front, SquadRowCoord::mid);
	SquadPos pos2 = SquadPos(SquadColCoord::front, SquadRowCoord::mid);
	SquadPos pos3 = SquadPos(SquadColCoord::back, SquadRowCoord::mid);

	Career car1 = Career(new DummyJob, 3, new DummyJob, 3, new DummyJob, 3);
	car1.addLesserTrait(Trait(TraitTag::enumGiantStrength));
	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumHero)->second, car1);

	Profession prof = Profession(ProfessionTag::enumWizard);

	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumHero)->second);
	Unit unit1 = idCreator.createUnit(strHandler.takeRandomName(), 12, atk, def, &profMap.find(ProfessionTag::enumWizard)->second);

	//leader2.addTraitRandomly(new FencingDrill());

	Squad atkSquad = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad defSquad = idCreator.createSquad(leader2, pos2, &strHandler);
	defSquad.addUnit(unit1, pos3);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();
	int HP_unit = defSquad.getUnitPtr(pos3)->getHP();
	int maxHP_unit = defSquad.getUnitPtr(pos3)->getMaxHP();
	Assert::IsTrue(HP_unit == maxHP_unit - 1);
}
void FightTests::TraitTests::FencingDrillTest()
{
	int HP = 10;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(1, 1);
	SquadPos pos2 = SquadPos(1, 1);

	Profession prof = Profession(ProfessionTag::enumWizard);
	Career car1 = Career(new Fencer, 0, new DummyJob, 0, new DummyJob, 0);
	car1.masterCurrentTier();

	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumHero)->second);
	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &profMap.find(ProfessionTag::enumHero)->second, car1);

	Squad atkSquad = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad defSquad = idCreator.createSquad(leader2, pos2, &strHandler);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionSetup actionSetup = battleStage.getDefSquad()->findUnitPtr(leader2.getID())->getActionSetup();
	if (actionSetup.getReactionsPtr()->size() > 0)
	{
		ActionTag tag = actionSetup.getReactionsPtr()->at(0)->getTag();
		Assert::IsTrue(tag == ActionTag::Riposte);
	}
	else
	{
		Assert::IsTrue(false);
	}
}

void ActionTests::ActionTests::ShieldBearerTest()
{
	int HP = 10;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(SquadColCoord::front, SquadRowCoord::mid);
	SquadPos pos2 = SquadPos(SquadColCoord::front, SquadRowCoord::mid);

	Profession prof1 = Profession(ProfessionTag::enumWarrior, 5);
	Profession prof2 = Profession(ProfessionTag::enumWarrior, 2);

	Career car1 = Career(new DummyJob, 3, new DummyJob, 3, new DummyJob, 3);
	car1.addLesserTrait(Trait(TraitTag::enumShieldBearer));
	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &prof1);
	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &prof2, car1);

	Squad atkSquad = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad defSquad = idCreator.createSquad(leader2, pos2, &strHandler);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();
	int HP_unit = defSquad.getUnitPtr(pos2)->getHP();
	int maxHP_unit = defSquad.getUnitPtr(pos2)->getMaxHP();

	Assert::IsTrue(HP_unit == maxHP_unit - (atk-def));
}

void ActionTests::ActionTests::IncreaseWepProfBoonTest()
{
	int HP = 15;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(SquadColCoord::front, SquadRowCoord::mid);
	SquadPos pos2 = SquadPos(SquadColCoord::front, SquadRowCoord::top);

	Profession prof1 = Profession(ProfessionTag::enumWarrior, 5);
	Profession prof2 = Profession(ProfessionTag::enumWarrior, 2);

	Career car1 = Career(new DummyJob, 3, new DummyJob, 3, new DummyJob, 3);
	car1.addLesserTrait(Trait(TraitTag::enumShieldBearer));
	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &prof1);
	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &prof2);
	Unit unit1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &prof1);
	Unit unit2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &prof1);

	Squad atkSquad = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad defSquad = idCreator.createSquad(leader2, pos1, &strHandler);
	atkSquad.addUnit(unit1, pos2);
	defSquad.addUnit(unit2, pos2);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();
	int HP_unit1 = defSquad.getUnitPtr(pos1)->getHP();
	int maxHP_unit1 = defSquad.getUnitPtr(pos1)->getMaxHP();
	int HP_unit2 = defSquad.getUnitPtr(pos2)->getHP();
	int maxHP_unit2 = defSquad.getUnitPtr(pos2)->getMaxHP();

	Assert::IsTrue(HP_unit1 == maxHP_unit1 - 2 * (atk + 2 - def));
	Assert::IsTrue(HP_unit2 == maxHP_unit2 - (atk - def));
}

void ActionTests::ActionTests::HeavyArmorTest()
{
	int HP = 15;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(SquadColCoord::front, SquadRowCoord::mid);
	SquadPos pos2 = SquadPos(SquadColCoord::front, SquadRowCoord::top);

	Profession prof1 = Profession(ProfessionTag::enumWarrior, 5);
	Profession prof2 = Profession(ProfessionTag::enumWarrior, 3);

	Career car1 = Career(new DummyJob, 3, new DummyJob, 3, new DummyJob, 3);
	car1.addLesserTrait(Trait(TraitTag::enumHeavyArmor));
	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &prof1);
	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP, atk, def, &prof2, car1);

	Squad atkSquad = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad defSquad = idCreator.createSquad(leader2, pos1, &strHandler);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &atkSquad, &defSquad);
	battleStage.doBattle();

	ActionResults results = battleStage.getResults().front();
	int HP_unit1 = defSquad.getUnitPtr(pos1)->getHP();
	int maxHP_unit1 = defSquad.getUnitPtr(pos1)->getMaxHP();

	Assert::IsTrue(HP_unit1 == (maxHP_unit1 - 2 * (atk + 2 - def - 2)));
}


void ActionTests::ActionTests::AttachedTest()
{
	int HP1 = 150;
	int HP2 = 1;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(SquadColCoord::front, SquadRowCoord::bot);
	SquadPos pos2 = SquadPos(SquadColCoord::front, SquadRowCoord::top);
	SquadPos pos3 = SquadPos(SquadColCoord::back, SquadRowCoord::top);

	Profession prof1 = Profession(ProfessionTag::enumWarrior, 5);

	Career car1 = Career(new DummyJob, 3, new DummyJob, 3, new DummyJob, 3);
	car1.addLesserTrait(Trait(TraitTag::enumAttached));
	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP1, atk, def, &prof1);
	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP1, atk, def, &prof1, car1);
	Unit unit1 = idCreator.createUnit(strHandler.takeRandomName(), HP2, atk, def, &prof1);
	Unit unit2 = idCreator.createUnit(strHandler.takeRandomName(), HP2, atk, def, &prof1);

	Squad squad1 = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad squad2 = idCreator.createSquad(leader2, pos3, &strHandler);
	squad2.addUnit(unit1, pos1);
	squad2.addUnit(unit2, pos2);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &squad2, &squad1);
	battleStage.doBattle();

	int HP_unit1 = squad1.getUnitPtr(pos1)->getHP();
	int maxHP_unit1 = squad1.getUnitPtr(pos1)->getMaxHP();
	Assert::IsTrue(HP_unit1 == (maxHP_unit1 - 3 * (atk - def)));

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &squad1, &squad2);
	battleStage.doBattle();

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &squad2, &squad1);
	battleStage.doBattle();

	int HP_unit2 = squad1.getUnitPtr(pos1)->getHP();
	Assert::IsTrue(HP_unit2 == (HP_unit1 - 2 * (atk - def) - 3));
}

void ActionTests::ActionTests::FormationTest()
{
	int HP1 = 150;
	int HP2 = 1;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(SquadColCoord::front, SquadRowCoord::bot);
	SquadPos pos2 = SquadPos(SquadColCoord::front, SquadRowCoord::top);
	SquadPos pos3 = SquadPos(SquadColCoord::front, SquadRowCoord::mid);
	SquadPos pos4 = SquadPos(SquadColCoord::back, SquadRowCoord::top);
	SquadPos pos5 = SquadPos(SquadColCoord::back, SquadRowCoord::mid);

	Profession prof1 = Profession(ProfessionTag::enumWarrior, 5);
	Profession prof2 = Profession(ProfessionTag::enumWarrior, 5 + 2 * 2 + 3);

	Career car1 = Career(new DummyJob, 3, new DummyJob, 3, new DummyJob, 3);
	car1.addLesserTrait(Trait(TraitTag::enumFormation));

	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP1, atk, def, &prof2);
	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP1, atk, def, &prof1, car1);
	Unit unit1 = idCreator.createUnit(strHandler.takeRandomName(), HP2, atk, def, &prof1, car1);
	Unit unit3 = idCreator.createUnit(strHandler.takeRandomName(), HP2, atk, def, &prof1, car1);
	Unit unit4 = idCreator.createUnit(strHandler.takeRandomName(), HP2, atk, def, &prof1, car1);
	Unit unit2 = idCreator.createUnit(strHandler.takeRandomName(), HP2, atk, def, &prof1);

	Squad squad1 = idCreator.createSquad(leader1, pos3, &strHandler);
	Squad squad2 = idCreator.createSquad(leader2, pos3, &strHandler);
	squad2.addUnit(unit1, pos1);
	squad2.addUnit(unit2, pos2);
	squad2.addUnit(unit3, pos4);
	squad2.addUnit(unit4, pos5);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &squad1, &squad2);
	battleStage.doBattle();

	int HP_unit = squad2.getUnitPtr(pos3)->getHP();
	int maxHP_unit = squad2.getUnitPtr(pos3)->getMaxHP();
	Assert::IsTrue(HP_unit == (maxHP_unit - 2 * (atk - def + 2)));
}

void ActionTests::ActionTests::InspiringHeroismTest()
{
	int HP1 = 10;
	int HP2 = 1;
	int atk = 5;
	int def = 2;

	SquadPos pos1 = SquadPos(SquadColCoord::front, SquadRowCoord::mid);
	SquadPos pos2 = SquadPos(SquadColCoord::back, SquadRowCoord::mid);

	Profession prof1 = Profession(ProfessionTag::enumWarrior, 5);

	Career car1 = Career(new DummyJob, 3, new DummyJob, 3, new DummyJob, 3);
	car1.addLesserTrait(Trait(TraitTag::enumInspiringHeroism));

	Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), HP1, atk, def, &prof1);
	Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP1, atk, def, &prof1, car1);
	Unit unit1 = idCreator.createUnit(strHandler.takeRandomName(), HP2, atk, def, &prof1, car1);

	Squad squad1 = idCreator.createSquad(leader1, pos1, &strHandler);
	Squad squad2 = idCreator.createSquad(leader2, pos2, &strHandler);
	squad2.addUnit(unit1, pos1);

	battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &squad1, &squad2);
	battleStage.doBattle();

	int HP_unit = squad1.getUnitPtr(pos1)->getHP();
	int maxHP_unit = squad1.getUnitPtr(pos1)->getMaxHP();
	Assert::IsTrue(HP_unit == (maxHP_unit - (atk - def)));
	Assert::IsTrue(squad2.getUnitPtr(pos1)->isDead());
}

void BattleFieldTests::BattleFieldTests::initiatePlayer()
{
	Unit a00 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Unit a01 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Unit a02 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Unit a03 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Unit a04 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Unit a05 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Squad testSquad = idCr.createSquad(a00, &strHandler);
	testSquad.addUnit(a01, SquadPos(0, 0));
	testSquad.addUnit(a02, SquadPos(0, 1));
	testSquad.addUnit(a03, SquadPos(0, 2));
	testSquad.addUnit(a04, SquadPos(1, 0));
	testSquad.addUnit(a05, SquadPos(1, 2));

	player = Flag(tagID::player, &idCr);
	player.addSquad(testSquad);
}

void BattleFieldTests::BattleFieldTests::initiatePlayer(std::vector<Squad> playerSquads)
{
	unsigned int i;
	player = Flag(tagID::player, &idCr);
	for (i = 0; i < playerSquads.size(); i++)
	{
		player.addSquad(playerSquads.at(i));
	}
}

void BattleFieldTests::BattleFieldTests::levelUpSquad(Squad sqd)
{
	mBrows.levelUpSquad(sqd);
	unsigned int i;
	sf::Event even = sf::Event();
	even.type = sf::Event::KeyPressed;
	even.key.code = sf::Keyboard::X;

	for (i = 0; i < sqd.getAllLivingUnitPtrs().size(); i++)
	{
		mBrows.receiveInput(even);
	}
}

BattleFieldTests::BattleFieldTests::BattleFieldTests()
{
	idCr = IdCreator();
	strHandler = StringHandler(Language::Svenska);
	pMap = createProfMap();
}

void BattleFieldTests::BattleFieldTests::initiateBattle()
{
	Unit a00 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Squad testSquad = idCr.createSquad(a00, &strHandler);

	std::vector<VictoryCondition> vc;
	vc.push_back(VictoryCondition::route);
	testBattle = Battle("C:\\Privat\\proj\\OgEm\\OgreEmblem\\chapters\\chapter1\\battle1.json", createTerrainMap(), vc);

	testBattle.addSquad(testSquad, MapCoord(11, 11));
}

void BattleFieldTests::BattleFieldTests::initiateBattleManager()
{
	bMan = BattleManager(&idCr, &strHandler);
	mBrows = MapBrowser(1, &bMan, &nonsens, true);

	initiatePlayer();
	initiateBattle();

	bMan.initiateBattlefield(&player, testBattle);
}

void BattleFieldTests::BattleFieldTests::initiateBattleManager(std::vector<Squad> playerSquads)
{
	bMan = BattleManager(&idCr, &strHandler);
	mBrows = MapBrowser(1, &bMan, &nonsens, true);

	initiatePlayer(playerSquads);
	initiateBattle();

	bMan.initiateBattlefield(&player, testBattle);
}

void BattleFieldTests::BattleFieldTests::LevelUpTest1()
{
	Unit a00 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Squad testSquad = idCr.createSquad(a00, &strHandler);
	initiateBattleManager({ testSquad });
	Squad sqd = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0);
	Unit preUnit = sqd.getAllUnits().at(0);
	int unitID = sqd.getAllLivingUnitPtrs().at(0)->getID();

	levelUpSquad(sqd);

	Unit postUnit1 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(0);

	Assert::IsTrue(preUnit.getLevel() == postUnit1.getLevel() - 1);
	Assert::IsTrue(preUnit.getTraitList().size() == postUnit1.getTraitList().size() - 1);

	levelUpSquad(sqd);

	Unit postUnit2 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(0);

	Assert::IsTrue(preUnit.getLevel() == postUnit2.getLevel() - 2);
	Assert::IsTrue(preUnit.getTraitList().size() == postUnit2.getTraitList().size() - 2);
}

void BattleFieldTests::BattleFieldTests::LevelUpTest_multipleUnits()
{
	initiateBattleManager();
	Squad sqd = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0);
	Unit preUnit0 = sqd.getAllUnits().at(0);
	Unit preUnit1 = sqd.getAllUnits().at(1);
	Unit preUnit2 = sqd.getAllUnits().at(2);
	Unit preUnit3 = sqd.getAllUnits().at(3);
	Unit preUnit4 = sqd.getAllUnits().at(4);
	Unit preUnit5 = sqd.getAllUnits().at(5);

	levelUpSquad(sqd);

	Unit postUnit0 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(0);
	Unit postUnit1 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(1);
	Unit postUnit2 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(2);
	Unit postUnit3 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(3);
	Unit postUnit4 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(4);
	Unit postUnit5 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(5);

	Assert::IsTrue(preUnit0.getLevel() == postUnit0.getLevel() - 1);
	Assert::IsTrue(preUnit1.getLevel() == postUnit1.getLevel() - 1);
	Assert::IsTrue(preUnit2.getLevel() == postUnit2.getLevel() - 1);
	Assert::IsTrue(preUnit3.getLevel() == postUnit3.getLevel() - 1);
	Assert::IsTrue(preUnit4.getLevel() == postUnit4.getLevel() - 1);
	Assert::IsTrue(preUnit5.getLevel() == postUnit5.getLevel() - 1);

	Assert::IsTrue(preUnit0.getTraitList().size() == postUnit0.getTraitList().size() - 1);
	Assert::IsTrue(preUnit1.getTraitList().size() == postUnit1.getTraitList().size() - 1);
	Assert::IsTrue(preUnit2.getTraitList().size() == postUnit2.getTraitList().size() - 1);
	Assert::IsTrue(preUnit3.getTraitList().size() == postUnit3.getTraitList().size() - 1);
	Assert::IsTrue(preUnit4.getTraitList().size() == postUnit4.getTraitList().size() - 1);
	Assert::IsTrue(preUnit5.getTraitList().size() == postUnit5.getTraitList().size() - 1);
}
void BattleFieldTests::BattleFieldTests::LevelUpTest_multipleUnitsAndLevels()
{
	Unit a00 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Unit a01 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Unit a02 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Unit a03 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Unit a04 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Unit a05 = idCr.createUnit(strHandler.takeRandomName(), 10, 3, 4, &pMap.find(ProfessionTag::enumWizard)->second);
	Squad testSquad = idCr.createSquad(a00, &strHandler);
	testSquad.addUnit(a01, SquadPos(0, 0));
	testSquad.addUnit(a02, SquadPos(0, 1));
	testSquad.addUnit(a03, SquadPos(0, 2));
	testSquad.addUnit(a04, SquadPos(1, 0));
	testSquad.addUnit(a05, SquadPos(1, 2));

	initiateBattleManager({ testSquad });
	Squad sqd = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0);
	Unit preUnit0 = sqd.getAllUnits().at(0);
	Unit preUnit1 = sqd.getAllUnits().at(1);
	Unit preUnit2 = sqd.getAllUnits().at(2);
	Unit preUnit3 = sqd.getAllUnits().at(3);
	Unit preUnit4 = sqd.getAllUnits().at(4);
	Unit preUnit5 = sqd.getAllUnits().at(5);

	levelUpSquad(sqd);
	levelUpSquad(sqd);

	Unit postUnit0 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(0);
	Unit postUnit1 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(1);
	Unit postUnit2 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(2);
	Unit postUnit3 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(3);
	Unit postUnit4 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(4);
	Unit postUnit5 = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0).getAllUnits().at(5);

	Assert::IsTrue(preUnit0.getLevel() == postUnit0.getLevel() - 2);
	Assert::IsTrue(preUnit1.getLevel() == postUnit1.getLevel() - 2);
	Assert::IsTrue(preUnit2.getLevel() == postUnit2.getLevel() - 2);
	Assert::IsTrue(preUnit3.getLevel() == postUnit3.getLevel() - 2);
	Assert::IsTrue(preUnit4.getLevel() == postUnit4.getLevel() - 2);
	Assert::IsTrue(preUnit5.getLevel() == postUnit5.getLevel() - 2);

	Assert::IsTrue(preUnit0.getTraitList().size() == postUnit0.getTraitList().size() - 2);
	Assert::IsTrue(preUnit1.getTraitList().size() == postUnit1.getTraitList().size() - 2);
	Assert::IsTrue(preUnit2.getTraitList().size() == postUnit2.getTraitList().size() - 2);
	Assert::IsTrue(preUnit3.getTraitList().size() == postUnit3.getTraitList().size() - 2);
	Assert::IsTrue(preUnit4.getTraitList().size() == postUnit4.getTraitList().size() - 2);
	Assert::IsTrue(preUnit5.getTraitList().size() == postUnit5.getTraitList().size() - 2);
}

void BattleFieldTests::BattleFieldTests::LevelUpTest_careerStageMastery()
{
	initiateBattleManager();
	Squad sqd = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0);

	levelUpSquad(sqd);
	//sqd = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0);
	//std::vector<Trait*> traits11 = sqd.getAllLivingUnitPtrs().at(0)->getTraitList();
	//Unit* unt = sqd.getAllLivingUnitPtrs().at(0);
	//std::vector<Trait*> traits12 = unt->getTraitList();
	levelUpSquad(sqd);
	levelUpSquad(sqd);
	levelUpSquad(sqd);

	sqd = bMan.getBattleField().getAllLivingFlagSquads(tagID::player).at(0);
	std::vector<Trait> traits = sqd.getAllLivingUnitPtrs().at(0)->getTraitList();

	Assert::IsTrue(traits.size() == 6);
}