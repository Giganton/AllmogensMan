#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "SquadRepresentation.h"
#include "SpriteAnimator.h"
#include "GraphicsUtils.h"

class CameraController;

class DeathAnimation
{
private:
	std::map < ProfessionTag, sf::Texture>* unitTextureMap = nullptr;
	CameraController* drawBucket = nullptr;
	SpriteAnimator spriteAnim;
	float fadeTime = 0.5;

	std::vector<std::pair<UnitRepresentation, float>> deadUnits;

	sf::Clock animationClock;
	void update();
public:
	DeathAnimation() {};
	DeathAnimation(std::map < ProfessionTag, sf::Texture>* txtMap, CameraController* dBucket);

	void addDeath(UnitRepresentation deadUnit);
	bool ongoingAnimation();
	void setBucket(CameraController* dBucket) { drawBucket = dBucket; };
	void draw();
};
