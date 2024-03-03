#pragma once
#include<vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "GraphicsAssets.h"
#include "AnimationSignal.h"

enum class OverlayAnimationType { none , Victory , EnemyTurn };

class MapOverlayAnimation
{
private:
	int level = -1;
	MapOverlayPackage* mapOverlayPackage = nullptr;
	sf::RenderWindow* window = nullptr;

	OverlayAnimationType currentlyRunningAnimation = OverlayAnimationType::none;
	std::vector<OverlayAnimationType> animQueue;

	int step = -1;
	std::clock_t startTime = 0;

	bool drawRect = false;
	sf::RectangleShape overlayRectangle;
	std::vector<sf::Sprite> spriteVector;

	std::vector<AnimationSignal> waitingSignals;

	sf::Sprite produceVictorySprite();
	sf::RectangleShape produceFadeSprite();
	void progress();
	void progressVictoryAnimation();
	void addAnimation(OverlayAnimationType type);
	void startAnimation(OverlayAnimationType type);
	void animationFinished();
public:
	MapOverlayAnimation() {};
	MapOverlayAnimation(int lvl, MapOverlayPackage* overlayPackage, sf::RenderWindow* ww);

	void draw();
	std::vector<AnimationSignal> retrieveSignals();
	void playVictoryAnimation();
};