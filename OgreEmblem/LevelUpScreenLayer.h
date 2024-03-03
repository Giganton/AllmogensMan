#pragma once
#include "AnimationLayer.h"
#include "Trait.h"
#include "LevelUpData.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Unit.h"
#include "TraitTreeAnimation.h"
#include "CareerAnimation.h"

#include <locale>
#include <codecvt>
#include <string>



class InitLevelUpScreenEvent;
class LevelUpScreenInputEvent;
class NextLevelupEvent;

class LevelUpScreenLayer : public AnimationLayer
{
private:
	CareerAnimation careerAnim;

	std::vector<UnitData> unitData;
	std::vector<int> newLevels;
	UnitData currentlyLeveledUnit;
	int currentNewLevel = -1;
	std::pair<TraitTag, TraitTag> traitChoice;
	bool test = false;
	bool traitAHighLighted = true;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	sf::Vector2f windowOffset;
	sf::Vector2f windowSize;

	sf::Text unitName;
	sf::Vector2f unitNamePos;

	sf::Text unitDescription;

	sf::Text traitAName;
	sf::Text traitBName;
	sf::Text traitADescription;
	sf::Text traitBDescription;
	sf::Text selectedDescription;
	sf::Vector2f traitDescriptionPos;

	sf::Sprite cursor;
	sf::Sprite traitAIcon;
	sf::Vector2f traitAIconPos;
	sf::Sprite traitBIcon;
	sf::Vector2f traitBIconPos;

	sf::Vector2f traitTreePos;



	void draw() override;
	void drawTrait(TraitTag trait, sf::Vector2f position, sf::RenderWindow* window);
	void setGraphicalEntities();
	void setupUnitText();
	void setCursorPosition();
	void highlightTraitA();
	void highlightTraitB();
public:
	LevelUpScreenLayer() {};
	LevelUpScreenLayer(int lr, sf::RenderWindow* ww, GraphicsAssets* assts, StringHandler* strHandler);
	LevelUpScreenLayer(const LevelUpScreenLayer& cpEQ);
	LevelUpScreenLayer& operator=(const LevelUpScreenLayer asEQ);
	~LevelUpScreenLayer() { AnimationLayer::~AnimationLayer(); };
	LevelUpScreenLayer* clone() override { return new LevelUpScreenLayer(*this); };

	void applyEvent(StructuredEvent* evnt) override;
	void applyInitLevelUpScreenEvent(InitLevelUpScreenEvent* evnt);
	void applyLevelUpScreenInputEvent(LevelUpScreenInputEvent* evnt);
	void applyNextLevelupEvent(NextLevelupEvent* evnt);
};