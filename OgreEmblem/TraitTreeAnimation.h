#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "TraitTree.h"
#include "GraphicsUtils.h"
#include "GraphicsAssets.h"
#include "MouseInteractionObject.h"
#include "Career.h"

class TraitTreeAnimation : public MouseInteractionObject
{
private:
	//TraitTagTree treeToDraw;
	Career careerToDraw;
	sf::Vector2f offset;
	TraitPackage* traitAssets = nullptr;

	bool showSmall = false;

	bool hitBoxInitiated = false;

	TraitTag hoveredTrait = TraitTag::enumTraitNone;

	float traitBarWidth = 8;

	void drawTree(sf::RenderWindow* window);
	void drawTriangleTree(sf::RenderWindow* window);
	void drawTraitSlot(TraitTag trait, sf::Vector2f position, sf::RenderWindow* window);

public:
	TraitTreeAnimation() {};
	TraitTreeAnimation(Career tree, sf::Vector2f offs, TraitPackage* tAssets) { careerToDraw = tree; offset = offs; traitAssets = tAssets; };

	void reInitTree(Career tree) { careerToDraw = tree; };

	void draw(sf::RenderWindow* window) override;
	void mousePosUpdate(sf::Vector2i currentMousePos) override;

	bool traitIsHovered();
	TraitTag getHoveredTrait();
};