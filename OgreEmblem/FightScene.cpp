#include "FightScene.h"
#include "Squad.h"

FightSlot::FightSlot(int occupyingUnitID)
{
	setOccupantID(occupyingUnitID);
}

void FightSlot::setOccupantID(int newOccupant)
{
	if (!empty || newOccupant < 0)
	{
		throw new std::exception();
	}
	empty = false;
	occupantID = newOccupant;
}

void FightSlot::removeOccupant()
{
	if (empty)
	{
		throw new std::exception();
	}
	occupantID = -1;
	empty = true;
}


int FightSlot::getOccupantID()
{
	if (empty)
	{
		throw new std::exception();
	}
	return occupantID;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

FightScene::FightScene(Squad* attackers, Squad* defenders)
{
	std::vector<FightPos> allPositions = getAllFightPositions();

	atkSquad = attackers;
	defSquad = defenders;

	unsigned int i;
	for (i = 0; i < allPositions.size(); i++)
	{
		Unit* slotOccupant = nullptr;
		bool spotIsEmpty;
		Squad* squadInQuestion = nullptr;

		if (allPositions.at(i).attackingSide)
		{
			squadInQuestion = attackers;
		}
		else
		{
			squadInQuestion = defenders;
		}

		spotIsEmpty = squadInQuestion->getTile(allPositions.at(i).squadPos)->isEmpty();
		if (spotIsEmpty)
		{
			slotMap.insert({ allPositions.at(i) , FightSlot() });
		}
		else
		{
			slotOccupant = squadInQuestion->getUnitPtr(allPositions.at(i).squadPos);
			slotMap.insert({ allPositions.at(i) , FightSlot(slotOccupant->getID()) });
		}
	}
}

bool FightScene::isPosOccupied(FightPos pos)
{
	return !slotMap.find(pos)->second.isEmpty();
}

int FightScene::getUnitID_unsafe(FightPos pos)
{
	if (isPosOccupied(pos))
	{
		return getUnitOnPos(pos)->getID();
	}
	else
	{
		return -1;
	}
}

Unit* FightScene::getUnitOnPos(FightPos pos)
{
	if (!isPosOccupied(pos))
	{
		throw new std::exception();
	}

	int id = slotMap.find(pos)->second.getOccupantID();
	if (pos.attackingSide)
	{
		return atkSquad->findUnitPtr(id);
	}
	else
	{
		return defSquad->findUnitPtr(id);
	}
}

void FightScene::moveUnit(FightPos startPos, FightPos endPos)
{
	FightSlot startSlot = slotMap.find(startPos)->second;
	FightSlot endSlot = slotMap.find(endPos)->second;

	if (startSlot.isEmpty() || !endSlot.isEmpty())
	{
		throw new std::exception();
	}
	
	slotMap.find(endPos)->second.setOccupantID(startSlot.getOccupantID());
	slotMap.find(startPos)->second.removeOccupant();
}

void FightScene::removeUnit(FightPos pos)
{
	slotMap.find(pos)->second.removeOccupant();
	//slotMap.erase(slotMap.find(pos));
}

void FightScene::addUnit(FightPos pos, int unitID)
{
	slotMap.find(pos)->second.setOccupantID(unitID);
}

void FightScene::returnFromExile(int unitID, FightPos pos)
{
	unsigned int i;
	for (i = 0; i < exiledZone.size(); i++)
	{
		if (exiledZone.at(i) == unitID)
		{
			addUnit(pos, unitID);
			exiledZone.erase(exiledZone.begin() + i);
			return;
		}
	}
	throw new std::exception();
}

void FightScene::exileUnitOnPos(FightPos exiledPos)
{
	exiledZone.push_back(slotMap.find(exiledPos)->second.getOccupantID());
	removeUnit(exiledPos);
}

bool FightScene::isUnitInExile(int id)
{
	unsigned int i;
	for (i = 0; i < exiledZone.size(); i++)
	{
		if (exiledZone.at(i) == id)
		{
			return true;
		}
	}
	return false;
}

std::vector<FightPos> FightScene::getAllLivingUnitPositions()
{
	std::vector<FightPos> retVal;
	std::map<FightPos, FightSlot>::iterator it;

	for (it = slotMap.begin(); it != slotMap.end(); it++)
	{
		if (!it->second.isEmpty() && !getUnitOnPos(it->first)->isDead())
		{
			retVal.push_back(it->first);
		}
	}

	return retVal;
}

std::vector<FightPos> FightScene::getAllLivingUnitPositions(bool atkSide)
{
	std::vector<FightPos> retVal;
	std::map<FightPos, FightSlot>::iterator it;

	for (it = slotMap.begin(); it != slotMap.end(); it++)
	{
		if (!it->second.isEmpty() && !getUnitOnPos(it->first)->isDead() && it->first.attackingSide==atkSide)
		{
			retVal.push_back(it->first);
		}
	}

	return retVal;
}

FightPos FightScene::FindUnitPosition(int id)
{
	std::map<FightPos, FightSlot>::iterator it;

	for (it = slotMap.begin(); it != slotMap.end(); it++)
	{
		if (!it->second.isEmpty() && it->second.getOccupantID() == id)
		{
			return it->first;
		}
	}
	throw new std::exception();
}

Unit* FightScene::getUnitWithID(int id)
{
	std::map<FightPos, FightSlot>::iterator it;

	for (it = slotMap.begin(); it != slotMap.end(); it++)
	{
		if (!it->second.isEmpty() && it->second.getOccupantID() == id)
		{
			return getUnitOnPos(it->first);
		}
	}
	unsigned int i;
	for (i = 0; i < exiledZone.size(); i++)
	{
		if (exiledZone.at(i) == id)
		{
			if (atkSquad->isThisUnitIn(id))
			{
				return atkSquad->findUnitPtr(id);
			}
			else if (defSquad->isThisUnitIn(id))
			{
				return defSquad->findUnitPtr(id);
			}
		}
	}
	throw new std::exception();
	return nullptr;
}

/*SIGNEDIJDIJJEWIIUREWIURUIREUNRNUREUREUIREUNREUNMFRUREUNEREUREIUREIUECUIURCIUREUIERUREUIREIURIIREUUEXO3EOE3OE3OX3XOO,KXOR,43IR3CIRIMCR4IMR4I34IMC3M3I4COICOI3C3II3I3CI3C3ICI43I43IR3IRIRIRIIEEIRIEJWIROOIEOIEIOREIORIOROIREIERIOFEIREIRIEIREIREIREIREIRIRIRIRICICMICIMRCICICRIMCRICRFICECIRIRIRIRTIUTRCIUGIUOIJJUCCJUCIURERUCMUTVVRTIUVTRIUTVRIU
MIXOWQIQEWEUOIEWMOIXEOMIEWQOIMWOMIEIOQWEIOWXEWIXW呐拍諳KIXMWNQENIQEXUIRFRUIUIEIFCEIUFIUCEIUEWIRECEANFNUCEIDENIUXADAINEDINMALSMISDNLADIXADXLIJSAIUXADXAIUSSIA
COIUEWI臥O帜UINWQLUNDXLINNXDENXIUDXNENEQDENIWQXIXIEUDNDIXWNUNXDEUXWSUDXEUXSUINDXUSNUXSDEWIRNUEIENEOWWIEIEWQIEOIEIEIOEQIOEQIMEOIEIEIOEQXIMXMIOXOIQXEIIQEXII
UIRENUREURNUEURUEUUEEUERURENURCIEWUIEXUIONEWIREWINREIUEWIU拍諴ONHUFNFWERYHURWEYWEFYUWFEUFRUEYWDUYWEYUERNYEYEYCRYBYEYREVWRYEWBWRWUNENUWRUNRNRUREEEEMMMMMMM
RIRUFIUTIUNTRCIUTNRNIVIUVTIUGRIURGIURIUVTIURTIURNV5TTNTRTNNVTIUTVTRINVRTNRVTNTNNRNVNRTVTIVTRITRIUTVRINNVTRIVUIVNIVTIUVTRUVTUTVUVTUTUNUVTRVNUVTUINRUUUNUNNN
Y2IUBXNXDNUXDWUNUXEUIEXIUXQZQSINXEQIEQIU胖腜OIUSNEDXWUEWIEUXDENUIDXNXEWUNUXEWNXNUWNWNXEUNUXHXUUU2IUWNNUWXUWUNNUXDEUEXNUEWXUXYUWYUEWUYWEUEXUNEUWNXUENEUIEUWIEW
ENUIWEUEUN EWKJ JXWJXEDJKEWJEX J FEHJRCJCRFCHJRCHJCJCRHJCEFHCEHJREHJEFHR INCURREDUEFIEIFRUR JKRECNEFIURCIURCIURE FCHJCFRUFEEUIUFRIURU REIORMIUROORURIUURNNN
IMEIRRIR R RE E IMEI E  JFEJIEIJREIJREIJREIJFRIJIF DIXUWNXWEIFNUNREYTYUNCETURUECTCT JEXFUJCDUINDCUUEUR JKD JU FEUJFEIUFEUIFEIUU EFRIUNEERUNRFURUUN ERJNIURNUINREUIE
MURMIRRIIUMREURE拍諴OXNUIDXWIFIWIRXWYC5YUITYNYRCTVRRIRIUREURIUUEEUREUIIUTIURICITCTIUTRUEERUYETCYUTEYUECTYUTEUYTRTRVYUTVRY XUFHUFFUYFUYFRYUFRYURFYURUYRFYURFYURY
胖腜OUE WEFYFWWWFYXEWFYXWEYFUWFYUXWXYFWEYFESWQAEDFR12345667890+创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创创*/