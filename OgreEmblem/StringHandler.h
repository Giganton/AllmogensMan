#pragma once
#include<map>
#include<string>
#include<vector>

enum class Language { Svenska , Engelska };
enum class EntityType { None, Profession, Trait, Draft };
enum class EntityStringType { None, Name, Description };

enum GeneralStringID { enumLevelString = 1, enumSquadString = 2 };
enum DraftStringID { enumNewSquadName = 1, enumConfirmDoneText = 2, enumConfirmNewLeader1 = 3, enumConfirmNewLeader2 = 4 , enumConfirmLeaderButtonText = 5, enumDenyLeaderButtonText = 6 };

struct EntityPhraseCollection
{	
	std::string name = ">>||tbd||<<";
	std::string description = ">>||tbd||<<";
};

class StringHandler
{
private:
	Language chosenLanguage = Language::Svenska;
	std::vector<Language> supportedLanguages;
	std::map<Language, std::string> languagePathMap;


	std::map<int, EntityPhraseCollection> professionMapSvenska;
	std::map<int, EntityPhraseCollection> professionMapEnglish;

	std::map<int, EntityPhraseCollection> traitMapSvenska;
	std::map<int, EntityPhraseCollection> traitMapEnglish;

	std::map<int, std::string> generalMapSvenska;
	std::map<int, std::string> generalMapEnglish;

	std::map<int, std::string> draftMapSvenska;
	std::map<int, std::string> draftMapEnglish;

	std::map<int, std::string> namingDescMapSvenska;
	std::map<int, std::string> namingDescMapEnglish;

	std::map<int, std::pair<std::string, std::string>> namingSubjMapSvenska;
	std::map<int, std::string> namingSubjMapEnglish;

	std::map<int, std::string> nameMap;
	int nrOfNames = -1;
	std::vector<int> takenNames;

	void readProfessionFile();
	void readTraitFile();
	void readGeneralFile();
	void readNameFile();
	void readDraftFile();
	void readNamingWordsFile();
public:
	StringHandler() {};
	StringHandler(Language language);

	std::string getEntityPhrase(int profID, EntityType eType, EntityStringType stringType);
	std::string getGeneralPhrase(int stringID);
	std::string getDraftPhrase(int stringID);
	std::string getName(int nameID) { return nameMap.find(nameID)->second; };
	std::string getNameDescriptor(int ID);
	std::string getRandomNameDescriptor(int seed);
	std::pair<std::string, std::string> getRandomNameSubject(int seed);
	std::string takeRandomName();
	void setLanguage(Language newLanguage) { chosenLanguage = newLanguage; };
	Language getSelectedLanguage() { return chosenLanguage; };
};