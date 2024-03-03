#include "UnitDetailsWindow.h"
#include "StringHandler.h"

UnitDetailsWindow::UnitDetailsWindow(UnitData unit, sf::Vector2f pos, GraphicsAssets* assts, StringHandler* strHand)
{
	position = pos;
	stringHandler = strHand;
	assets = assts;

	textDrawer = TextDrawer(assets);

	setUnit(unit);

	setupBoxes();
	setupUnitText(unit);
}

void UnitDetailsWindow::setUnit(UnitData unitD)
{
	showUnit = true;
	unitData = unitD;
	traitTreeAnimation = TraitTreeAnimation(unitData.career, position + infoOffset + traitTreeOffset, &assets->traitPackage);

	portrait.setTexture(*assets->unitPackage.getProfessionPortrait(unitData.profession));

	portrait.setPosition(position + infoOffset + portraitOffset);
	setupUnitText(unitD);

}

UnitDetailsWindow::UnitDetailsWindow(sf::Vector2f pos, GraphicsAssets* assts, StringHandler* strHand)
{
	//unitData = unit;
	position = pos;
	stringHandler = strHand;
	assets = assts;

	textDrawer = TextDrawer(assets);
	//traitTreeAnimation = TraitTreeAnimation(unitData.traitTree, position + infoOffset + traitTreeOffset, &assets->traitPackage);

	//portrait.setTexture(*assets->unitPackage.getProfessionPortrait(unitData.profession));

	//portrait.setPosition(position + infoOffset + portraitOffset);

	setupBoxes();
	//setupUnitText(unit);
}

void UnitDetailsWindow::setupBoxes()
{
	/*visualBox = sf::RectangleShape(vBoxSize);
	visualBox.setPosition(position);
	visualBox.setFillColor(sf::Color(0x3e, 0x57, 0x5b)); //#3e575b*/

	sf::Vector2f frameOffset = sf::Vector2f(-3, -3);

	visualQuads = sf::VertexArray(sf::Quads, 4);

	visualQuads[0].position = sf::Vector2f(position.x, position.y);
	visualQuads[1].position = sf::Vector2f(position.x + vBoxSize.x, position.y);
	visualQuads[2].position = sf::Vector2f(position.x + vBoxSize.x, position.y + vBoxSize.y);
	visualQuads[3].position = sf::Vector2f(position.x, position.y + vBoxSize.y);

	visualQuads[0].color = sf::Color(0x3e, 0x57, 0x5b);
	visualQuads[1].color = sf::Color(0x69, 0x82, 0x87);//#698287
	visualQuads[2].color = sf::Color(0x39, 0x4a, 0x54);//#1d2b2c
	visualQuads[3].color = sf::Color(0x1d, 0x2b, 0x2c);//#394a54

	sf::Vector2f framePos = position + frameOffset;
	sf::Vector2f frameSize = vBoxSize + sf::Vector2f(6, 6);

	visualFrameQuads = sf::VertexArray(sf::Quads, 4);

	visualFrameQuads[0].position = sf::Vector2f(framePos.x, framePos.y);
	visualFrameQuads[1].position = sf::Vector2f(framePos.x + frameSize.x, framePos.y);
	visualFrameQuads[2].position = sf::Vector2f(framePos.x + frameSize.x, framePos.y + frameSize.y);
	visualFrameQuads[3].position = sf::Vector2f(framePos.x, framePos.y + frameSize.y);

	visualFrameQuads[0].color = sf::Color(0x8f, 0x3e, 0x21);//#8f3e21
	visualFrameQuads[1].color = sf::Color(0xa8, 0x60, 0x38);//#a86038
	visualFrameQuads[2].color = sf::Color(0x9d, 0x49, 0x31);//#6a2d1b
	visualFrameQuads[3].color = sf::Color(0x6a, 0x2d, 0x1b);//#9d4931

	/*visualFrame = sf::RectangleShape(vBoxSize + sf::Vector2f(6, 6));
	visualFrame.setPosition(position + frameOffset);
	visualFrame.setFillColor(sf::Color(0x8f, 0x3e, 0x21)); //#a86038*/

	sf::Vector2f traitBoxSize = sf::Vector2f(470, 200);
	sf::Vector2f traitBoxOffset = sf::Vector2f(-10, -15);

	traitBox = sf::RectangleShape(traitBoxSize);
	traitBox.setPosition(position + infoOffset + traitTreeOffset + traitBoxOffset);
	traitBox.setFillColor(sf::Color(0x53, 0x63, 0x63));//#536363

	float tfw = 8;
	traitFrame = sf::RectangleShape(traitBoxSize + sf::Vector2f(tfw, tfw));
	traitFrame.setPosition(position + infoOffset + traitTreeOffset + traitBoxOffset + sf::Vector2f(-tfw/2, -tfw/2));
	traitFrame.setFillColor(sf::Color(0x39, 0x4a, 0x54));//#394a54
}

void UnitDetailsWindow::setupUnitText(UnitData unit)
{
	std::vector<sf::Text> newText;
	sf::Vector2f textOffset = sf::Vector2f(130, 0);

	unitName = unit.name;
	textDrawer.setSize(24);
	textDrawer.setColor(sf::Color(0xd2, 0xcc, 0xb6));//#d2ccb6
	newText.push_back(textDrawer.drawText(unitName, position + infoOffset + textOffset, 500));

	std::string profName = stringHandler->getEntityPhrase(unitData.profession, EntityType::Profession, EntityStringType::Name);
	std::string levelNumber = std::to_string(unitData.level);
	descriptionText = profName + ", " + stringHandler->getGeneralPhrase(GeneralStringID::enumLevelString) + " " + levelNumber;
	textDrawer.setSize(18);
	newText.push_back(textDrawer.drawText(descriptionText, position + infoOffset + textOffset + sf::Vector2f(0, 26), 500));


	std::string hpString = "HP:";
	std::string hpVal = std::to_string(unit.statistics.HP) + "/" + std::to_string(unit.statistics.maxHP);
	newText.push_back(textDrawer.drawText(hpString, position + infoOffset + textOffset + sf::Vector2f(0, 60), 500));
	newText.push_back(textDrawer.drawText(hpVal, position + infoOffset + textOffset + sf::Vector2f(90, 60), 500));

	textDrawer.setSize(18);

	std::string atkString = "Attack:";
	std::string atkVal = std::to_string(unit.statistics.attack);
	newText.push_back(textDrawer.drawText(atkString, position + infoOffset + textOffset + sf::Vector2f(0, 80), 500));
	newText.push_back(textDrawer.drawText(atkVal, position + infoOffset + textOffset + sf::Vector2f(90, 80), 500));
	std::string defString = "Defense: ";
	std::string defVal = std::to_string(unit.statistics.defense);

	newText.push_back(textDrawer.drawText(defString, position + infoOffset + textOffset + sf::Vector2f(0, 100), 500));
	newText.push_back(textDrawer.drawText(defVal, position + infoOffset + textOffset + sf::Vector2f(90, 100), 500));

	unitText = newText;
}

void UnitDetailsWindow::setupTraitText(TraitTag trait)
{
	if (!showTraitText)
	{
		showTraitText = true;

		traitDescription = stringHandler->getEntityPhrase(trait, EntityType::Trait, EntityStringType::Description);
		traitTitle = stringHandler->getEntityPhrase(trait, EntityType::Trait, EntityStringType::Name);
	}
}

void UnitDetailsWindow::passMousePos(sf::Vector2i pos)
{
	traitTreeAnimation.mousePosUpdate(pos);

	if (traitTreeAnimation.traitIsHovered())
	{
		if (traitTreeAnimation.getHoveredTrait() != TraitTag::enumTraitNone)
		{
			setupTraitText(traitTreeAnimation.getHoveredTrait());
		}
		else
		{
			showTraitText = false;
		}
	}
	else
	{
		showTraitText = false;
	}
}

void UnitDetailsWindow::draw(sf::RenderWindow* window)
{
	//window->draw(visualFrame);
	window->draw(visualFrameQuads);
	window->draw(visualQuads);
	//window->draw(visualBox);
	//window->draw(traitFrame);
	//window->draw(traitBox);

	sf::Text traitText;
	sf::Text traitTitleText;

	if (showTraitText)
	{
		textDrawer.setSize(18);
		traitTitleText = textDrawer.drawText(traitTitle, position + infoOffset + traitTreeOffset + sf::Vector2f(200, 38), 500);
		traitText = textDrawer.drawText(traitDescription, position + infoOffset + traitTreeOffset + sf::Vector2f(200, 70), 270);
	}

	unsigned int i;
	// signe
	if (showUnit)
	{
		for (i = 0; i < unitText.size(); i++)
		{
			window->draw(unitText.at(i));
		}

		window->draw(traitText);
		window->draw(traitTitleText);

		window->draw(portrait);
		traitTreeAnimation.draw(window);
	}
}