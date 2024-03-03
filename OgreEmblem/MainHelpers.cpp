#include "MainHelpers.h"

std::list<Profession> createProfList()
{
    Profession* knekt = new Profession(ProfessionTag::enumWarrior);
    Profession* trollkarl = new Profession(ProfessionTag::enumWizard);
    Profession* hero = new Profession(ProfessionTag::enumHero);
    std::list<Profession> retVal = { *knekt , *trollkarl , *hero };

    return retVal;

}

std::map<ProfessionTag, Profession> createProfMap()
{
    unsigned int i;
    Profession* knekt = new Profession(ProfessionTag::enumWarrior);
    Profession* trollkarl = new Profession(ProfessionTag::enumWizard);
    Profession* hero = new Profession(ProfessionTag::enumHero);

    std::list<Profession> pList = createProfList();
    std::map<ProfessionTag, Profession> retVal;

    while (pList.size() > 0)
    {
        Profession prof = pList.front();
        retVal.insert({ prof.getTag(), prof });
        pList.pop_front();
    }

    return retVal;
}

std::map<std::string, TerrainTypes> createTerrainMap()
{
    std::map<std::string, TerrainTypes> retVal;

    retVal.insert({ "field" , TerrainTypes::field });
    retVal.insert({ "none" , TerrainTypes::noTerrain });

    return retVal;
}