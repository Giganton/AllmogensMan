#include "Boon.h"
#include "AllBoons.h"

Boon* createBoon(BoonTag tag)
{
	return createBoon(tag, -1);
}
Boon* createBoon(BoonTag tag, int utilityInt)
{
	switch (tag)
	{
	case BoonTag::enumGiantStrength:
		return new GiantStrength();
		break;
	case BoonTag::enumShieldBearer:
		return new ShieldBearer();
		break;
	case BoonTag::enumIncreaseWepProfBoon_WarriorProf:
	case BoonTag::enumIncreaseWepProfBoon_HeroProf:
	case BoonTag::enumIncreaseWepProfBoon_WizardProf:
	{
		if (utilityInt == -1)
		{
			throw new std::exception();
		}
		return new IncreaseWepProfBoon(tag, utilityInt);
		break;
	}
	case BoonTag::enumHeavyArmor:
		return new HeavyArmor();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumAttached:
		return new Attached();
		break;
	case BoonTag::enumHejsan:
		return new Hejsan();
		break;
	case BoonTag::enumHejsan:
		return new Hejsan();
		break;
	case BoonTag::enumHejsan:
		return new Hejsan();
		break;
		//python-entry createBoon
	default:
		throw new std::exception();
	}
}