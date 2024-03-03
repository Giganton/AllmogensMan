#include "GraphicsAssets.h"

sf::Texture* UnitPackage::getProfessionPortrait(ProfessionTag tag)
{
	switch (tag)
	{
	default:
		return &defaultPortrait;
	}
}

sf::Vector2f UnitPackage::getPortraitSize()
{
	sf::Vector2u size = defaultPortrait.getSize();
	return sf::Vector2f((float)size.x, (float)size.y);
}