#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Career.h"
#include "GraphicsUtils.h"
#include "GraphicsAssets.h"
#include "MouseInteractionObject.h"

class CareerAnimation : public MouseInteractionObject
{
private:
	Career careerToDraw;
	sf::Vector2f offset;
	TraitPackage* traitAssets = nullptr;

	bool initiated = false;

	sf::Vector2f jobSize = sf::Vector2f(347, 163);

	sf::Vector2f apprenticePos = sf::Vector2f(0, (JOB_HEIGHT + 38)*2);
	sf::Vector2f professionalPos = sf::Vector2f(0, JOB_HEIGHT + 38);
	sf::Vector2f masterPos = sf::Vector2f(0, 0);

	sf::Vector2f majorOffset = sf::Vector2f(30, 15);


	TraitTag hoveredTrait = TraitTag::enumTraitNone;

	void drawCareer(bool init, sf::RenderWindow* window);
	void drawCareerStage(CareerStage cStage, bool mastered, sf::Vector2f pos, bool init, sf::RenderWindow* window);
	void drawMajorTraitSlot(TraitTag trait, sf::Vector2f position, bool init, sf::RenderWindow* window);
	void drawJob(JobTag job, sf::Vector2f position, bool init, sf::RenderWindow* window);
	void drawLesserTraitSlot(TraitTag trait, sf::Vector2f position, bool init, sf::RenderWindow* window);
	void initHitBoxes(Career cr);

public:
	CareerAnimation() {};
	CareerAnimation(Career tree, sf::Vector2f offs, TraitPackage* tAssets) { careerToDraw = tree; offset = offs; traitAssets = tAssets; };

	void reInitCareer(Career cr) { careerToDraw = cr; };

	void draw(sf::RenderWindow* window) override;
	void mousePosUpdate(sf::Vector2i currentMousePos) override;

	bool traitIsHovered();
	TraitTag getHoveredTrait();
};