#include "BrowserEvent.h"
#include "BrowserAnimation.h"

void BrowserCursorMove::actUponBrowserAnim(BrowserAnimation* anim)
{
	anim->performCursorMove(this);
}

void SelectionMade::actUponBrowserAnim(BrowserAnimation* anim)
{
	anim->performSelection(this);
}

void BrowserOpened::actUponBrowserAnim(BrowserAnimation* anim)
{
	anim->initBrowser(initData);
}

void BrowserActiveness::actUponBrowserAnim(BrowserAnimation* anim)
{
	if (activated)
	{
		anim->activateBrowser();
	}
	else
	{
		anim->deActivateBrowser();
	}
}

void BrowserPickup::actUponBrowserAnim(BrowserAnimation* anim)
{
	anim->pickUpItem(pickupPos);
}

void BrowserDrop::actUponBrowserAnim(BrowserAnimation* anim)
{
	anim->dropItem(dropPos);
}

void BrowserSwap::actUponBrowserAnim(BrowserAnimation* anim)
{
	anim->swapItem(swapPos);
}