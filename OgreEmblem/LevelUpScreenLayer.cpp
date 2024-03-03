#include "LevelUpScreenLayer.h"
#include "InitLevelUpScreenEvent.h"
#include "GraphicsAssets.h"
#include "LevelUpScreenInputEvent.h"
#include "NextLevelupEvent.h"
#include "SquadPos.h"

LevelUpScreenLayer::LevelUpScreenLayer(int lr, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler) : AnimationLayer(lr, ww, assts, strHandler)
{
	int fontSize = 30;
	windowSize = sf::Vector2f(680, 350);
	windowOffset = sf::Vector2f(ww->getSize().x / 2 - windowSize.x / 2, ww->getSize().y / 2 - windowSize.y / 2);

	unitNamePos = windowOffset + sf::Vector2f(450, 50);
	traitAIconPos = windowOffset + sf::Vector2f(405, 150);
	traitBIconPos = windowOffset + sf::Vector2f(555, 150);
	traitTreePos = windowOffset + sf::Vector2f(50, 50);

	unitName.setFont(assts->horizontalMapMenuPackage.font);
	unitName.setCharacterSize(30);
	unitName.setFillColor(sf::Color::Black);

	traitAName.setFont(assts->horizontalMapMenuPackage.font);
	traitAName.setCharacterSize(16);
	traitAName.setFillColor(sf::Color::Black);

	traitBName.setFont(assts->horizontalMapMenuPackage.font);
	traitBName.setCharacterSize(16);
	traitBName.setFillColor(sf::Color::Black);
	
	traitDescriptionPos = traitAIconPos + sf::Vector2f(-50, 100);
}

LevelUpScreenLayer::LevelUpScreenLayer(const LevelUpScreenLayer& cpEQ)
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

	currentlyLeveledUnit = cpEQ.currentlyLeveledUnit;
	currentNewLevel = cpEQ.currentNewLevel;

	unitData = cpEQ.unitData;
	traitChoice = cpEQ.traitChoice;
	newLevels = cpEQ.newLevels;

	drawable = cpEQ.drawable;
	seeThrough = cpEQ.seeThrough;

	careerAnim = cpEQ.careerAnim;

	traitDescriptionPos = cpEQ.traitDescriptionPos;
}

LevelUpScreenLayer& LevelUpScreenLayer::operator=(const LevelUpScreenLayer asEQ)
{
	middleMan = asEQ.middleMan;
	if (middleMan)
	{
		nextLevel = asEQ.nextLevel->clone();
	}
	window = asEQ.window;
	stringHandler = asEQ.stringHandler;
	layer = asEQ.layer;
	signals = asEQ.signals;

	currentlyLeveledUnit = asEQ.currentlyLeveledUnit;
	currentNewLevel = asEQ.currentNewLevel;

	unitData = asEQ.unitData;
	traitChoice = asEQ.traitChoice;
	newLevels = asEQ.newLevels;

	drawable = asEQ.drawable;
	seeThrough = asEQ.seeThrough;

	careerAnim = asEQ.careerAnim;

	traitDescriptionPos = asEQ.traitDescriptionPos;

	return *this;
}

void LevelUpScreenLayer::setupUnitText()
{
	std::string test = currentlyLeveledUnit.name;
	unitName.setString(converter.from_bytes(test));
	unitName.setPosition(unitNamePos);

	int nameFontSize = 30;
	unitName.setFont(assets->horizontalMapMenuPackage.font);
	unitName.setCharacterSize(nameFontSize);
	unitName.setFillColor(sf::Color::Black);

	std::string profName = stringHandler->getEntityPhrase(unitData.at(0).profession, EntityType::Profession, EntityStringType::Name);
	std::string levelNumber = std::to_string(currentNewLevel);
	std::string fullDesc = profName + ", " + stringHandler->getGeneralPhrase(GeneralStringID::enumLevelString) + " " + levelNumber;
	unitDescription.setString(converter.from_bytes(fullDesc));
	sf::Vector2f unitDescNameOffset = sf::Vector2f(-16 , nameFontSize + 4);

	unitDescription.setPosition(unitNamePos + unitDescNameOffset);
	int descFontSize = 20;
	unitDescription.setFont(assets->horizontalMapMenuPackage.font);
	unitDescription.setCharacterSize(descFontSize);
	unitDescription.setFillColor(sf::Color::Black);
}

void LevelUpScreenLayer::setGraphicalEntities()
{
	setupUnitText();
	traitADescription.setString(converter.from_bytes(stringHandler->getEntityPhrase(traitChoice.first, EntityType::Trait, EntityStringType::Description)));
	traitBDescription.setString(converter.from_bytes(stringHandler->getEntityPhrase(traitChoice.second, EntityType::Trait, EntityStringType::Description)));

	traitADescription.setPosition(traitDescriptionPos);
	traitBDescription.setPosition(traitDescriptionPos);

	traitADescription.setFont(assets->horizontalMapMenuPackage.font);
	traitADescription.setCharacterSize(20);
	traitADescription.setFillColor(sf::Color::Black);
	traitBDescription.setFont(assets->horizontalMapMenuPackage.font);
	traitBDescription.setCharacterSize(20);
	traitBDescription.setFillColor(sf::Color::Black);

	traitAIcon.setTexture(assets->traitPackage.traitTextures.find(traitChoice.first)->second);
	traitAIcon.setPosition(traitAIconPos);
	traitBIcon.setTexture(assets->traitPackage.traitTextures.find(traitChoice.second)->second);
	traitBIcon.setPosition(traitBIconPos);

	if (traitAHighLighted)
	{
		selectedDescription = traitADescription;
	}
	else
	{
		selectedDescription = traitBDescription;
	}

	cursor.setTexture(assets->traitPackage.traitCursor);
	setCursorPosition();
}

void LevelUpScreenLayer::setCursorPosition()
{
	sf::Vector2f cursorOffset = sf::Vector2f(+25 - cursor.getTextureRect().width / 2, -6 - cursor.getTextureRect().height);
	if (traitAHighLighted)
	{
		cursor.setPosition(traitAIconPos + cursorOffset);
	}
	else
	{
		cursor.setPosition(traitBIconPos + cursorOffset);
	}
}

void LevelUpScreenLayer::applyInitLevelUpScreenEvent(InitLevelUpScreenEvent* evnt)
{
	unitData = evnt->getUnitData();
	traitChoice = evnt->getTraits();
	newLevels = evnt->getNewLevels();

	currentlyLeveledUnit = unitData.at(0);
	currentNewLevel = newLevels.at(0);

	setGraphicalEntities();

	//careerAnim = TraitTreeAnimation(unitData.at(0).career, traitTreePos, &assets->traitPackage);
	careerAnim = CareerAnimation(unitData.at(0).career, traitTreePos+sf::Vector2f(-300,-140), &assets->traitPackage);
	
	drawable = true;
}

void LevelUpScreenLayer::highlightTraitA()
{
	traitAHighLighted = true;
	setCursorPosition();
	selectedDescription = traitADescription;
}

void LevelUpScreenLayer::highlightTraitB()
{
	traitAHighLighted = false;
	setCursorPosition();
	selectedDescription = traitBDescription;
}

void LevelUpScreenLayer::applyLevelUpScreenInputEvent(LevelUpScreenInputEvent* evnt)
{
	switch (evnt->getHappening())
	{
	case LevelUpScreenEvent::MoveCursorLeft:
		highlightTraitA();
		break;
	case LevelUpScreenEvent::MoveCursorRight:
		highlightTraitB();
		break;
	case LevelUpScreenEvent::AcceptTrait:
		if (unitData.size() > 1)
		{
			unitData.erase(unitData.begin());
			newLevels.erase(newLevels.begin());

			setGraphicalEntities();
		}
		break;

	}
}

void LevelUpScreenLayer::applyNextLevelupEvent(NextLevelupEvent* evnt)
{
	currentlyLeveledUnit = evnt->getUnitData();
	traitChoice = evnt->getTraits();
	currentNewLevel = evnt->getNewLevels();
	careerAnim.reInitCareer(currentlyLeveledUnit.career);
	setGraphicalEntities();
}

void LevelUpScreenLayer::applyEvent(StructuredEvent* evnt)
{
	evnt->applyToLevelUpScreenLayer(this);
}

void LevelUpScreenLayer::draw()
{
	sf::RectangleShape hej = sf::RectangleShape(windowSize);
	hej.setFillColor(sf::Color::Green);
	hej.setPosition(windowOffset);
	window->draw(hej);

	window->draw(unitName);

	window->draw(unitDescription);

	drawTrait(traitChoice.first, traitAIconPos, window);
	drawTrait(traitChoice.second, traitBIconPos, window);

	window->draw(selectedDescription);

	window->draw(cursor);

	careerAnim.draw(window);
}

void LevelUpScreenLayer::drawTrait(TraitTag trait, sf::Vector2f position, sf::RenderWindow* window)
{
	sf::Sprite traitSprite, backgroundSprite;
	sf::Text traitName;

	backgroundSprite.setTexture(assets->traitPackage.traitBackgroundTexture);
	backgroundSprite.setPosition(position);
	traitSprite.setTexture(assets->traitPackage.traitTextures.find(trait)->second);
	traitSprite.setPosition(position);

	traitName.setString(converter.from_bytes(stringHandler->getEntityPhrase(trait, EntityType::Trait, EntityStringType::Name)));
	traitName.setFont(assets->horizontalMapMenuPackage.font);
	traitName.setCharacterSize(16);
	traitName.setFillColor(sf::Color::Black);
	float size = traitName.getLocalBounds().width;
	traitName.setPosition(sf::Vector2f(position.x - size / 2 + backgroundSprite.getTextureRect().width / 2, position.y + 60));

	window->draw(backgroundSprite);
	window->draw(traitSprite);
	window->draw(traitName);
}