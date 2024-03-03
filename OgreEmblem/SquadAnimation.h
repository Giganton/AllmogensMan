#pragma once
#include<vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "SquadRepresentation.h"
#include "MovementAnimation.h"
#include "AnimationSignal.h"
#include "SpriteAnimator.h"
#include "DeathAnimation.h"
#include "SquadDrawer.h"

struct MoveData;
class SquadData;
class CameraController;

class SquadAnimation
{
private:
	std::map < ProfessionTag, sf::Texture>* squadTextureMap = nullptr;
	std::map<int, SquadRepresentation> squadSpriteMap;
	CameraController* drawBucket = nullptr;

	SquadDrawer squadDrawer;

	MovementAnimation moveAnim;
	DeathAnimation deathAnim;
	SpriteAnimator spriteAnim;
	bool moveAnimDoneToggle = false;

	UTIL::ScreenCoord squadSpriteSize = UTIL::ScreenCoord(40, 47);
	float animStepTime = 0.5f;
	int nrOfAnimSteps = 2;

	void drawMapSquad(SquadRepresentation sqd);
	//std::vector<sf::Sprite> placeUnitSprites(SquadRepresentation squadRep);
	//void checkAnimationTiming();
public:
	SquadAnimation() {};
	SquadAnimation(std::map < ProfessionTag, sf::Texture>* sqdTMap, CameraController* dBucket);
	void init(std::vector<SquadData> sqdData);
	void startMovementAnimation(MoveData mData);

	void draw();
	MovementAnimation getMovementAnimation() { return moveAnim; };
	bool isAnySquadMoving() { return moveAnim.isActive(); };
	bool isMoveAnimationDone();
	void animationEndingHandled();
	MapCoord getSquadCoord(int ID);
	bool ongoingDeathAnimation() { return deathAnim.ongoingAnimation(); };

	void setBucket(CameraController* dBucket) { drawBucket = dBucket; deathAnim.setBucket(dBucket); };
	tagID getSquadTag(int id);

	void killUnit(int squadID, int unitID);
};