#include "MapAnimationLayer.h"
#include "InitBattleMapEvent.h"
#include "MapCursorEvent.h"
#include "MovementDotsEvent.h"
#include "MovementTargetCrossEvent.h"
#include "SquadMovedEvent.h"
#include "SetAttackTargetEvent.h"
#include "ConfirmationMenuEvent.h"
#include "BattleEvent.h"
#include "UnitKilledEvent.h"
#include "StartPlayerTurnEvent.h"
#include "StartEnemyTurnEvent.h"
#include "LevelUpScreenLayer.h"

MapAnimationLayer::MapAnimationLayer(MapAnimation2 mapAnim, int layer, sf::RenderWindow* window, GraphicsAssets* asst, StringHandler* strHandler) : AnimationLayer(layer, window, asst, strHandler)
{
	drawBucket = CameraController(window);

	battleAnimation = BattleAnimation(window, asst);
	mapAnimation = MapAnimation2(&asst->mapPackage, &asst->verticalMapMenuPackage, &drawBucket);
	dotAnimation = MovementDotAnimation(&asst->mapPackage, &drawBucket);
	cursorAnimation = MapCursorAnimation(cursorOffset, UTIL::ScreenCoord(0, 0), &assets->mapPackage.cursorTexture, &drawBucket);
	menuAnimation = VerticalMenuAnimation(&asst->verticalMapMenuPackage, menuOffset, window);
	confirmationMenuAnimation = HorizontalMenuAnimation(&asst->horizontalMapMenuPackage, UTIL::ScreenCoord(0, 600), true, window);
	squadAnimation = SquadAnimation(&asst->mapPackage.squadTextureMap, &drawBucket);
	mapOverlayAnimation = MapOverlayAnimation(layer, &asst->mapOverlayPackage, window);

	seeThrough = false;
};

MapAnimationLayer::MapAnimationLayer(MapAnimation2 mapAnim, SquadAnimation squadAnim, MapCursorAnimation cursorAnim, int layer, sf::RenderWindow* window, GraphicsAssets* asst, UTIL::ScreenCoord cameraOffset, StringHandler* strHandler) : AnimationLayer(layer, window, asst, strHandler)
{
	drawBucket = CameraController(window, cameraOffset);

	battleAnimation = BattleAnimation(window, asst);
	mapAnimation = mapAnim;
	mapAnimation.setBucket(&drawBucket);
	dotAnimation = MovementDotAnimation(&asst->mapPackage, &drawBucket);
	cursorAnimation = cursorAnim;
	cursorAnimation.setBucket(&drawBucket);
	menuAnimation = VerticalMenuAnimation(&asst->verticalMapMenuPackage, menuOffset, window);
	confirmationMenuAnimation = HorizontalMenuAnimation(&asst->horizontalMapMenuPackage, UTIL::ScreenCoord(0, 600), true, window);
	squadAnimation = squadAnim;
	squadAnimation.setBucket(&drawBucket);
	mapOverlayAnimation = MapOverlayAnimation(layer, &asst->mapOverlayPackage, window);

	drawable = true;
	seeThrough = false;
};

MapAnimationLayer::MapAnimationLayer(const MapAnimationLayer& cpEQ)
{
	middleMan = cpEQ.middleMan;
	if (middleMan)
	{
		nextLevel = cpEQ.nextLevel->clone();
	}
	window = cpEQ.window;
	layer = cpEQ.layer;
	signals = cpEQ.signals;
	stringHandler = cpEQ.stringHandler;

	mapAnimation = cpEQ.mapAnimation;
	menuAnimation = cpEQ.menuAnimation;
	squadAnimation = cpEQ.squadAnimation;
	dotAnimation = cpEQ.dotAnimation;
	mapOverlayAnimation = cpEQ.mapOverlayAnimation;

	drawable = cpEQ.drawable;
	seeThrough = cpEQ.seeThrough;

}

MapAnimationLayer& MapAnimationLayer::operator=(const MapAnimationLayer asEQ)
{
	middleMan = asEQ.middleMan;
	if (middleMan)
	{
		nextLevel = asEQ.nextLevel->clone();
	}
	window = asEQ.window;
	layer = asEQ.layer;
	signals = asEQ.signals;
	stringHandler = asEQ.stringHandler;

	mapAnimation = asEQ.mapAnimation;
	menuAnimation = asEQ.menuAnimation;
	squadAnimation = asEQ.squadAnimation;
	dotAnimation = asEQ.dotAnimation;
	mapOverlayAnimation = asEQ.mapOverlayAnimation;

	drawable = asEQ.drawable;
	seeThrough = asEQ.seeThrough;

	return *this;
}

void MapAnimationLayer::applyEvent(StructuredEvent* evnt)
{
	evnt->applyToMapAnimationLayer(this);
}

void MapAnimationLayer::applyInitBattleMapEvent(InitBattleMapEvent* evnt)
{
	mapAnimation.initMapAnimation(evnt->getMapData());
	cursorAnimation.moveCursor(evnt->getCursorPos());
	squadAnimation.init(evnt->getSquadData());
	drawBucket.center(MapCoord(evnt->getCursorPos().x, evnt->getCursorPos().y), true);
	drawable = true;
}

void MapAnimationLayer::applyMapCursorEvent(MapCursorEvent* evnt)
{
	switch (evnt->getType())
	{
	case MapCursorEventType::move:
		cursorAnimation.moveCursor(evnt->getMoveData());
		drawBucket.pan(MapCoord(evnt->getMoveData().start.x, evnt->getMoveData().start.y), MapCoord(evnt->getMoveData().end.x, evnt->getMoveData().end.y));
		break;
	case MapCursorEventType::hide:
		cursorAnimation.deactivate();
		break;
	case MapCursorEventType::show:
		cursorAnimation.activate();
		break;
	}
}

void MapAnimationLayer::applyMovementDotsEvent(MovementDotsEvent* evnt)
{
	dotAnimation.startDotAnimation(evnt->getDotPath());
}

void MapAnimationLayer::applyMovementTargetCrossEvent(MovementTargetCrossEvent* evnt)
{
	if (evnt->putDown)
	{
		dotAnimation.startMovementCrossAnimation(evnt->coord);
	}
	else
	{
		dotAnimation.startMovementCrossRemovalAnimation();
	}
}

void MapAnimationLayer::applySquadMovedEvent(SquadMovedEvent* evnt)
{
	MoveData data = evnt->getMoveData();
	//måste kolla lag innan vi startar animationen, för animationen tar bort squaden ur kartan tillfälligt
	if (squadAnimation.getSquadTag(data.movedSquadID) == tagID::player)
	{
		dotAnimation.setDotPath(data.path);
		dotAnimation.setMovementCross(data.path.at(data.path.size() - 1));
	}
	else
	{
		drawBucket.center(data.path.at(0), false);
	}

	squadAnimation.startMovementAnimation(data);
	signals.push_back(AnimationSignal(layer, SignalType::animationStarted, SignalSubType::Movement));
	holdNewEvents = true;
}

void MapAnimationLayer::applySetAttackTargetEvent(SetAttackTargetEvent* evnt)
{
	setAttackTarget(evnt->getTargetID());
}

void MapAnimationLayer::setAttackTarget(int targetID)
{
	CursorPos position = CursorPos(squadAnimation.getSquadCoord(targetID).getX(), squadAnimation.getSquadCoord(targetID).getY());
	cursorAnimation.moveCursor(position);
	drawBucket.center(MapCoord(position.x, position.y), false);
}

void MapAnimationLayer::generalMenuControl(MenuEventType type, MenuVisualData menuData, MenuAnimation* animation)
{
	switch (type)
	{
	case MenuEventType::opened:
		animation->activate();
		animation->setMenuData(menuData);
		break;
	case MenuEventType::changedSelected:
		animation->setMenuData(menuData);
		break;
	case MenuEventType::closed:
		animation->deActivate();
		break;
	case MenuEventType::hidden:
		animation->deActivate();
		break;
	case MenuEventType::shown:
		animation->activate();
		break;
	}
}

void MapAnimationLayer::applyMenuEvent(MenuEvent* evnt)
{
	generalMenuControl(evnt->getEventType(), evnt->getMenuData(), &menuAnimation);
}

void MapAnimationLayer::applyConfirmationMenuEvent(ConfirmationMenuEvent* evnt)
{
	generalMenuControl(evnt->getEventType(), evnt->getMenuData(), &confirmationMenuAnimation);
}

void MapAnimationLayer::draw()
{
	window->clear();
	mapAnimation.draw();
	dotAnimation.draw();
	cursorAnimation.draw();
	squadAnimation.draw();

	if (squadAnimation.isAnySquadMoving() || (squadAnimation.getMovementAnimation().isAnimationFinished() && dotAnimation.getPathSize() > 0))
	{
		unsigned int moveLength = squadAnimation.getMovementAnimation().getMovementList().size();
		int currInd = squadAnimation.getMovementAnimation().getCurrentIndex();
		if (moveLength - currInd <= dotAnimation.getPathSize())
		{
			dotAnimation.eatOffTile();
		}
	}

	if (squadAnimation.isMoveAnimationDone())
	{
		signals.push_back(AnimationSignal(layer, SignalType::animationDone, SignalSubType::Movement));
		squadAnimation.animationEndingHandled();
		holdNewEvents = false;
	}

	if (activeDeathAnimation && !squadAnimation.ongoingDeathAnimation())
	{
		signals.push_back(AnimationSignal(layer, SignalType::animationDone, SignalSubType::Death));
		activeDeathAnimation = false;
		holdNewEvents = false;
	}

	drawBucket.draw();

	menuAnimation.draw();
	battleAnimation.draw();
	if (battleAnimation.isAnimationDone())
	{
		battleAnimation.resetAnimation();
		signals.push_back(AnimationSignal(layer, SignalType::animationDone, SignalSubType::Battle));
		holdNewEvents = false;
	}

	mapOverlayAnimation.draw();
	concatSignals(mapOverlayAnimation.retrieveSignals());

	confirmationMenuAnimation.draw();
}

void MapAnimationLayer::openMapAnimationLayer(bool copyBattleField)
{
	if (copyBattleField)
	{
		openNewLayer(new MapAnimationLayer(mapAnimation, squadAnimation, cursorAnimation, layer + 1, window, assets, drawBucket.getOffset(), stringHandler));
	}
	else
	{
		openNewLayer(new MapAnimationLayer(mapAnimation, layer + 1, window, assets, stringHandler));
	}
}

void MapAnimationLayer::concatSignals(std::vector<AnimationSignal> newSignals)
{
	signals.insert(signals.begin(), newSignals.begin(), newSignals.end());
}

void MapAnimationLayer::openLevelUpScreenLayer()
{
	openNewLayer(new LevelUpScreenLayer(layer + 1, window, assets, stringHandler));
}

void MapAnimationLayer::applyBattleEvent(BattleEvent* evnt)
{
	battleAnimation.setup(evnt->getVisualData());
	signals.push_back(AnimationSignal(layer, SignalType::animationStarted, SignalSubType::Battle));
	holdNewEvents = true;
}

void MapAnimationLayer::applyUnitKilledEvent(UnitKilledEvent* evnt)
{
	squadAnimation.killUnit(evnt->getSquadID(), evnt->getUnitID());
	signals.push_back(AnimationSignal(layer, SignalType::animationStarted, SignalSubType::Death));
	activeDeathAnimation = true;
	holdNewEvents = true;
}

void MapAnimationLayer::applyStartPlayerTurnEvent(StartPlayerTurnEvent* evnt)
{
	CursorPos currentPos = cursorAnimation.getPosition();
	drawBucket.center(MapCoord(currentPos.x, currentPos.y), false);
}

void MapAnimationLayer::applyStartEnemyTurnEvent(StartEnemyTurnEvent* evnt)
{
}

void MapAnimationLayer::applyVictoryAchievedEvent(VictoryAchievedEvent* evnt)
{
	mapOverlayAnimation.playVictoryAnimation();
}