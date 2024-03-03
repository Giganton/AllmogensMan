#include "ExperienceBar.h"
#include "Formler.h"

ExperienceBar::ExperienceBar(int startExp, UTIL::ScreenCoord barOffset)
{ 
	setXP(startExp); 
	offset = barOffset; 

	frame.setSize(sf::Vector2f(120, 40));
	frame.setFillColor(frameColor);
	frame.setPosition(sf::Vector2f(offset.x, offset.y));

	background.setSize(sf::Vector2f(114, 34));
	background.setFillColor(backgroundColor);
	background.setPosition(sf::Vector2f(offset.x + 3, offset.y + 3));

	barFrame.setSize(sf::Vector2f(barLength + 4, 16));
	barFrame.setFillColor(barFrameColor);
	barFrame.setPosition(sf::Vector2f(offset.x + 20 + 3, offset.y + 12 + 3));

	emptyBar.setSize(sf::Vector2f(barLength, 12));
	emptyBar.setFillColor(emptyBarColor);
	emptyBar.setPosition(sf::Vector2f(offset.x + 3 + 20 + 2, offset.y + 12 + 3 + 2));

	filledBar.setSize(sf::Vector2f(((float)experiencePercentage)/100 * barLength, 12));
	filledBar.setFillColor(filledBarColor);
	filledBar.setPosition(sf::Vector2f(offset.x + 3 + 20 + 2, offset.y + 12 + 3 + 2));
};

void ExperienceBar::draw(sf::RenderWindow* window)
{
	window->draw(frame);
	window->draw(background);
	window->draw(barFrame);
	window->draw(emptyBar);
	window->draw(filledBar);
}

void ExperienceBar::increment()
{
	if (experiencePercentage >= 101)
	{
		throw new std::exception();
	}
	experiencePercentage = experiencePercentage + 1;

	filledBar.setSize(sf::Vector2f(((float)experiencePercentage) / 100 * barLength, 12));
	filledBar.setFillColor(filledBarColor);
	filledBar.setPosition(sf::Vector2f(offset.x + 3 + 20 + 2, offset.y + 12 + 3 + 2));
}

void ExperienceBar::setXP(int xp)
{
	experiencePercentage = xp;

	filledBar.setSize(sf::Vector2f(((float)experiencePercentage) / 100 * barLength, 12));
	filledBar.setFillColor(filledBarColor);
	filledBar.setPosition(sf::Vector2f(offset.x + 3 + 20 + 2, offset.y + 12 + 3 + 2));
}