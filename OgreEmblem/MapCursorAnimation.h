#pragma once
#include "CursorAnimation.h"
#include "CameraController.h"
class MapCursorAnimation : public CursorAnimation
{
private:
	CameraController* drawBucket = nullptr;
	float offsetX = 0;
	float offsetY = -4;
public:
	MapCursorAnimation() {};
	MapCursorAnimation(UTIL::ScreenCoord offset, UTIL::ScreenCoord spacing, sf::Texture* texture, CameraController* drawBucket);

	void moveCursor(CursorPos newPos) override;
	void moveCursor(CursorMove moveData);

	void draw() override;
	void setBucket(CameraController* dBucket) { drawBucket = dBucket; };
};