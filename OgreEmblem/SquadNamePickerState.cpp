#include "SquadNamePickerState.h"
#include "StringHandler.h"
#include "InitSquadNamePickerEvent.h"
#include "OpenNamePickerEvent.h"
#include "NamePickerButtons.h"
#include "ChangeWordSelectionEvent.h"

SquadNamePickerState::SquadNamePickerState(std::string* nameBuckt, std::string squadLeaderName, int lvl, StringHandler* strHandler)
{
	level = lvl;
	stringHandler = strHandler;

	nameBucket = nameBuckt;
	leaderName = squadLeaderName;

	subjectGrammarType = 1;

	setupRandomWords();

	setRandomName();
	while (!isNameViable())
	{
		setRandomName();
	}

	InitSquadNamePickerEvent evnt = InitSquadNamePickerEvent(level, prefixes, descriptors, collectSubjects() , currentName);
	eventQueue.addEvent(&evnt);
	ChangeWordSelectionEvent evnt2 = ChangeWordSelectionEvent(level, selectedPrefix, selectedDescriptor, selectedSubject, currentName);
	eventQueue.addEvent(&evnt2);
	initiated = true;
}

std::vector<std::string> SquadNamePickerState::collectSubjects()
{
	std::vector<std::string> retVal;

	unsigned int i;
	for (i = 0; i < subjects.size(); i++)
	{
		std::string temp;
		if (subjectGrammarType == 1)
		{
			temp = subjects.at(i).first;
		}
		else if (subjectGrammarType == 2)
		{
			temp = subjects.at(i).second;
		}
		else
		{
			throw new std::exception();
		}
		retVal.push_back(temp);
	}
	return retVal;
}

void SquadNamePickerState::setupRandomWords()
{
	srand(time(0));

	prefixes.push_back("De");
	prefixes.push_back(leaderName + "s");
	int seed = time(0);
	descriptors.push_back(stringHandler->getRandomNameDescriptor(seed));
	descriptors.push_back(stringHandler->getRandomNameDescriptor(seed+1));
	descriptors.push_back(stringHandler->getRandomNameDescriptor(seed+2));

	subjects.push_back(stringHandler->getRandomNameSubject(seed + 3));
	subjects.push_back(stringHandler->getRandomNameSubject(seed + 4));
	subjects.push_back(stringHandler->getRandomNameSubject(seed + 5));

}

void SquadNamePickerState::setRandomName()
{
	srand(time(0));
	int prefInd = (rand() % (prefixes.size() + 1)) - 1;
	int descInd = (rand() % (descriptors.size() + 1)) - 1;
	int subjInd = (rand() % (subjects.size() + 1)) - 1;

	//selectPrefix(prefInd);
	selectedPrefix = prefInd;
	if (selectedPrefix == -1 || selectedPrefix == 0)
	{
		subjectGrammarType = 2;
	}
	else if (selectedPrefix == 1)
	{
		subjectGrammarType = 1;
	}
	selectedDescriptor = descInd;
	selectedSubject = subjInd;
	//selectDescriptor(descInd);
	//selectSubject(subjInd);

	constructName();
}

bool SquadNamePickerState::isNameViable(int prefInd, int descInd, int subjInd)
{
	if (prefInd == -1 && descInd == -1 && subjInd == -1)
	{
		return false; //tomt namn
	}
	if (prefInd != -1 && descInd == -1 && subjInd == -1)
	{
		return false; // de
	}
	if (prefInd == -1 && descInd != -1 && subjInd == -1)
	{
		return false; // gula
	}
	if (prefInd == 0 && descInd == -1 && subjInd != -1)
	{
		return false; // de vargarna
	}
	return true;
}

bool SquadNamePickerState::isNameViable()
{
	return isNameViable(selectedPrefix, selectedDescriptor, selectedSubject);
}

void SquadNamePickerState::handleKeyPress(sf::Event inputEvent)
{

}

void SquadNamePickerState::handleMouseEvent(sf::Event mouseEvent)
{
	if (mouseEvent.type == sf::Event::MouseButtonPressed)
	{
		if (mouseEvent.mouseButton.button == sf::Mouse::Left)
		{
			handleMouseClickLeft(mouseEvent);
		}
	}
}
void SquadNamePickerState::handleMouseClickLeft(sf::Event mouseEvent)
{
	if (latestSignal.getHoveredId() == NamePickerButton::Descriptor || latestSignal.getHoveredId() == NamePickerButton::Prefix || latestSignal.getHoveredId() == NamePickerButton::Subject)
	{
		handleWordClick(latestSignal);
	}
	if (latestSignal.getHoveredId() == NamePickerButton::Done)
	{
		close();
	}
}

void SquadNamePickerState::close()
{
	*nameBucket = currentName;
	closeMe = true;
}

void SquadNamePickerState::handleWordClick(MouseSignal latest)
{
	if (latestSignal.getHoveredId() == NamePickerButton::Prefix)
	{
		selectPrefix(latestSignal.getPayload().at(0));
	}
	if (latestSignal.getHoveredId() == NamePickerButton::Descriptor)
	{
		selectDescriptor(latestSignal.getPayload().at(0));
	}
	if (latestSignal.getHoveredId() == NamePickerButton::Subject)
	{
		selectSubject(latestSignal.getPayload().at(0));
	}
}

void SquadNamePickerState::selectPrefix(int i)
{
	if (selectedPrefix == i)
	{
		if (isNameViable(-1, selectedDescriptor, selectedSubject))
		{
			selectedPrefix = -1;
		}
	}
	else
	{
		if (isNameViable(i, selectedDescriptor, selectedSubject))
		{
			selectedPrefix = i;
		}
	}

	if (selectedPrefix == -1 || selectedPrefix == 0)
	{
		subjectGrammarType = 2;
	}
	else if (selectedPrefix == 1)
	{
		subjectGrammarType = 1;
	}

	constructName();

	if (initiated)
	{

		InitSquadNamePickerEvent evnt = InitSquadNamePickerEvent(level, prefixes, descriptors, collectSubjects(), currentName);
		eventQueue.addEvent(&evnt);
		ChangeWordSelectionEvent evnt2 = ChangeWordSelectionEvent(level, selectedPrefix, selectedDescriptor, selectedSubject, currentName);
		eventQueue.addEvent(&evnt2);
	}
}


void SquadNamePickerState::selectDescriptor(int i)
{
	if (selectedDescriptor == i)
	{
		if (isNameViable(selectedPrefix, -1, selectedSubject))
		{
			selectedDescriptor = -1;
		}
	}
	else
	{
		if (isNameViable(selectedPrefix, i, selectedSubject))
		{
			selectedDescriptor = i;
		}
	}

	constructName();
	if (initiated)
	{
		ChangeWordSelectionEvent evnt = ChangeWordSelectionEvent(level, selectedPrefix, selectedDescriptor, selectedSubject, currentName);
		eventQueue.addEvent(&evnt);
	}
}


void SquadNamePickerState::selectSubject(int i)
{
	if (selectedSubject == i)
	{
		if (isNameViable(selectedPrefix, selectedDescriptor, -1))
		{
			selectedSubject = -1;
		}
	}
	else
	{
		if (isNameViable(selectedPrefix, selectedDescriptor, i))
		{
			selectedSubject = i;
		}
	}

	constructName();

	if (initiated)
	{
		ChangeWordSelectionEvent evnt = ChangeWordSelectionEvent(level, selectedPrefix, selectedDescriptor, selectedSubject, currentName);
		eventQueue.addEvent(&evnt);
	}
}


StructuredEvent* SquadNamePickerState::getOpeningEvent()
{
	return new OpenNamePickerEvent(level - 1);
}


void SquadNamePickerState::constructName()
{
	std::string tempString = "";
	bool addSpace = false;
	if (selectedPrefix != -1)
	{
		tempString = tempString + prefixes.at(selectedPrefix);
		addSpace = true;
	}
	if (selectedDescriptor != -1)
	{
		if (addSpace)
		{
			tempString = tempString + " ";
		}
		tempString = tempString + descriptors.at(selectedDescriptor);
		addSpace = true;
	}
	if (selectedSubject != -1)
	{
		if (addSpace)
		{
			tempString = tempString + " ";
		}
		tempString = tempString + collectSubjects().at(selectedSubject);
	}

	currentName = tempString;
}