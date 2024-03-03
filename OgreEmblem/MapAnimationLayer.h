#pragma once
#include "AnimationLayer.h"
#include "MapAnimation2.h"
#include "MapEvent.h"
#include "MapCursorEvent.h"
#include "MapCursorAnimation.h"
#include "SquadAnimation.h"
#include "MovementDotAnimation.h"
#include "AnimationSignal.h"
#include "BattleAnimation.h"
#include "CameraController.h"
#include "MapOverlayAnimation.h"

class InitBattleMapEvent;
class GraphicsAssets;
class MapCursorEvent;
class MovementDotsEvent;
class MovementTargetCrossEvent;
class MenuEvent;
class SquadMovedEvent;
class SetAttackTargetEvent;
class ConfirmationMenuEvent;
class BattleEvent;
class UnitKilledEvent;
class StartPlayerTurnEvent;
class StartEnemyTurnEvent;
class VictoryAchievedEvent;

class MapAnimationLayer : public AnimationLayer
{
private:
	MapAnimation2 mapAnimation;
	MapCursorAnimation cursorAnimation;
	VerticalMenuAnimation menuAnimation;
	HorizontalMenuAnimation confirmationMenuAnimation;
	SquadAnimation squadAnimation;
	MovementDotAnimation dotAnimation;
	BattleAnimation battleAnimation;
	MapOverlayAnimation mapOverlayAnimation;

	CameraController drawBucket;

	UTIL::ScreenCoord cursorOffset = UTIL::ScreenCoord(TILE_W, TILE_H);
	UTIL::ScreenCoord menuOffset = UTIL::ScreenCoord(0,0);

	bool activeDeathAnimation = false;

	void setAttackTarget(int targetID);
	void concatSignals(std::vector<AnimationSignal> newSignals);

public:
	MapAnimationLayer() {};
	MapAnimationLayer(MapAnimation2 mapAnim, int layer, sf::RenderWindow* window, GraphicsAssets* asst, StringHandler* strHandler);
	MapAnimationLayer(MapAnimation2 mapAnim, SquadAnimation squadAnim, MapCursorAnimation cursorAnim, int layer, sf::RenderWindow* window, GraphicsAssets* asst, UTIL::ScreenCoord cameraOffset, StringHandler* strHandler);

	MapAnimationLayer(const MapAnimationLayer& cpEQ);
	MapAnimationLayer& operator=(const MapAnimationLayer asEQ);
	~MapAnimationLayer() { AnimationLayer::~AnimationLayer(); };
	MapAnimationLayer* clone() override { return new MapAnimationLayer(*this); };

	void draw() override;

	void applyEvent(StructuredEvent* evnt) override;
	void applyInitBattleMapEvent(InitBattleMapEvent* evnt);
	void applyMapCursorEvent(MapCursorEvent* evnt);
	void generalMenuControl(MenuEventType type, MenuVisualData menuData, MenuAnimation* animation);
	void applyMenuEvent(MenuEvent* evnt); 
	void applyConfirmationMenuEvent(ConfirmationMenuEvent* evnt);
	void applyMovementDotsEvent(MovementDotsEvent* evnt);
	void applyMovementTargetCrossEvent(MovementTargetCrossEvent* evnt);
	void applySquadMovedEvent(SquadMovedEvent* evnt);
	void applySetAttackTargetEvent(SetAttackTargetEvent* evnt);
	void applyBattleEvent(BattleEvent* evnt);
	void applyUnitKilledEvent(UnitKilledEvent* evnt);
	void openMapAnimationLayer(bool copyBattleField);
	void openLevelUpScreenLayer();
	void applyStartPlayerTurnEvent(StartPlayerTurnEvent* evnt);
	void applyStartEnemyTurnEvent(StartEnemyTurnEvent* evnt);
	void applyVictoryAchievedEvent(VictoryAchievedEvent* evnt);
};