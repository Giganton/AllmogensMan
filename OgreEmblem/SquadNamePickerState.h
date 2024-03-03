#pragma once
#include "InputLink.h"
#include<string>

class StringHandler;

class SquadNamePickerState : public InputLink
{
private:
	std::string* nameBucket = nullptr;
	StringHandler* stringHandler = nullptr;
	std::string leaderName;

	std::vector<std::string> prefixes;
	std::vector<std::string> descriptors;
	std::vector<std::pair<std::string, std::string>> subjects;
	int subjectGrammarType = -1;

	int selectedPrefix = -1;
	int selectedDescriptor = -1;
	int selectedSubject = -1;

	std::string currentName;
	bool initiated = false;

	void handleKeyPress(sf::Event inputEvent) override;
	void handleMouseEvent(sf::Event mouseEvent) override;
	void handleMouseClickLeft(sf::Event mouseEvent);

	void handleWordClick(MouseSignal latestClick);

	void selectPrefix(int i);
	void selectDescriptor(int i);
	void selectSubject(int i);
	void constructName();
	void close() override;
	std::vector<std::string> collectSubjects();

	void setupRandomWords();
	void setRandomName();
	bool isNameViable();
	bool isNameViable(int prefInd, int descInd, int subjInd);
public:
	SquadNamePickerState() {};
	SquadNamePickerState(std::string* nameBuckt, std::string squadLeaderName, int lvl, StringHandler* strHandler);


	SquadNamePickerState* clone() const override { return new SquadNamePickerState(*this); };
	SquadNamePickerState* allocateNew() const override { return new SquadNamePickerState(); };

	StructuredEvent* getOpeningEvent() override;
};

