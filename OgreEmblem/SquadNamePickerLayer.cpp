#include "SquadNamePickerLayer.h"
#include "NamePickerButtons.h"

SquadNamePickerLayer::SquadNamePickerLayer(int lyer, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler) : AnimationLayer(lyer, ww, assts, strHandler)
{
	drawable = true;

	windowSize = sf::Vector2f(900, 300);
	windowPos = sf::Vector2f(ww->getSize().x / 2 - windowSize.x / 2, 720);

	windowBox = DialogueWindow(windowSize, windowPos);

	doneButton = DialogueButton("Klar", windowPos + windowSize - sf::Vector2f(200, windowSize.y / 2 + DialogueButton().getSize().y/2 + 25), assts);
	textDrawer = TextDrawer(assts);
	textDrawer.setNameFont();
	textDrawer.setSize(48);
}

SquadNamePickerLayer::SquadNamePickerLayer(const SquadNamePickerLayer& cpEQ)
{
	middleMan = cpEQ.middleMan;
	if (middleMan)
	{
		nextLevel = cpEQ.nextLevel->clone();
	}

	window = cpEQ.window;
	stringHandler = cpEQ.stringHandler;
	layer = cpEQ.layer;
	signals = cpEQ.signals;

	drawable = cpEQ.drawable;
	seeThrough = cpEQ.seeThrough;

	prefixes = cpEQ.prefixes;
	descriptor = cpEQ.descriptor;
	subject = cpEQ.subject;

	windowBox = cpEQ.windowBox;
	textDrawer = cpEQ.textDrawer;
}

SquadNamePickerLayer& SquadNamePickerLayer::operator=(const SquadNamePickerLayer cpEQ)
{
	middleMan = cpEQ.middleMan;
	if (middleMan)
	{
		nextLevel = cpEQ.nextLevel->clone();
	}

	window = cpEQ.window;
	stringHandler = cpEQ.stringHandler;
	layer = cpEQ.layer;
	signals = cpEQ.signals;

	drawable = cpEQ.drawable;
	seeThrough = cpEQ.seeThrough;

	prefixes = cpEQ.prefixes;
	descriptor = cpEQ.descriptor;
	subject = cpEQ.subject;

	windowBox = cpEQ.windowBox;
	textDrawer = cpEQ.textDrawer;

	return *this;
}

WordButton::WordButton(std::string bttonText, sf::Vector2f pos, GraphicsAssets* assets) : DialogueButton(bttonText, pos, assets)
{
	buttonSize = sf::Vector2f(110, 40);
	textOffset = sf::Vector2f(buttonSize.x / 2, buttonSize.y / 2 - textDrawer.getSize() / 2 + 3);

	setInteractionBoxPos(position);
	setInteractionBoxSize(buttonSize);
}

void WordButton::draw(sf::RenderWindow* window)
{
	if (hovered || selected)
	{
		sf::RectangleShape box = sf::RectangleShape(buttonSize);

		box.setFillColor(sf::Color::Green);
		box.setPosition(position);

		window->draw(box);

		window->draw(textDrawer.drawText(buttonText, position + textOffset, 500, true));
	}
	else
	{
		DialogueButton::draw(window);
	}
}

void SquadNamePickerLayer::init(std::vector<std::string> prefWords, std::vector<std::string> descWords, std::vector<std::string> subjWords, std::string startString)
{
	unsigned int i;
	sf::Vector2f buttonOffset = windowPos + sf::Vector2f(100, 90);
	prefixes.clear();
	descriptor.clear();
	subject.clear();

	for (i = 0; i < prefWords.size(); i++)
	{
		sf::Vector2f pos = buttonOffset + sf::Vector2f(0, i * 50);
		prefixes.push_back(WordButton(prefWords.at(i), pos, assets));
	}
	for (i = 0; i < descWords.size(); i++)
	{
		sf::Vector2f pos = buttonOffset + sf::Vector2f(200, i * 50);
		descriptor.push_back(WordButton(descWords.at(i), pos, assets));
	}
	for (i = 0; i < subjWords.size(); i++)
	{
		sf::Vector2f pos = buttonOffset + sf::Vector2f(400, i * 50);
		subject.push_back(WordButton(subjWords.at(i), pos, assets));
	}

	currentString = startString;
}

void SquadNamePickerLayer::draw()
{
	windowBox.draw(window);

	unsigned int i;
	for (i = 0; i < prefixes.size(); i++)
	{
		prefixes.at(i).draw(window);
	}
	for (i = 0; i < descriptor.size(); i++)
	{
		descriptor.at(i).draw(window);
	}
	for (i = 0; i < subject.size(); i++)
	{
		subject.at(i).draw(window);
	}

	doneButton.draw(window);

	sf::Vector2f textPos = sf::Vector2f(windowBox.getPos().x + windowBox.getSize().x / 2, windowBox.getPos().y + 12);
	window->draw(textDrawer.drawText(currentString, textPos, 1000, true, false));
}

void SquadNamePickerLayer::applyEvent(StructuredEvent* evnt)
{
	evnt->applyToSquadNamePickerLayer(this);
}

void SquadNamePickerLayer::applyMousePos(sf::Vector2i mousePos)
{
	unsigned int i;
	bool hitSomething = false;

	for (i = 0; i < prefixes.size(); i++)
	{
		prefixes.at(i).mousePosUpdate(mousePos);
		if (prefixes.at(i).isHovered())
		{
			MouseSignal signal = MouseSignal(layer, NamePickerButton::Prefix);
			signal.addPayload(i);
			mouseSignals.push_back(signal);
			hitSomething = true;
		}
	}
	for (i = 0; i < descriptor.size(); i++)
	{
		descriptor.at(i).mousePosUpdate(mousePos);
		if (descriptor.at(i).isHovered())
		{
			MouseSignal signal = MouseSignal(layer, NamePickerButton::Descriptor);
			signal.addPayload(i);
			mouseSignals.push_back(signal);
			hitSomething = true;
		}
	}
	for (i = 0; i < subject.size(); i++)
	{
		subject.at(i).mousePosUpdate(mousePos);
		if (subject.at(i).isHovered())
		{
			MouseSignal signal = MouseSignal(layer, NamePickerButton::Subject);
			signal.addPayload(i);
			mouseSignals.push_back(signal);
			hitSomething = true;
		}
	}

	doneButton.mousePosUpdate(mousePos);
	if (doneButton.isHovered())
	{
		MouseSignal signal = MouseSignal(layer, NamePickerButton::Done);
		mouseSignals.push_back(signal);
		hitSomething = true;
	}

	if (!hitSomething)
	{
		MouseSignal signal = MouseSignal(layer, NamePickerButton::None);
		mouseSignals.push_back(signal);
	}
}

void SquadNamePickerLayer::deselectAllWords()
{
	unsigned int i;
	for (i = 0; i < prefixes.size(); i++)
	{
		prefixes.at(i).unSelect();
	}
	for (i = 0; i < descriptor.size(); i++)
	{
		descriptor.at(i).unSelect();
	}
	for (i = 0; i < subject.size(); i++)
	{
		subject.at(i).unSelect();
	}
}

void SquadNamePickerLayer::updateSelection(int pi, int di, int si, std::string newName)
{
	deselectAllWords();

	if (pi != -1)
	{
		prefixes.at(pi).select();
	}
	if (di != -1)
	{
		descriptor.at(di).select();
	}
	if (si != -1)
	{
		subject.at(si).select();
	}

	currentString = newName;
}