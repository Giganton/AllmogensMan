#include "UnitListButton.h"
#include "StringHandler.h"

UnitListButton::UnitListButton(UnitData unit, sf::Vector2f pos, GraphicsAssets* assets, StringHandler* strHand)
{
	unitData = unit;
	position = pos;
	stringHandler = strHand;

	setInteractionBoxPos(pos);
	setInteractionBoxSize(vBoxSize);

	textDrawer = TextDrawer(assets);

	visualBox = sf::RectangleShape(vBoxSize);
	visualBox.setPosition(pos);
	visualBox.setFillColor(sf::Color::Green);

	portrait.setTexture(*assets->unitPackage.getProfessionPortrait(unitData.profession));
	portrait.setPosition(pos + sf::Vector2f(10, 10));

	std::string profName = stringHandler->getEntityPhrase(unitData.profession, EntityType::Profession, EntityStringType::Name);
	std::string levelNumber = std::to_string(unitData.level);
	descriptionText = profName + ", " + stringHandler->getGeneralPhrase(GeneralStringID::enumLevelString) + " " + levelNumber;
}

/*UnitListButton::UnitListButton(const UnitListButton& cpEQ)
{
	textDrawer = cpEQ.textDrawer;
	stringHandler = cpEQ.stringHandler;

	unitData = cpEQ.unitData;

	position = cpEQ.position;
	visualBox = cpEQ.visualBox;
	vBoxSize = cpEQ.vBoxSize;

	unitName = cpEQ.unitName;
	unitDescription = cpEQ.unitDescription;

	portrait= cpEQ.portrait;

	descriptionText = cpEQ.descriptionText;

	unitNamePos = cpEQ.unitNamePos;
}

UnitListButton& UnitListButton::operator=(const UnitListButton cpEQ)
{
	textDrawer = cpEQ.textDrawer;
	stringHandler = cpEQ.stringHandler;

	unitData = cpEQ.unitData;

	position = cpEQ.position;
	visualBox = cpEQ.visualBox;
	vBoxSize = cpEQ.vBoxSize;

	unitName = cpEQ.unitName;
	unitDescription = cpEQ.unitDescription;

	portrait = cpEQ.portrait;

	descriptionText = cpEQ.descriptionText;

	unitNamePos = cpEQ.unitNamePos;

	return *this;
}*/

void UnitListButton::setup()
{

}

void UnitListButton::draw(sf::RenderWindow* window)
{
	window->draw(visualBox);
	std::string unitName = unitData.name;

	textDrawer.setSize(24);
	textDrawer.setColor(sf::Color::Black);
	textDrawer.setNameFont();
	sf::Text nameText = textDrawer.drawText(unitName, position + sf::Vector2f(100, 10), 500);

	textDrawer.setSize(18);
	textDrawer.setStandardFont();
	sf::Text descText = textDrawer.drawText(descriptionText, position + sf::Vector2f(100, 32), 500);
	unsigned int i;
	// signe
	window->draw(nameText);
	window->draw(descText);

	window->draw(portrait);
}

void UnitListButton::mousePosUpdate(sf::Vector2i currentMousePos)
{

}