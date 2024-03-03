#pragma once
#include "AnimationLayer.h"
#include "DialogueButton.h"
#include "DialogueWindow.h"

class WordButton : public DialogueButton
{
private:

public:
	WordButton() {};
	WordButton(std::string bttonText, sf::Vector2f pos, GraphicsAssets* assets);

	void draw(sf::RenderWindow* window) override;
};

class SquadNamePickerLayer : public AnimationLayer
{
private:
	TextDrawer textDrawer;

	std::vector<WordButton> prefixes;
	std::vector<WordButton> descriptor;
	std::vector<WordButton> subject;

	DialogueButton doneButton;

	std::string currentString;

	sf::Vector2f windowSize;
	sf::Vector2f windowPos;

	sf::Vector2f columnOffset;
	sf::Vector2f rowOffset;

	DialogueWindow windowBox;

	void applyMousePos(sf::Vector2i mousePos) override;
	void deselectAllWords();
public:
	SquadNamePickerLayer() {};
	SquadNamePickerLayer(int lyer, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler);

	SquadNamePickerLayer(const SquadNamePickerLayer& cpEQ);
	SquadNamePickerLayer& operator=(const SquadNamePickerLayer asEQ);
	~SquadNamePickerLayer() { AnimationLayer::~AnimationLayer(); };

	SquadNamePickerLayer* clone() override { return new SquadNamePickerLayer(*this); };

	void init(std::vector<std::string> prefWords, std::vector<std::string> descWords, std::vector<std::string> subjWords, std::string startString);

	void draw() override;
	void applyEvent(StructuredEvent* evnt) override;

	void updateSelection(int pi, int di, int si, std::string newName);
};