#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Privat\proj\OgEm\OgreEmblem\BattleStage.h"
#include "C:\Privat\proj\OgEm\OgreEmblem\IdCreator.h"
#include "C:\Privat\proj\OgEm\OgreEmblem\StringHandler.h"
#include "C:\Privat\proj\OgEm\OgreEmblem\allActions.h"
#include "C:\Privat\proj\OgEm\OgreEmblem\Profession.h"
#include "C:\Privat\proj\OgEm\OgreEmblem\ProfessionID.h"
#include "C:\Privat\proj\OgEm\OgreEmblem\TraitTree.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AllmogeTest
{
	TEST_CLASS(AllmogeTest)
	{
	public:
		BattleStage battleStage;

		//std::map < ProfessionTag, sf::Texture>* profTextureMap;

		std::map<ProfessionTag, Profession> profMap;

		StringHandler strHandler;
		IdCreator idCreator;

		
		Squad squad1;
		Squad squad2;
		
		TEST_METHOD(StrikeTest1)
		{
			idCreator = IdCreator();
			strHandler = StringHandler(Language::Svenska);

			Strike strikeAction = Strike();
			SquadPos pos1 = SquadPos(1, 1);
			SquadPos pos2 = SquadPos(1, 2);

			int HP = 10;
			int atk = 5;
			int def = 2;

			Unit leader1 = idCreator.createUnit(strHandler.takeRandomName(), 100, atk, 3, &profMap.find(ProfessionTag::enumHero)->second, strikeAction.clone());
			Unit leader2 = idCreator.createUnit(strHandler.takeRandomName(), HP, 50, def, &profMap.find(ProfessionTag::enumHero)->second, strikeAction.clone());

			squad1 = idCreator.createSquad(leader1, pos1, &strHandler);
			squad2 = idCreator.createSquad(leader2, pos2, &strHandler);

			battleStage = BattleStage(Terrain(TerrainTypes::field), Terrain(TerrainTypes::field), &squad1, &squad2);
			battleStage.doBattle();

			ActionResults results = battleStage.getResults().front();

			Assert::AreEqual(squad2.getUnitPtr(pos2)->getHP(), HP - (atk - def));
			Assert::AreEqual(squad1.getUnitPtr(pos1)->getHP(), leader1.getMaxHP());
		
			Assert::IsTrue(results.didActionResolve());

			Assert::AreEqual(results.getEffects().at(0).damageTaken, atk - def);
			Assert::AreEqual(results.getEffects().at(0).affectedID, leader2.getID());
		}
	};
}
