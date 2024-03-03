#include "GameMaster.h"
#include "BattleStage.h"
#include "Flag.h"
#include "StringHandler.h"
#include "TraitList.h"
#include "allActions.h"
#include "DraftScreenState.h"
#include "TraitTag.h"
#include "AllJobs.h"

GameMaster::GameMaster()
{
	//goToState(State::mapBrowse, true);
}

GameMaster::GameMaster(IdCreator idC, std::map<ProfessionTag, Profession > pMap, std::map<std::string, TerrainTypes> terrainMap, StringHandler* strHand, ChapterCollection chapColl, bool debugging)
{
	stringHandler = strHand;
	idCreator = idC;
	profMap = pMap;
	debugMode = debugging;
	chapterCollection = chapColl;
	currentChapter = chapColl.getAllChapters().at(0);

	rootLink = RootLink(&rootControls);

	initPlayer();

	battleManager = BattleManager(&idCreator, strHand);
	camp = Camp(&player, &idCreator);

	openCampScreen();

	//gameState = State::camp;
}

//DSFREWQCVBNMKLOPÖÄPÅIOUYTREWQXXEWERXEWOMIIIIXSDZZZZZZZZZZZZZZZZZZAZZZDASSSSSSSJNKUJNUKY,UUJLNÖOÄNUE121234567890DFXERWFSDWXDSXEDSZZZZZFDEFWFDXSERWXSFDFSEWSEWXSERDERWFTEWRDSFDSFSDEWQDSEERWQDSRDW
//DDDFASAXFWSEFZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZDSDC12345678901234567845678890JKMUKMRNFJEGRRRRRRUHY4TF7KT7F3Y7H4FHTIKNFUIUYJURETGHVFHDUREJJDFNHCHCNHDSHFHNCJNNNNNHXDNRZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
//DWFXDFSRXSEFADSEWSSKNJDFHHHHHH,BVBCBHCSXZZXCVBBBNNNMMM,,,,,....---------------------------------------ESWFDQF4T5324ST5D43F52REXSQR4ES3WAQESEQEDAWQWQWSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSAAAAAAANHJHHFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
//HUJYRU12345678901234567890123456789012345678901234567890123455678901234567890123445678901234567890123457678901223456788901234567890123345687890123456789012345678901234567890122345678901234566666666666667890
//12345678901234567890123578901567890123457789012345567890123455678901223456789012345678904567890110123456789012345611121314123456789012344567890111234567890122345678901 2 3 4 5 6 7 9 8 O 
//HUWRWIEEEEEEEEEEEEE88W9JE897521 2 3 44444 5 6 U7 78 89 0 YUFIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIYURYGITKHIOMWA9AM89E89EJGJGEZNEUIUIFTJTRKUEIGFJDKFUTRIFDJKRDITRKIUTRJVI676767RR555555555555555555555555555ÅEOMIIII98Ö58Ö


GameMaster::GameMaster(const GameMaster& cp)
{
	profMap = cp.profMap;

	chapterCollection = cp.chapterCollection;
	currentChapter = cp.currentChapter;
	debugMode = cp.debugMode;

	idCreator = cp.idCreator;
	player = cp.player;

	battleManager = cp.battleManager;
	camp = cp.camp;
	rootLink = cp.rootLink;
	stringHandler = cp.stringHandler;

	rootLink.updateManagerPointers(&camp, &battleManager);
}

GameMaster& GameMaster::operator=(const GameMaster as)
{
	profMap = as.profMap;

	chapterCollection = as.chapterCollection;
	currentChapter = as.currentChapter;
	debugMode = as.debugMode;

	idCreator = as.idCreator;
	player = as.player;

	battleManager = as.battleManager;
	camp = as.camp;
	rootLink = as.rootLink;
	stringHandler = as.stringHandler;

	rootLink.updateManagerPointers(&camp, &battleManager);

	return *this;
}

void GameMaster::handleRootControls()
{
	if (rootControls.openCampScreen)
	{
		openCampScreen();
	}
	else if (rootControls.startNextBattle)
	{
		initBattle();
		startBattle();
	}

	rootControls.reset();
}

std::vector<Unit> GameMaster::generateShopUnits()
{
	std::vector<Unit> retval;
	unsigned int i;
	srand(time(0));
	for (i = 0; i < 6; i++)
	{
		unsigned int rn = rand() % 2;
		Unit a10 = idCreator.createUnit(stringHandler->takeRandomName(), 12, 5, 1, &profMap.find(ProfessionTag::enumWarrior)->second);
		Unit a00 = idCreator.createUnit(stringHandler->takeRandomName(), 10, 3, 4, &profMap.find(ProfessionTag::enumWizard)->second);
		Unit a01 = idCreator.createUnit(stringHandler->takeRandomName(), 15, 4, 2, &profMap.find(ProfessionTag::enumWizard)->second);
		switch (rn)
		{
		case 0:
			retval.push_back(a10);
			break;
		case 1:
			retval.push_back(a00);
			break;
		default:
			throw new std::exception();
		}
	}
	return retval;
}


void GameMaster::run()
{
	if (battleManager.isActive())
	{
		if (battleManager.isBattleWon())
		{
			currentChapter.battleWon();
			battleManager.deActivateBattle();

			rootLink.closeAllFollowers();
			openCampScreen();
		}
	}
	rootLink.closingRound();

	handleRootControls();
}

void GameMaster::takeInput(sf::Event keyPress)
{
	rootLink.receiveInput(keyPress);

	if (openMapBucket)
	{
		openMapBucket = false;
		initBattle();
		startBattle();
	}
	if (openCampBucket)
	{
		openCampBucket = false;
		openCampScreen();
	}
}

void GameMaster::initBattle()
{
	battleManager.initiateBattlefield(&player, currentChapter.getNextBattle());
}

void GameMaster::startBattle()
{
	openCampBucket = false;
	rootLink.openLink(new MapBrowser(1, &battleManager, &openCampBucket, debugMode));
}

void GameMaster::openCampScreen()
{
	//openMapBucket = false;
	//rootLink.openLink(new CampMenuState(1, &camp, &openMapBucket));
	rootLink.openLink(new DraftScreenState(1, &player, generateShopUnits(), &idCreator, stringHandler));
}

void GameMaster::createVisualStack(GraphicsInterface* graphInt)
{
	rootLink.compileVisualStack(graphInt);
}

MasterState::MasterState(State st)
{
	state = st;

	switch (st)
	{
	case State::mapBrowse:
		mapIsActive = true;
		menuIsActive = false;
		break;
	default:
		throw new std::exception();
	}
}

void GameMaster::initPlayer()
{
	Unit a00 = idCreator.createUnit(stringHandler->takeRandomName(), 10, 3, 4, &profMap.find(ProfessionTag::enumWizard)->second);
	PlusAttack trait = PlusAttack();
	//a00.addTraitRandomly(&trait);
	Unit a01 = idCreator.createUnit(stringHandler->takeRandomName(), 15, 4, 2, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit a02 = idCreator.createUnit(stringHandler->takeRandomName(), 13, 4, 3, &profMap.find(ProfessionTag::enumWizard)->second);
	//Unit a03 = idCreator.createUnit("a03", 12, 3, 2, &profMap.find(ProfessionID::Knekt)->second, &actionVec.at(0));
	Unit a10 = idCreator.createUnit(stringHandler->takeRandomName(), 12, 5, 1, &profMap.find(ProfessionTag::enumWarrior)->second);
	Unit leader1 = idCreator.createUnit(stringHandler->takeRandomName(), 8, 4, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit a12 = idCreator.createUnit(stringHandler->takeRandomName(), 10, 3, 1, &profMap.find(ProfessionTag::enumWarrior)->second);
	//Unit a13 = idCreator.createUnit("a13", 12, 4, 1, &profMap.find(ProfessionID::Knekt)->second, &actionVec.at(0));

	Unit aa00 = idCreator.createUnit(stringHandler->takeRandomName(), 12, 4, 3, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit aa01 = idCreator.createUnit(stringHandler->takeRandomName(), 20, 4, 2, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit aa02 = idCreator.createUnit(stringHandler->takeRandomName(), 13, 3, 3, &profMap.find(ProfessionTag::enumWizard)->second);
	//Unit aa03 = idCreator.createUnit("aa03", 12, 3, 3, &profMap.find(ProfessionID::Knekt)->second, &actionVec.at(0));
	Unit aa10 = idCreator.createUnit(stringHandler->takeRandomName(), 11, 5, 1, &profMap.find(ProfessionTag::enumWarrior)->second);
	Unit leader2 = idCreator.createUnit(stringHandler->takeRandomName(), 10, 4, 2, &profMap.find(ProfessionTag::enumHero)->second);
	leader2.addReAction(new Riposte());
	Unit aa12 = idCreator.createUnit(stringHandler->takeRandomName(), 7, 3, 3, &profMap.find(ProfessionTag::enumWarrior)->second);
	
	//Unit aa13 = idCreator.createUnit("aa13", 12, 5, 1, &profMap.find(ProfessionID::Knekt)->second, &actionVec.at(0));

	Unit aaa00 = idCreator.createUnit(stringHandler->takeRandomName(), 12, 4, 3, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit aaa01 = idCreator.createUnit(stringHandler->takeRandomName(), 99, 4, 2, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit aaa02 = idCreator.createUnit(stringHandler->takeRandomName(), 13, 3, 3, &profMap.find(ProfessionTag::enumWizard)->second);
	//Unit aaa03 = idCreator.createUnit("aaa03", 12, 3, 3, &profMap.find(ProfessionID::Knekt)->second, &actionVec.at(0));
	Unit aaa10 = idCreator.createUnit(stringHandler->takeRandomName(), 11, 5, 1, &profMap.find(ProfessionTag::enumWarrior)->second);
	Unit aaa11 = idCreator.createUnit(stringHandler->takeRandomName(), 10, 4, 2, &profMap.find(ProfessionTag::enumWarrior)->second);
	Unit aaa12 = idCreator.createUnit("GubbensKompis", 1, 10, 0, &profMap.find(ProfessionTag::enumWarrior)->second);

	Career car1 = Career(new DummyJob, 3, new DummyJob, 3, new DummyJob, 3);
	car1.addLesserTrait(Trait(TraitTag::enumInspiringHeroism));

	Unit leader3 = idCreator.createUnit("GubbenMedGrejen", 10, 4, 2, &profMap.find(ProfessionTag::enumHero)->second,car1);
	Unit leader4 = idCreator.createUnit(stringHandler->takeRandomName(), 10, 4, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit leader5 = idCreator.createUnit(stringHandler->takeRandomName(), 10, 4, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit leader6 = idCreator.createUnit(stringHandler->takeRandomName(), 10, 4, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit leader7 = idCreator.createUnit(stringHandler->takeRandomName(), 10, 4, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit leader8 = idCreator.createUnit(stringHandler->takeRandomName(), 10, 4, 2, &profMap.find(ProfessionTag::enumHero)->second);
	Unit leader9 = idCreator.createUnit(stringHandler->takeRandomName(), 10, 4, 2, &profMap.find(ProfessionTag::enumHero)->second);


	Unit s1 = idCreator.createUnit(stringHandler->takeRandomName(), 12, 4, 3, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit s2 = idCreator.createUnit(stringHandler->takeRandomName(), 99, 4, 2, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit s3 = idCreator.createUnit(stringHandler->takeRandomName(), 13, 3, 3, &profMap.find(ProfessionTag::enumWizard)->second);
	Unit s4 = idCreator.createUnit(stringHandler->takeRandomName(), 11, 5, 1, &profMap.find(ProfessionTag::enumWarrior)->second);
	Unit s5 = idCreator.createUnit(stringHandler->takeRandomName(), 10, 4, 2, &profMap.find(ProfessionTag::enumWarrior)->second);
	Unit s6 = idCreator.createUnit(stringHandler->takeRandomName(), 7, 3, 3, &profMap.find(ProfessionTag::enumWarrior)->second);
	
	//Gains trait1 = Gains();
	//PlusAttack trait2 = PlusAttack();
	//PlusDefense trait3 = PlusDefense();
	//NaturalSelection trait4 = NaturalSelection();
	//HugeStrength trait5 = HugeStrength();

	//leader3.addTraitRandomly(&trait5);
	//leader3.addTraitRandomly(&trait2);
	//aaa12.addTraitRandomly(&trait5);
	//aaa12.addTraitRandomly(&trait2);

	//aaa00.addTraitRandomly(&trait1);
	//aaa00.addTraitRandomly(&trait2);
	//aaa00.addTraitRandomly(&trait3);
	//aaa00.addTraitRandomly(&trait4);
	//aaa00.addTraitRandomly(&trait5);
	//Unit aaa13 = idCreator.createUnit("aaa13", 12, 5, 1, &profMap.find(ProfessionID::Knekt)->second, &actionVec.at(0));

	Squad attacker1 = idCreator.createSquad(leader1, stringHandler);
	Squad attacker2 = idCreator.createSquad(leader2, stringHandler);
	Squad attacker3 = idCreator.createSquad(leader3, stringHandler);
	/*Squad attacker4 = idCreator.createSquad(leader4, stringHandler);
	Squad attacker5 = idCreator.createSquad(leader5, stringHandler);
	Squad attacker6 = idCreator.createSquad(leader6, stringHandler);
	Squad attacker7 = idCreator.createSquad(leader7, stringHandler);
	Squad attacker8 = idCreator.createSquad(leader8, stringHandler);
	Squad attacker9 = idCreator.createSquad(leader9, stringHandler);*/

	//a01.addReAction(new Martyr());
	attacker1.addUnit(a00, 0, 0);
	attacker1.addUnit(a01, 0, 1);
	attacker1.addUnit(a02, 0, 2);
	//attacker1.addUnit(a03, 0, 3);
	attacker1.addUnit(a10, 1, 0);
	attacker1.addUnit(a12, 1, 2);
	//attacker1.addUnit(a13, 1, 3);

	//aa01.addTraitRandomly(new Martyr_Trait());
	attacker2.addUnit(aa00, 0, 0);
	attacker2.addUnit(aa01, 0, 1);
	attacker2.addUnit(aa02, 0, 2);
	//attacker2.addUnit(aa03, 0, 3);
	//attacker2.addUnit(aa10, 1, 0);
	//attacker2.addUnit(aa12, 1, 2);
	//attacker2.addUnit(aa13, 1, 3);

	attacker3.addUnit(aaa12, 1, 0);

	/*attacker4.addUnit(aaa00, 0, 1);
	attacker5.addUnit(aaa01, 0, 2);
	attacker6.addUnit(aaa02, 1, 2);
	attacker7.addUnit(aaa10, 0, 0);
	attacker8.addUnit(aaa11, 1, 2);
	attacker9.addUnit(aaa12, 1, 0);*/

	player = Flag(tagID::player, &idCreator);
	player.addSquad(attacker1);
	player.addSquad(attacker2);
	player.addSquad(attacker3);
	/*player.addSquad(attacker4);
	player.addSquad(attacker5);
	player.addSquad(attacker6);
	player.addSquad(attacker7);
	player.addSquad(attacker8);
	player.addSquad(attacker9);*/

	player.addUnit(s1);
	player.addUnit(s2);
	player.addUnit(s3);
	//player.addUnit(aaa03);
	player.addUnit(s4);
	player.addUnit(s5);
	player.addUnit(s6);
	//player.addUnit(aaa13);

}