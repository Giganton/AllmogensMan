#include "ChapterCollection.h"
#include "idCreator.h"
#include "Profession.h"
#include "allActions.h"

ChapterCollection::ChapterCollection(IdCreator* idManager, std::map<ProfessionTag, Profession> pMap)
{
    terrainMap.insert({ "field" , TerrainTypes::field });
    terrainMap.insert({ "none" , TerrainTypes::noTerrain });
	idCreator = idManager;
    profMap = pMap;

	initFirstChapter();
}


void ChapterCollection::initFirstChapter()
{
	Battle firstBattle = initC1B1();
    Battle secondBattle = initC1B2();
    Battle levelupBattle = initLevelupBattle();

    std::vector<Battle> bl = { firstBattle , secondBattle };
    Chapter chap(bl);

    chapterList.push_back(chap);
}

Battle ChapterCollection::initC1B1()
{
    std::vector<VictoryCondition> vc = { VictoryCondition::route };
	Battle retVal("chapters\\chapter1\\battle1.json", terrainMap, vc);
    Squad defender1 = idCreator->createSquad();
    Squad defender2 = idCreator->createSquad();
    defender1.tag(tagID::redEnemy);
    defender2.tag(tagID::redEnemy);
    Action* strike = new Strike();

    Unit b00 = idCreator->createUnit("b00", 10, 5, 1, &profMap.find(ProfessionTag::enumWizard)->second);
    Unit b01 = idCreator->createUnit("b01", 10, 5, 2, &profMap.find(ProfessionTag::enumWizard)->second);
    Unit b02 = idCreator->createUnit("b02", 10, 5, 2, &profMap.find(ProfessionTag::enumWizard)->second);

    Unit b10 = idCreator->createUnit("b10", 10, 5, 3, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit b11 = idCreator->createUnit("b11", 10, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit b12 = idCreator->createUnit("b12", 10, 5, 3, &profMap.find(ProfessionTag::enumWarrior)->second);


    Unit bb00 = idCreator->createUnit("bb00", 10, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit bb01 = idCreator->createUnit("bb01", 10, 5, 1, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit bb02 = idCreator->createUnit("bb02", 10, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);

    Unit bb10 = idCreator->createUnit("bb10", 10, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit bb11 = idCreator->createUnit("bb11", 10, 5, 1, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit bb12 = idCreator->createUnit("bb12", 10, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);


    defender1.addUnit(b00, 0, 0);
    defender1.addUnit(b01, 0, 1);
    defender1.addUnit(b02, 0, 2);

    defender1.addUnit(b10, 1, 0);
    defender1.addUnit(b11, 1, 1);
    defender1.addUnit(b12, 1, 2);

    defender2.addUnit(bb00, 0, 0);
    defender2.addUnit(bb01, 0, 1);
    defender2.addUnit(bb02, 0, 2);

    defender2.addUnit(bb10, 1, 0);
    defender2.addUnit(bb11, 1, 1);
    defender2.addUnit(bb12, 1, 2);

    retVal.addSquad(defender1, MapCoord(10, 11));
    retVal.addSquad(defender2, MapCoord(11, 11));

	return retVal;
}

Battle ChapterCollection::initC1B2()
{
    std::vector<VictoryCondition> vc = { VictoryCondition::route };
    Battle retVal("chapters\\chapter1\\battle2.json", terrainMap, vc);
    Squad defender1 = idCreator->createSquad();
    Squad defender2 = idCreator->createSquad();
    defender1.tag(tagID::redEnemy);
    defender2.tag(tagID::redEnemy);

    Action* strike = new Strike();

    Unit b00 = idCreator->createUnit("b00", 10, 5, 1, &profMap.find(ProfessionTag::enumWizard)->second);
    Unit b01 = idCreator->createUnit("b01", 10, 5, 2, &profMap.find(ProfessionTag::enumWizard)->second);
    Unit b02 = idCreator->createUnit("b02", 10, 5, 2, &profMap.find(ProfessionTag::enumWizard)->second);

    Unit b10 = idCreator->createUnit("b10", 10, 5, 3, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit b11 = idCreator->createUnit("b11", 10, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit b12 = idCreator->createUnit("b12", 10, 5, 3, &profMap.find(ProfessionTag::enumWarrior)->second);

    Unit bb00 = idCreator->createUnit("bb00", 10, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit bb01 = idCreator->createUnit("bb01", 10, 5, 1, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit bb02 = idCreator->createUnit("bb02", 10, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);

    Unit bb10 = idCreator->createUnit("bb10", 10, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit bb11 = idCreator->createUnit("bb11", 10, 5, 1, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit bb12 = idCreator->createUnit("bb12", 10, 5, 2, &profMap.find(ProfessionTag::enumWarrior)->second);


    defender1.addUnit(b00, 0, 0);
    defender1.addUnit(b01, 0, 1);
    defender1.addUnit(b02, 0, 2);

    defender1.addUnit(b10, 1, 0);
    defender1.addUnit(b11, 1, 1);
    defender1.addUnit(b12, 1, 2);

    defender2.addUnit(bb00, 0, 0);
    defender2.addUnit(bb01, 0, 1);
    defender2.addUnit(bb02, 0, 2);

    defender2.addUnit(bb10, 1, 0);
    defender2.addUnit(bb11, 1, 1);
    defender2.addUnit(bb12, 1, 2);

    retVal.addSquad(defender1, MapCoord(13, 8));
    retVal.addSquad(defender2, MapCoord(12, 8));

    return retVal;
}

Battle ChapterCollection::initLevelupBattle()
{
    std::vector<VictoryCondition> vc = { VictoryCondition::route };
    Battle retVal("chapters\\chapter1\\battle2.json", terrainMap, vc);
    Squad defender1 = idCreator->createSquad();
    Squad defender2 = idCreator->createSquad();
    defender1.tag(tagID::redEnemy);
    defender2.tag(tagID::redEnemy);

    Action* strike = new Strike();

    Unit b00 = idCreator->createUnit("b00", 1, 0, 0, &profMap.find(ProfessionTag::enumWizard)->second);
    Unit b01 = idCreator->createUnit("b01", 1, 0, 0, &profMap.find(ProfessionTag::enumWizard)->second);
    Unit b02 = idCreator->createUnit("b02", 1, 0, 0, &profMap.find(ProfessionTag::enumWizard)->second);

    Unit b10 = idCreator->createUnit("b10", 1, 0, 0, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit b11 = idCreator->createUnit("b11", 1, 0, 0, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit b12 = idCreator->createUnit("b12", 1, 0, 0, &profMap.find(ProfessionTag::enumWarrior)->second);

    Unit bb00 = idCreator->createUnit("bb00", 1, 0, 0, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit bb01 = idCreator->createUnit("bb01", 1, 0, 0, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit bb02 = idCreator->createUnit("bb02", 1, 0, 0, &profMap.find(ProfessionTag::enumWarrior)->second);

    Unit bb10 = idCreator->createUnit("bb10", 1, 0, 0, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit bb11 = idCreator->createUnit("bb11", 1, 0, 0, &profMap.find(ProfessionTag::enumWarrior)->second);
    Unit bb12 = idCreator->createUnit("bb12", 1, 0, 0, &profMap.find(ProfessionTag::enumWarrior)->second);


    defender1.addUnit(b00, 0, 0);
    defender1.addUnit(b01, 0, 1);
    defender1.addUnit(b02, 0, 2);

    defender1.addUnit(b10, 1, 0);
    defender1.addUnit(b11, 1, 1);
    defender1.addUnit(b12, 1, 2);

    defender2.addUnit(bb00, 0, 0);
    defender2.addUnit(bb01, 0, 1);
    defender2.addUnit(bb02, 0, 2);

    defender2.addUnit(bb10, 1, 0);
    defender2.addUnit(bb11, 1, 1);
    defender2.addUnit(bb12, 1, 2);

    retVal.addSquad(defender1, MapCoord(13, 8));
    retVal.addSquad(defender2, MapCoord(12, 8));

    return retVal;
}