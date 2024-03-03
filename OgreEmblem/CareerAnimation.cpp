#include "CareerAnimation.h"
#include "Trait.h"
#include "Job.h"


void CareerAnimation::draw(sf::RenderWindow* window)
{
	drawCareer(!initiated, window);
	initiated = true;
}

void CareerAnimation::drawCareer(bool init, sf::RenderWindow* window)
{
	drawCareerStage(careerToDraw.getCareerStage(CareerTierTag::apprentice),
		careerToDraw.isTierMastered(CareerTierTag::apprentice),
		apprenticePos,
		init,
		window);
	drawCareerStage(careerToDraw.getCareerStage(CareerTierTag::professional),
		careerToDraw.isTierMastered(CareerTierTag::professional),
		professionalPos,
		init,
		window);
	drawCareerStage(careerToDraw.getCareerStage(CareerTierTag::master),
		careerToDraw.isTierMastered(CareerTierTag::master),
		masterPos,
		init,
		window);
}

void CareerAnimation::drawCareerStage(CareerStage cStage, bool mastered, sf::Vector2f pos, bool init, sf::RenderWindow* window)
{
	unsigned int i;
	TraitTag majorTag = TraitTag::enumTraitNone;
	if (mastered)
	{
		majorTag = cStage.getMajorTrait().getTag();
	}
	drawJob(cStage.getJob()->getTag(), pos, init, window);
	//drawMajorTraitSlot(majorTag, pos+majorOffset, init, window);

	//std::vector<LesserTrait*> lesserTraits = cStage.getLesserTraits();
	std::vector<Trait> lesserTraits = cStage.getLesserTraits();
	unsigned int stageSlots = cStage.getNumberOfTraitSlots();
	TraitTag lesserTag;
	for (i = 0; i < stageSlots; i++)
	{
		lesserTag = TraitTag::enumTraitNone;
		if (i < stageSlots)
		{
			if (i < lesserTraits.size())
			{
				lesserTag = lesserTraits.at(i).getTag();
			}
			else
			{
				lesserTag = TraitTag::enumTraitNone;
			}
		}
		sf::Vector2f lesserOffset = sf::Vector2f((i+1)*((JOB_WIDTH)/ (stageSlots + 1)) - LESSER_TRAIT_WIDTH/2, JOB_HEIGHT - 20);

		drawLesserTraitSlot(lesserTag, pos + lesserOffset + offset, init, window);
	}
}

void CareerAnimation::drawMajorTraitSlot(TraitTag trait, sf::Vector2f position, bool init, sf::RenderWindow* window)
{
	sf::Sprite traitSprite, backgroundSprite;
	sf::Text traitName;

	backgroundSprite.setTexture(traitAssets->traitBackgroundTexture);
	backgroundSprite.setPosition(position + offset);
	window->draw(backgroundSprite);
	if (trait != TraitTag::enumTraitNone)
	{
		traitSprite.setTexture(traitAssets->traitTextures.find(trait)->second);
		traitSprite.setPosition(position + offset);
		window->draw(traitSprite);
		if (init)
		{
			addInteractionImage(&traitAssets->traitCircleHitBox, position);
		}
	}
}

void CareerAnimation::drawJob(JobTag job, sf::Vector2f position, bool init, sf::RenderWindow* window)
{
	sf::Sprite jobSprite, foregroundSprite;
	sf::Text jobName;

	foregroundSprite.setTexture(traitAssets->jobForeground);
	foregroundSprite.setPosition(position+offset);

	jobSprite.setTexture(traitAssets->defaultJobTexture);
	jobSprite.setPosition(position+offset);

	window->draw(jobSprite);
	window->draw(foregroundSprite);
}

void CareerAnimation::drawLesserTraitSlot(TraitTag trait, sf::Vector2f position, bool init, sf::RenderWindow* window)
{
	sf::Sprite traitSprite, backgroundSprite;
	sf::Text traitName;

	backgroundSprite.setTexture(traitAssets->traitBackgroundTexture);
	backgroundSprite.setPosition(position);
	window->draw(backgroundSprite);
	if (trait != TraitTag::enumTraitNone)
	{
		traitSprite.setTexture(traitAssets->traitTextures.find(trait)->second);
		traitSprite.setPosition(position);
		window->draw(traitSprite);
		if (init)
		{
			addInteractionImage(&traitAssets->traitCircleHitBox, position);
		}
	}
}

void CareerAnimation::mousePosUpdate(sf::Vector2i currentMousePos)
{
	sf::Vector2f mousePosTx(sf::Vector2f(currentMousePos.x, currentMousePos.y));
	isThisHoveredBy(mousePosTx);
}

bool CareerAnimation::traitIsHovered()
{
	return imageIsHovered;
}

TraitTag CareerAnimation::getHoveredTrait()
{
	if (!imageIsHovered)
	{
		throw new std::exception();
	}
	//traitbilderna ritas ut i ordningen: appr major, appr lesser, prof major, prof lesser, master major, master lesser
	int imageIndex = hoveredImage;
	unsigned int i;
	std::vector<CareerTierTag> careerTiers = { CareerTierTag::apprentice , CareerTierTag::professional, CareerTierTag::master };

	for (i = 0; i < careerTiers.size(); i++)
	{
		CareerStage careerStage = careerToDraw.getCareerStage(careerTiers.at(i)); 
		if (imageIndex < careerStage.getNumberOfLesserTraits() + 1)
		{
			if (imageIndex == 0)
			{
				return careerStage.getMajorTrait().getTag();
			}
			else
			{
				return careerStage.getLesserTraits().at(imageIndex).getTag();
			}
		}
	}
	throw new std::exception();

	return TraitTag::enumDummyTrait;
}