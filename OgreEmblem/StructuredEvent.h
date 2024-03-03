#pragma once
#include "GraphicalEvent.h"

class AnimationLayer;
class MapAnimationLayer;
class Graphics;

class BaseLayer;
class SquadBrowserLayer;
class EditSquadLayer;
class CampMenuLayer;
class SquadMenuLayer;
class MapAnimationLayer;
class AnimationLayer;
class LevelUpScreenLayer;
class DraftScreenLayer;
class ConfirmationLayer;
class DraftScreenLayer;
class SquadNamePickerLayer;

class StructuredEvent
{
protected:
	int layer = -1;
	bool ignoreHolds = false;
public:
	StructuredEvent() {};
	StructuredEvent(int lr) { layer = lr; };
	virtual StructuredEvent* allocateNew() const = 0;
	virtual StructuredEvent* clone() const = 0;
	virtual ~StructuredEvent() {};

	int getDepth() { return layer; };
	//virtual void openNewAnimationLayer(AnimationLayer* currLayer) = 0;
	//virtual void actUponAnimationLayer(AnimationLayer* layer) {	throw new std::exception(); };
	//virtual void actUponMapAnimationLayer(MapAnimationLayer* layer) { throw new std::exception(); };

	void setLayer(int lyr) { layer = lyr; };
	virtual bool tryLayer(AnimationLayer* layer);

	virtual void applyToBaseLayer(BaseLayer* layer) { throw new std::exception(); };
	virtual void applyToCampMenuLayer(CampMenuLayer* layer) { throw new std::exception(); };
	virtual void applyToSquadBrowserLayer(SquadBrowserLayer* layer) { throw new std::exception(); };
	virtual void applyToEditSquadLayer(EditSquadLayer* layer) { throw new std::exception(); };
	virtual void applyToSquadMenuLayer(SquadMenuLayer* layer) { throw new std::exception(); };
	virtual void applyToMapAnimationLayer(MapAnimationLayer* layer) { throw new std::exception(); };
	virtual void applyToLevelUpScreenLayer(LevelUpScreenLayer* layer) { throw new std::exception(); };
	virtual void applyToDraftScreenLayer(DraftScreenLayer* layer) { throw new std::exception(); };
	virtual void applyToConfirmationLayer(ConfirmationLayer* layer) { throw new std::exception(); };
	virtual void applyToSquadNamePickerLayer(SquadNamePickerLayer* layer) { throw new std::exception(); };
};



class CloseSubLayerEvent : public StructuredEvent
{
private:

public:
	CloseSubLayerEvent() {};
	CloseSubLayerEvent(int layer) : StructuredEvent(layer) {};

	CloseSubLayerEvent* allocateNew() const override { return new CloseSubLayerEvent(); };
	CloseSubLayerEvent* clone() const override { return new CloseSubLayerEvent(*this); };

	bool tryLayer(AnimationLayer* layer) override;

	void applyToBaseLayer(BaseLayer* layer) override;
	void applyToCampMenuLayer(CampMenuLayer* layer) override;
	void applyToSquadBrowserLayer(SquadBrowserLayer* layer) override;
	void applyToEditSquadLayer(EditSquadLayer* layer) override;
	void applyToSquadMenuLayer(SquadMenuLayer* layer) override;
	void applyToMapAnimationLayer(MapAnimationLayer* layer) override;
	void applyToLevelUpScreenLayer(LevelUpScreenLayer* layer) override;
	void applyToDraftScreenLayer(DraftScreenLayer* layer) override;
	//void openNewAnimationLayer(SquadManagerLayer* currLayer) override { throw new std::exception(); };
};