#include "StringHandler.h"
#include "json.hpp"
#include<fstream>
#include<ctime>

using json = nlohmann::json;

StringHandler::StringHandler(Language language)
{
	chosenLanguage = language;
	supportedLanguages = { Language::Svenska , Language::Engelska };
	languagePathMap.insert({ Language::Svenska , "svenska" });
	languagePathMap.insert({ Language::Engelska , "english" });
	readProfessionFile();
	readTraitFile();
	readGeneralFile();
	readNameFile();
	readDraftFile();
	readNamingWordsFile();
	srand(time(0));
}

void StringHandler::readProfessionFile()
{
	unsigned int i;
	for (i = 0; i < supportedLanguages.size(); i++)
	{
		std::string filePath = "languageFiles\\" + languagePathMap.find(supportedLanguages.at(i))->second + "\\professions.json";
		std::ifstream file1(filePath);
		json jSon, j2;
		file1 >> jSon;
		unsigned int j;
		for (j = 0; j < jSon["profs"].size(); j++)
		{
			j2 = jSon["profs"][j];

			std::string professionID = j2["ID"];
			json jstring = j2["ID"];
			int profID = std::stoi(professionID);
			EntityPhraseCollection profCollection = EntityPhraseCollection();
			profCollection.name = j2["name"];
			profCollection.description = j2["description"];

			switch (supportedLanguages.at(i))
			{
			case Language::Svenska:
				professionMapSvenska.insert({ profID , profCollection });
				break;
			case Language::Engelska:
				professionMapEnglish.insert({ profID , profCollection });
				break;
			}
		}
	}
}

void StringHandler::readTraitFile()
{
	unsigned int i;
	for (i = 0; i < supportedLanguages.size(); i++)
	{
		std::ifstream file1("languageFiles\\" + languagePathMap.find(supportedLanguages.at(i))->second + "\\traits.json");
		json jSon, j2;
		file1 >> jSon;
		unsigned int j;
		for (j = 0; j < jSon["traits"].size(); j++)
		{
			j2 = jSon["traits"][j];

			std::string traitID = j2["ID"];
			int profID = std::stoi(traitID);
			EntityPhraseCollection traitCollection = EntityPhraseCollection();
			traitCollection.name = j2["name"];
			traitCollection.description = j2["description"];

			switch (supportedLanguages.at(i))
			{
			case Language::Svenska:
				traitMapSvenska.insert({ profID , traitCollection });
				break;
			case Language::Engelska:
				traitMapEnglish.insert({ profID , traitCollection });
				break;
			}
		}
	}
}

void StringHandler::readDraftFile()
{
	unsigned int i;
	for (i = 0; i < supportedLanguages.size(); i++)
	{
		std::ifstream file1("languageFiles\\" + languagePathMap.find(supportedLanguages.at(i))->second + "\\draft.json");
		json jSon, j2;
		file1 >> jSon;
		unsigned int j;
		for (j = 0; j < jSon["draft"].size(); j++)
		{
			j2 = jSon["draft"][j];
			std::string traitID = j2["ID"];
			int stringID = std::stoi(traitID);

			switch (supportedLanguages.at(i))
			{
			case Language::Svenska:
				draftMapSvenska.insert({ stringID , j2["string"] });
				break;
			case Language::Engelska:
				draftMapEnglish.insert({ stringID , j2["string"] });
				break;
			}
		}
	}
}

void StringHandler::readNamingWordsFile()
{
	unsigned int i;
	for (i = 0; i < supportedLanguages.size(); i++)
	{
		std::ifstream file1("languageFiles\\" + languagePathMap.find(supportedLanguages.at(i))->second + "\\squad_name_descriptors.json");
		json jSon, j2;
		file1 >> jSon;
		unsigned int j;
		for (j = 0; j < jSon["descriptors"].size(); j++)
		{
			j2 = jSon["descriptors"][j];
			std::string traitID = j2["ID"];
			int stringID = std::stoi(traitID);

			switch (supportedLanguages.at(i))
			{
			case Language::Svenska:
				namingDescMapSvenska.insert({ stringID , j2["string"] });
				break;
			case Language::Engelska:
				namingDescMapEnglish.insert({ stringID , j2["string"] });
				break;
			}
		}
		for (j = 0; j < jSon["subjects"].size(); j++)
		{
			j2 = jSon["subjects"][j];
			std::string traitID = j2["ID"];
			int stringID = std::stoi(traitID);

			switch (supportedLanguages.at(i))
			{
			case Language::Svenska:
				namingSubjMapSvenska.insert({ stringID , std::make_pair(j2["string_1"],j2["string_2"]) });
				break;
			case Language::Engelska:
				namingSubjMapEnglish.insert({ stringID , j2["string"] });
				break;
			}
		}
	}
}

void StringHandler::readGeneralFile()
{
	unsigned int i;
	for (i = 0; i < supportedLanguages.size(); i++)
	{
		std::ifstream file1("languageFiles\\" + languagePathMap.find(supportedLanguages.at(i))->second + "\\general.json");
		json jSon, j2;
		file1 >> jSon;
		unsigned int j;
		for (j = 0; j < jSon["general"].size(); j++)
		{
			j2 = jSon["general"][j];
			std::string traitID = j2["ID"];
			int stringID = std::stoi(traitID);

			switch (supportedLanguages.at(i))
			{
			case Language::Svenska:
				generalMapSvenska.insert({ stringID , j2["string"] });
				break;
			case Language::Engelska:
				generalMapEnglish.insert({ stringID , j2["string"] });
				break;
			}
		}
	}
}

void StringHandler::readNameFile()
{
	unsigned int i;
	for (i = 0; i < supportedLanguages.size(); i++)
	{
		std::ifstream file1("languageFiles\\names.json");
		json jSon, j2;
		file1 >> jSon;
		unsigned int j;
		nrOfNames = jSon["names"].size();
		for (j = 0; j < nrOfNames; j++)
		{
			j2 = jSon["names"][j];
			std::string traitID = j2["ID"];
			int stringID = std::stoi(traitID);

			nameMap.insert({ stringID , j2["name"] });
		}
	}
}

std::string StringHandler::getEntityPhrase(int entityID, EntityType eType, EntityStringType stringType)
{ 
	EntityPhraseCollection phraseColl;
	switch (chosenLanguage)
	{
		case Language::Svenska:
			switch (eType)
			{
			case EntityType::Profession:
				phraseColl = professionMapSvenska.find(entityID)->second;
				break;
			case EntityType::Trait:
				phraseColl = traitMapSvenska.find(entityID)->second;
				break;
			case EntityType::Draft:
				phraseColl = traitMapSvenska.find(entityID)->second;
				break;
			default:
				throw new std::exception();
			}
			break;
		case Language::Engelska:
			switch (eType)
			{
			case EntityType::Profession:
				phraseColl = professionMapEnglish.find(entityID)->second;
				break;
			case EntityType::Trait:
				phraseColl = traitMapEnglish.find(entityID)->second;
				break;
			default:
				throw new std::exception();
			}
			break;
		default:
			throw new std::exception();
			phraseColl = professionMapSvenska.find(entityID)->second;
	}
	switch (stringType)
	{
	case EntityStringType::Name:
		return phraseColl.name;
	case EntityStringType::Description:
		return phraseColl.description;
	default:
		throw new std::exception();
		return "";
	}
}

std::string StringHandler::getGeneralPhrase(int stringID)
{
	switch (chosenLanguage)
	{
	case Language::Svenska:
		return generalMapSvenska.find(stringID)->second;
	case Language::Engelska:
		return generalMapEnglish.find(stringID)->second;
	default:
		throw new std::exception();
		return "";
	}
}

std::string StringHandler::getDraftPhrase(int stringID)
{
	switch (chosenLanguage)
	{
	case Language::Svenska:
		return draftMapSvenska.find(stringID)->second;
	case Language::Engelska:
		return draftMapEnglish.find(stringID)->second;
	default:
		throw new std::exception();
		return "";
	}
}

std::string StringHandler::getNameDescriptor(int stringID)
{
	switch (chosenLanguage)
	{
	case Language::Svenska:
		return namingDescMapSvenska.find(stringID)->second;
	case Language::Engelska:
		return namingDescMapEnglish.find(stringID)->second;
	default:
		throw new std::exception();
		return "";
	}
}

std::string StringHandler::getRandomNameDescriptor(int seed)
{
	srand(seed);
	int randID;
	switch (chosenLanguage)
	{
	case Language::Svenska:
		randID = (rand() % namingDescMapSvenska.size()) + 1;
		return namingDescMapSvenska.find(randID)->second;
	case Language::Engelska:
		randID = (rand() % namingDescMapEnglish.size()) + 1;
		return namingDescMapEnglish.find(randID)->second;
	default:
		throw new std::exception();
		return "";
	}
}

std::pair<std::string, std::string> StringHandler::getRandomNameSubject(int seed)
{
	srand(seed);
	int randID;
	switch (chosenLanguage)
	{
	case Language::Svenska:
		randID = (rand() % namingSubjMapSvenska.size()) + 1;
		return namingSubjMapSvenska.find(randID)->second;
	case Language::Engelska:
		randID = (rand() % namingSubjMapEnglish.size()) + 1;
		return std::make_pair(namingSubjMapEnglish.find(randID)->second, namingSubjMapEnglish.find(randID)->second);
	default:
		throw new std::exception();
		return std::make_pair("","");
	}

}

std::string StringHandler::takeRandomName()
{
	if (takenNames.size() == nrOfNames)
	{
		takenNames.clear();
	}

	std::vector<int> nonTakenNames;

	unsigned int i, j;
	for (i = 0; i < nrOfNames; i++)
	{
		nonTakenNames.push_back(i + 1);
	}
	for (i = 0; i < takenNames.size(); i++)
	{
		for (j = 0; j < nonTakenNames.size(); j++)
		{
			if (nonTakenNames.at(j) == takenNames.at(i))
			{
				nonTakenNames.erase(nonTakenNames.begin() + j);
				break;
			}
		}
	}
	int randIndex = rand() % nonTakenNames.size();
	takenNames.push_back(randIndex);

	return nameMap.find(nonTakenNames.at(randIndex))->second;
}