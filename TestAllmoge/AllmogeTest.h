#pragma once
#include "pch.h"
#include "CppUnitTest.h"
/*#include "C:\Privat\proj\OgEm\OgreEmblem\BattleStage.h"
#include "C:\Privat\proj\OgEm\OgreEmblem\IdCreator.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\StringHandler.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\allActions.h"
#include "C:\Privat\proj\OgEm\OgreEmblem\Profession.h"
#include "C:\Privat\proj\OgEm\OgreEmblem\ProfessionID.h"
#include "C:\Privat\proj\OgEm\OgreEmblem\TraitTree.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\TraitTreeNode.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\ActionSetup.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Unit.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Browsable.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Action.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\SquadPos.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\TraitFightContainer.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Profession.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Formler.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\FightScene.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\FightPos.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Squad.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\FighterFormation.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\BattleStage.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Fight.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\FightResults.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\ReactionStage.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Strike.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Blast.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\LightningStrike.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Riposte.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Martyr.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\MainHelpers.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\BattleManager.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\GraphicalEvent.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Flag.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\TurnKeeper.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\BattleField.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\StructuredEvent.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\BattleMap.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\StartPlayerTurnEvent.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\StartEnemyTurnEvent.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Direction.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\MapTile.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\BattleMapVisualData.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\Battle.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\SquadAI.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\AnimationLayer.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\MapAnimationLayer.cpp"
#include "C:\Privat\proj\OgEm\OgreEmblem\DeathAnimation.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>*/
#include "BattleStage.h"
#include "StringHandler.h"
#include "IdCreator.h"
#include "MainHelpers.h"
#include "ActionAnimation_LightningStrike.h"
#include "BattleManager.h"
#include "Flag.h"
//#include "C:\Privat\proj\OgEm\OgreEmblem\FencingDrill.h"
//#include "C:\Privat\proj\OgEm\OgreEmblem\FencingDrill.cpp"

//Additional include $(VCInstallDir)UnitTest\include;C:\Privat\proj\OgEm\OgreEmblem\include;C:\Privat\proj\OgEm\OgreEmblem\sfml\include;%(AdditionalIncludeDirectories)
namespace FightTests
{
	TEST_CLASS(TraitTests)
	{
	public:
		BattleStage battleStage;
		std::map<ProfessionTag, Profession> profMap = createProfMap();
		StringHandler strHandler = StringHandler(Language::Svenska);
		IdCreator idCreator = IdCreator();

		TEST_METHOD(FencingDrillTest);

	};
	
}

namespace ActionTests
{
	TEST_CLASS(ActionTests)
	{
	public:
		BattleStage battleStage;

		//std::map < ProfessionTag, sf::Texture>* profTextureMap;

		std::map<ProfessionTag, Profession> profMap = createProfMap();

		StringHandler strHandler = StringHandler(Language::Svenska);
		IdCreator idCreator = IdCreator();
		TEST_METHOD(StrikeTest1);
		/*TEST_METHOD(MartyrTest1);
		TEST_METHOD(MartyrTest2);
		TEST_METHOD(MartyrTest3);
		TEST_METHOD(MartyrTest4);
		TEST_METHOD(MartyrRiposteTest);*/
		TEST_METHOD(RiposteTest1);
		TEST_METHOD(RageTest);
		TEST_METHOD(GiantStrengthTest1);
		TEST_METHOD(ShieldBearerTest);
		TEST_METHOD(IncreaseWepProfBoonTest);
		TEST_METHOD(HeavyArmorTest);
		TEST_METHOD(AttachedTest);
		TEST_METHOD(FormationTest);
		TEST_METHOD(InspiringHeroismTest);
	};
}

namespace BattleFieldTests
{
	TEST_CLASS(BattleFieldTests)
	{
	public:
		IdCreator idCr;
		StringHandler strHandler;
		BattleManager bMan;
		MapBrowser mBrows;
		bool nonsens = false;
		Flag player;
		Battle testBattle; 
		std::map<ProfessionTag, Profession> pMap;
		BattleFieldTests();

		void initiatePlayer();
		void initiateBattle();
		void initiateBattleManager();
		void initiateBattleManager(std::vector<Squad> playerSquads);
		void initiatePlayer(std::vector<Squad> playerSquads);
		void levelUpSquad(Squad sqd);

		TEST_METHOD(LevelUpTest1);
		TEST_METHOD(LevelUpTest_multipleUnits);
		TEST_METHOD(LevelUpTest_multipleUnitsAndLevels);
		TEST_METHOD(LevelUpTest_careerStageMastery);
	};
}